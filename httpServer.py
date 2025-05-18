from flask import Flask, request
from logEvent import log_event

def start_http_server():
    app = Flask(__name__)
    http_counter = {"count": 0}

    @app.route('/latencia', methods=['POST'])
    def upload():
        http_counter["count"] += 1
        log_event("http", http_counter["count"])
        return "OK", 200

    app.run(host='0.0.0.0', port=5001)