import json
import os
import socket
import subprocess
import time
import random
import unittest
import select
from pathlib import Path
"""
The following are high-level tests for our server application
that receives and handles tax reports of specified format
subject to user authentication and authorization.
"""

TCP_IP = 'localhost'
BUFFER_SIZE = 1024
OK = 'OK'
NOK = 'NOK'

# Credentials are hardcoded in the application.
# As an exercise, you can extend the application with the support for
# registering users and storing their credentials in some kind of database.
LOGIN = 'John Doe'
PASSWORD = "@12345"

# For formatting, you can use
# yapf --in-place --recursive --style="{ based_on_style: pep8, column_limit: 120 }" .


class TestsBase:
    def setUp(self):
        # 1. Prepare a command to start the server (bound to the provided port
        # and accepting reports of the provided format (JSON, XML)

        # TODO: pass binary path as a command line argument
        binary = Path(__file__).absolute().parents[3] / Path('./build/main/Main')
        self.TCP_PORT = random.randint(3000, 9000)
        command = '{} --port {} --format {}'.format(binary, self.TCP_PORT, self.REPORT_FORMAT)

        # 2. Create a subprocess and start the server
        self.process = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
        time.sleep(0.1)

        # 3. Create a TCP connection to the server
        # so that we can send reports and receive replies.
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((TCP_IP, self.TCP_PORT))

    def tearDown(self):
        self.sock.close()
        self.process.stdout.close()
        self.process.kill()
        self.process.wait()


class JsonTaxReportTests(TestsBase, unittest.TestCase):
    REPORT_FORMAT = 'json'

    def login(self, sock=None):
        sock = sock or self.sock
        sock.send(json.dumps({'login': LOGIN, 'password': PASSWORD}).encode())
        self.assertEqual(sock.recv(BUFFER_SIZE).decode(), OK)

    def test_sending_tax_reports_succeeds(self):
        self.login()

        request = json.dumps({'payer': 1, 'tax': 'Corporate Income Tax', 'amount': 25000, 'year': 2020})
        self.sock.send(request.encode())
        response = self.sock.recv(BUFFER_SIZE)
        self.assertEqual(response.decode(), OK)

        request = json.dumps({'payer': 2, 'tax': 'Value Added Tax', 'amount': 5000, 'year': 2020})
        self.sock.send(request.encode())
        response = self.sock.recv(BUFFER_SIZE)
        self.assertEqual(response.decode(), OK)

    def test_sending_tax_reports_from_multiple_clients_succeeds(self):
        self.sock2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock2.connect((TCP_IP, self.TCP_PORT))

        self.sock3 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock3.connect((TCP_IP, self.TCP_PORT))

        for i, sock in enumerate([self.sock, self.sock2, self.sock3]):
            self.login(sock)
            request = json.dumps({'payer': i + 1, 'tax': 'Corporate Income Tax', 'amount': 25000, 'year': 2020})
            sock.send(request.encode())
            response = sock.recv(BUFFER_SIZE)
            self.assertEqual(response.decode(), OK)

        self.sock2.close()
        self.sock3.close()

    def test_sending_tax_report_fails_due_to_missing_data(self):
        self.login()

        request = json.dumps({'payer': 1, 'tax': 'Corporate Income Tax'})
        self.sock.send(request.encode())
        response = self.sock.recv(BUFFER_SIZE)
        self.assertEqual(response.decode(), NOK)

    def test_sending_tax_report_fails_due_to_invalid_format_of_data(self):
        self.login()
        request = 'Something not JSON'

        self.sock.send(request.encode())
        response = self.sock.recv(BUFFER_SIZE)

        self.assertEqual(response.decode(), NOK)

    def test_cannot_send_report_when_login_fails(self):
        self.sock.send(json.dumps({'login': LOGIN + 'x', 'password': PASSWORD + 'y'}).encode())
        self.assertEqual(self.sock.recv(BUFFER_SIZE).decode(), NOK)

        try:
            self.sock.send(json.dumps({}).encode())
            self.assertEqual(len(self.sock.recv(BUFFER_SIZE)), 0)
        except ConnectionAbortedError:
            pass

    def test_sending_tax_report_fails_due_to_invalid_taxpayer_id(self):
        self.login()

        invalidId = 111  # Ids are just hardcoded in the application
        request = json.dumps({'payer': invalidId, 'tax': 'Corporate Income Tax', 'amount': 25000, 'year': 2020})

        self.sock.send(request.encode())
        self.assertEqual(self.sock.recv(BUFFER_SIZE).decode(), NOK)  # Because not authorized

    def test_sending_tax_report_fails_due_to_invalid_taxname(self):
        self.login()

        request = json.dumps({'payer': 1, 'tax': 'Weird Tax', 'amount': 25000, 'year': 2020})
        self.sock.send(request.encode())
        self.assertEqual(self.sock.recv(BUFFER_SIZE).decode(), NOK)


class XmlTaxReportTests(TestsBase, unittest.TestCase):
    REPORT_FORMAT = 'xml'

    def login(self):
        request = """<credentials><login>{}</login>
                        <password>{}</password>
                     </credentials>""".format(LOGIN, PASSWORD)
        self.sock.send(request.encode())
        response = self.sock.recv(BUFFER_SIZE)
        self.assertEqual(response.decode(), OK)

    def test_sending_tax_report_succeeds(self):
        self.login()
        request = """<report>
                        <payer>1</payer>
                        <tax>Corporate Income Tax</tax>
                        <amount>25000</amount>
                        <year>2020</year>
                    </report>"""

        self.sock.send(request.encode())
        response = self.sock.recv(BUFFER_SIZE)

        self.assertEqual(response.decode(), OK)

    def test_sending_valid_and_invalid_tax_reports(self):
        self.login()
        valid_request = """<report>
                               <payer>1</payer>
                               <tax>Corporate Income Tax</tax>
                               <amount>25000</amount>
                               <year>2020</year>
                           </report>"""

        self.sock.send(valid_request.encode())
        response = self.sock.recv(BUFFER_SIZE)
        self.assertEqual(response.decode(), OK)

        invalid_request = 'Something not XML'
        self.sock.send(invalid_request.encode())
        response = self.sock.recv(BUFFER_SIZE)
        self.assertEqual(response.decode(), NOK)

        self.sock.send(valid_request.encode())
        response = self.sock.recv(BUFFER_SIZE)
        self.assertEqual(response.decode(), OK)

    def test_sending_tax_report_fails_due_to_missing_data(self):
        self.login()
        request = """<report>
                        <payer>2</payer>
                        <tax>Corporate Income Tax</tax>
                    </report>"""

        self.sock.send(request.encode())
        response = self.sock.recv(BUFFER_SIZE)
        self.assertEqual(response.decode(), NOK)

    def test_sending_tax_report_fails_due_to_invalid_format_of_data(self):
        self.login()
        request = 'Something not XML'

        self.sock.send(request.encode())
        response = self.sock.recv(BUFFER_SIZE)

        self.assertEqual(response.decode(), NOK)


if __name__ == '__main__':
    unittest.main()
