# -*- coding: utf-8 -*-
import socket


class Client(object):

    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def __enter__(self):
        self.sock.connect((self.host, self.port))
        self.rfile = self.sock.makefile('r', -1)
        self.wfile = self.sock.makefile('w', 0)
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.sock.close()

    def send(self, message):
        args = message.split()
        cmd = "*%d\r\n" % len(args)
        for arg in args:
            cmd += "$%d\r\n" % len(arg)
            cmd += "%s\r\n" % arg
        self.wfile.write(cmd)

    def recv(self):
        message = self.rfile.readline()
        if message[0] == "+":
            return message[1:-2]
        if message[0] == "-":
            return "(error) %s" % message[1:-2]
        if message[0] == ":":
            return "(integer) %s" % message[1:-2]
        if message[0] == "$":
            message = self.rfile.read(int(message[1:-2]) + 2)
            return "\"%s\"" % message[0:-2]
        if message[0] == "*":
            return "".join(["%d) %s\n" % (index + 1, self.recv()) for index in range(int(message[1:-2]))])

    def comm(self, message):
        self.send(message)
        return self.recv()
        

with Client("127.0.0.1", 6379) as client:
    print client.comm("SET key 1")
    print client.comm("FUCK")
    print client.comm("INCR key")
    print client.comm("GET key")

    print client.comm("RPUSH list foo")
    print client.comm("RPUSH list bar")
    print client.comm("RPUSH list Hello")
    print client.comm("RPUSH list World")
    print client.comm("LRANGE list 0 3")