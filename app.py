from flask import Flask, request, jsonify, render_template
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

data_store = []

@app.route("/")   # 👈 ADD THIS
def home():
    return render_template("index.html")

@app.route('/update', methods=['POST'])
def update_data():
    data = request.json
    
    temperature = data['temperature']
    humidity = data['humidity']
    gas = data['gas']

    if temperature > 25 or humidity > 90 or gas > 500:
        status = "SPOILED"
    else:
        status = "SAFE"

    entry = {
        "temperature": temperature,
        "humidity": humidity,
        "gas": gas,
        "status": status
    }

    data_store.append(entry)

    return jsonify({"message": "Data received"}), 200


@app.route('/data', methods=['GET'])
def get_data():
    return jsonify(data_store)


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)