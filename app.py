from flask import Flask, render_template, request, jsonify
import subprocess

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/run', methods=['POST'])
def run():
    try:
        data = request.get_json()

        n = data['n']
        edges = data['edges']

        input_data = f"{n} {len(edges)}\n"
        for u, v, w in edges:
            input_data += f"{u} {v} {w}\n"

        result = subprocess.run(
            ["./kruskal"],   # IMPORTANT FIX
            input=input_data,
            text=True,
            capture_output=True
        )

        print("INPUT:", input_data)
        print("OUTPUT:", result.stdout)
        print("ERROR:", result.stderr)

        return jsonify({"output": result.stdout})

    except Exception as e:
        print("EXCEPTION:", str(e))
        return jsonify({"output": "Error: " + str(e)})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=10000)
