from flask import Flask, render_template, request, jsonify
import subprocess
import os

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/run', methods=['POST'])
def run():
    try:
        data = request.get_json()

        n = data['n']
        locations = data['locations']
        edges = data['edges']

        # Build correct input format
        input_data = f"{n} {len(edges)}\n"
        input_data += " ".join(locations) + "\n"

        for u, v, w in edges:
            input_data += f"{u} {v} {w}\n"

        # Ensure executable exists
        executable_path = "./kruskal"

        if not os.path.exists(executable_path):
            return jsonify({"output": "Error: kruskal executable not found!"})

        # Run C program safely
        result = subprocess.run(
            [executable_path],
            input=input_data,
            text=True,
            capture_output=True,
            timeout=5   # 🔥 prevents hanging
        )

        # Return output or error
        if result.returncode != 0:
            return jsonify({"output": result.stderr})

        return jsonify({"output": result.stdout})

    except subprocess.TimeoutExpired:
        return jsonify({"output": "Error: Execution timed out!"})

    except Exception as e:
        return jsonify({"output": "Error: " + str(e)})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=10000)
