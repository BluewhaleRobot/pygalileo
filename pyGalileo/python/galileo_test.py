import pyGalileo
import time


def test_pub():
    sdk = pyGalileo.SDK()
    while True:
        servers = sdk.GetServersOnline()
        if len(servers) == 0:
            print("No Server Found")
        for server in servers:
            print(server.getID())
            sdk.Connect("", True, 10000, None, None)
        sdk.PublishTest()
        time.sleep(1)


def test_get_servers_online():
    sdk = pyGalileo.SDK()
    while True:
        servers = sdk.GetServersOnline()
        if len(servers) == 0:
            print("No Server Found")
        for server in servers:
            print(server.getID())
            sdk.Connect("", True, 10000, None, None)
        time.sleep(1)


if __name__ == "__main__":
    test_get_servers_online()
