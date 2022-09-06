from flask import Flask
import os


app = Flask(__name__)



@app.route('/helloesp')
def helloHandler():
    os.system("curl http://192.168.1.25/on")
    return 'Hello ESP8266, from Flask'


@app.route('/left')
def helloHandlers():
    os.system("xrandr --output HDMI-1 --rotate right")
    return 'Hello ESP8266, from Flask'

@app.route('/right')
def helloHandlerss():
    os.system("xrandr --output HDMI-1 --rotate left")
    return 'Hello ESP8266, from Flask'

@app.route('/normal')
def helloHandlersss():
    os.system("xrandr --output HDMI-1 --rotate normal")
    return 'Hello ESP8266, from Flask'


 
app.run(host='0.0.0.0', port= 8090)