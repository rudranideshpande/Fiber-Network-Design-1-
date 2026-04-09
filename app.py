from flask import Flask, render_template, request, jsonify
import subprocess

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/run', methods=['POST'])
def run():
    data = request.json
    n = data['n']
    edges = data['edges']

    input_data = f"{n} {len(edges)}\n"
    for u, v, w in edges:
        input_data += f"{u} {v} {w}\n"

    result = subprocess.run(
        ["kruskal"],
        input=input_data,
        text=True,
        capture_output=True
    )

    return jsonify({"output": result.stdout})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=10000)