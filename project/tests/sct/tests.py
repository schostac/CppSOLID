import unittest
import subprocess
import os
import time
import socket
import json
from pathlib import Path

TCP_IP = 'localhost'
TCP_PORT = 7788
BUFFER_SIZE = 1024


class JsonTaxReportTests(unittest.TestCase):
    binary = Path(__file__).absolute().parents[3] / Path('./build/server/server')
    start_server= "exec {} {} json".format(binary, TCP_PORT)

    def setUp(self):
        self.process = subprocess.Popen(self.start_server, stdout=subprocess.PIPE, shell=True)
        time.sleep(0.1)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((TCP_IP, TCP_PORT))
    
    def tearDown(self):
        self.sock.close()
        self.process.stdout.close()
        self.process.kill()
        self.process.wait()

    def test_sending_tax_report_succeeds(self):
        request = json.dumps({
            'payer': 100, 
            'tax': 'Corporate Income Tax',
            'amount': 25000,
            'year': 2020
        })

        self.sock.send(request.encode())
        response = self.sock.recv(BUFFER_SIZE)

        self.assertEqual(response.decode(), "OK")

    def test_sending_taxt_report_fails_due_to_missing_data(self):
        request = json.dumps({
            'payer': 100, 
            'tax': 'Corporate Income Tax',
        })

        self.sock.send(request.encode())
        response = self.sock.recv(BUFFER_SIZE)
        self.assertEqual(response.decode(), "NOK")

    def test_sending_taxt_report_fails_due_to_invalid_format_of_data(self):
        request = 'Something not JSON'

        self.sock.send(request.encode())
        response = self.sock.recv(BUFFER_SIZE)

        self.assertEqual(response.decode(), "NOK")


class XmlTaxReportTests(unittest.TestCase):
    binary = Path(__file__).absolute().parents[3] / Path('./build/server/server')
    start_server= "exec {} {} xml".format(binary, TCP_PORT)

    def setUp(self):
        self.process = subprocess.Popen(self.start_server, stdout=subprocess.PIPE, shell=True)
        time.sleep(0.1)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((TCP_IP, TCP_PORT))
    
    def tearDown(self):
        self.sock.close()
        self.process.stdout.close()
        self.process.kill()
        self.process.wait()

    def test_sending_tax_report_succeeds(self):
        request = """<report><payer>100</payer><tax>Corporate Income Tax</tax>
                        <amount>25000</amount><year>2020</year></report>"""

        self.sock.send(request.encode())
        response = self.sock.recv(BUFFER_SIZE)

        self.assertEqual(response.decode(), "OK")

    def test_sending_taxt_report_fails_due_to_missing_data(self):
        request = """<report>
                        <payer>100</payer>
                        <tax>Corporate Income Tax</tax>
                    </report>"""

        self.sock.send(request.encode())
        response = self.sock.recv(BUFFER_SIZE)
        self.assertEqual(response.decode(), "NOK")

    def test_sending_taxt_report_fails_due_to_invalid_format_of_data(self):
        request = 'Something not XML'

        self.sock.send(request.encode())
        response = self.sock.recv(BUFFER_SIZE)

        self.assertEqual(response.decode(), "NOK")


if __name__ == '__main__':
    unittest.main()
