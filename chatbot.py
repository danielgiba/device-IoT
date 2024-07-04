from flask import Flask, request, jsonify
from influxdb import InfluxDBClient
from chatterbot import ChatBot
from chatterbot.trainers import ChatterBotCorpusTrainer

app = Flask(__name__)

client = InfluxDBClient(host='localhost', port=8086)
client.switch_database('sensor_data')

chatbot = ChatBot('DataBot')
trainer = ChatterBotCorpusTrainer(chatbot)
trainer.train("chatterbot.corpus.english")

@app.route('/chat', methods=['POST'])
def chat():
    user_input = request.json.get('message')
    if 'temperature' in user_input.lower():
        result = client.query('SELECT last("value") FROM "temperature"')
        temp = list(result.get_points())[0]['last']
        response = f"The latest temperature is {temp}°C"
    elif 'humidity' in user_input.lower():
        result = client.query('SELECT last("value") FROM "humidity"')
        humidity = list(result.get_points())[0]['last']
        response = f"The latest humidity is {humidity}%"
    else:
        response = str(chatbot.get_response(user_input))
    
    return jsonify({'response': response})

if __name__ == "__main__":
    app.run(port=5000, debug=True)
