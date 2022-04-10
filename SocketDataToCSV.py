import websocket
import time
import csv

x_value = 0
total_1 = 0
total_2 = 0

with open('data.csv', 'w',newline='') as csv_file:
        fieldnames = ["x_value", "total_1", "total_2"]
        csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        csv_writer.writeheader()



while True:
    ws = websocket.WebSocket()
    ws.connect("ws://192.168.1.43:81")
    #ws.send("Hello, Server")
    print(ws.recv())
    data=ws.recv()
    data=data.replace("{","").replace("}","").replace(":",",").replace('"',"")
    arrdata=data.split(',')

    with open('data.csv', 'a',newline='') as csv_file:
        csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        info = {
            "x_value": x_value,
            "total_1": arrdata[1],
            "total_2": arrdata[3]
        }
        #print(info)
        csv_writer.writerow(info)
        print(arrdata[1], arrdata[3], arrdata[5])
 
    x_value += 1
    ws.close()
