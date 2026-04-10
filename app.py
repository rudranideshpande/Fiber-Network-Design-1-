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
        locations = data['locations']
        edges = data['edges']

        # Build correct input
        input_data = f"{n} {len(edges)}\n"
        input_data += " ".join(locations) + "\n"

        for u, v, w in edges:
            input_data += f"{u} {v} {w}\n"

        result = subprocess.run(
            ["./kruskal"],
            input=input_data,
            text=True,
            capture_output=True
        )

        return jsonify({
            "output": result.stdout if result.stdout else result.stderr
        })

    except Exception as e:
        return jsonify({"output": "Error: " + str(e)})

if __name__ == '__main__':
    app.run(debug=True)
