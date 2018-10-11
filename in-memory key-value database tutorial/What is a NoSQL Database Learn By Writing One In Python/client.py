# -*- coding: utf-8 -*-
import socket


def _get_kind(value):
    if isinstance(value, list):
        return 'LIST'
    if isinstance(value, int):
        return 'INT'
    if isinstance(value, str):
        return 'STRING'
    return ''


class Client(object):

    def __init__(self, host, port):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((host, port))

    def get(self, key):
        command, key, value, kind = 'GET', str(key), '', ''
        return self.send(command, key, value, kind)

    def put(self, key, value):
        command, key, value, kind = 'PUT', key, str(value), _get_kind(value)
        return self.send(command, key, value, kind)

    def get_list(self, key):
        command, key, value, kind = 'GETLIST', key, '', ''
        return self.send(command, key, value, kind)

    def put_list(self, key, value):
        command, key, value, kind = 'PUTLIST', key, ','.join(map(str, value)), 'LIST'
        return self.send(command, key, value, kind)

    def increment(self, key):
        command, key, value, kind = 'INCREMENT', key, '', ''
        return self.send(command, key, value, kind)

    def append(self, key, value):
        command, key, value, kind = 'APPEND', key, str(value), _get_kind(value)
        return self.send(command, key, value, kind)

    def delete(self, key):
        command, key, value, kind = 'DELETE', key, '', ''
        return self.send(command, key, value, kind)

    def stats(self):
        command, key, value, kind = 'STATS', '', '', ''
        return self.send(command, key, value, kind)

    def send(self, command, key, value, kind):
        message = ';'.join([command, key, value, kind])
        self.socket.send(message.encode())
        message = self.socket.recv(4096).decode()
        self.socket.close()
        return message


if __name__ == '__main__':
    client = Client('localhost', 50505)
    print client.put('a', '1')
    client = Client('localhost', 50505)
    print client.put('b', 2)
    client = Client('localhost', 50505)
    print client.get('a')
    client = Client('localhost', 50505)
    print client.increment('b')
    client = Client('localhost', 50505)
    print client.put_list('foo', ['a', 'b', 'c'])
    client = Client('localhost', 50505)
    print client.append('foo', 1)
    client = Client('localhost', 50505)
    print client.get_list('foo')
    client = Client('localhost', 50505)
    print client.delete('a')
    client = Client('localhost', 50505)
    print client.stats()

