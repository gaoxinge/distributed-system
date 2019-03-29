import json
import requests


headers = {
    "Content-type": "application/json-rpc",
    "Accept": "text/json"
}


app_params1 = {
    "jsonrpc": "2.0",
    "method": "sayHello",
    "params": ["gxg"],
    "id": 1
}
response = requests.post(
    url="http://127.0.0.1:8080/com.unj.dubbotest.provider.DemoService",
    data=json.dumps(app_params1),
    headers=headers
)
print(response.json())


app_params2 = {
    "jsonrpc": "2.0",
    "method": "getUsers",
    "params": [],
    "id": 1
}
response = requests.post(
    url="http://127.0.0.1:8080/com.unj.dubbotest.provider.DemoService",
    data=json.dumps(app_params2),
    headers=headers
)
print(response.json())
