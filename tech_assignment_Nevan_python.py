from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/sensor-data', methods=['POST'])
def receive_data():
    data = request.get_json()
    temperature = data.get('temperature')

    print(f"Received temperature: {temperature}")

    response = {
        "status": "success",
        "temperature": temperature
    }
    return jsonify(response)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
