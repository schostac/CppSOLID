import json
import os
import socket
import subprocess
import time
import unittest
import select
from pathlib import Path

TCP_IP = 'localhost'
TCP_PORT = 7788
BUFFER_SIZE = 1024
OK = 'OK'
NOK = 'NOK'

# Credentials are hardcoded in the application
LOGIN = 'Jhon Doe'
PASSWORD = "@12345"

# For formatting, use
# yapf --in-place --recursive --style="{ based_on_style: pep8, column_limit: 120 }" .


class TestsBase:
    def setUp(self):
        binary = Path(__file__).absolute().parents[3] / Path('./build/main/Main')
        command = 'exec {} --port {} --format {}'.format(binary, TCP_PORT, self.report_format)
        self.process = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)
        time.sleep(0.1)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((TCP_IP, TCP_PORT))

    def tearDown(self):
        self.sock.close()
        self.process.stdout.close()
        self.process.kill()
        self.process.wait()


class JsonTaxReportTests(TestsBase, unittest.TestCase):
    report_format = 'json'

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
        self.sock2.connect((TCP_IP, TCP_PORT))

        self.sock3 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock3.connect((TCP_IP, TCP_PORT))

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

        self.sock.send(json.dumps({}).encode())
        self.assertEqual(len(self.sock.recv(BUFFER_SIZE)), 0)

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
    report_format = 'xml'

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
