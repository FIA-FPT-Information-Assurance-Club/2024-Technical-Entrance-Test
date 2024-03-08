from flask import Flask, request, jsonify, render_template, redirect, url_for
import mysql.connector
import os

app = Flask(__name__)


@app.after_request
def add_header(response):
    response.headers['Cache-Control'] = 'no-cache, no-store, must-revalidate'
    response.headers['Pragma'] = 'no-cache'
    response.headers['Expires'] = '0'
    return response


@app.route('/api/check_username', methods=['POST'])
def check_username():
    # Get the username from the request data
    mydb = mysql.connector.connect(
        host=os.getenv('MYSQL_HOSTNAME'),
        user=os.getenv('MYSQL_USER'),
        password=os.getenv('MYSQL_PASSWORD'),
        database=os.getenv('MYSQL_DATABASE')
    )
    mycursor = mydb.cursor(prepared=True)
    data = request.get_json()
    username = data['username']

    # Construct the SQL query using string concatenation
    query = "SELECT * FROM users WHERE username = '" + username + "'"

    # Execute the SQL query
    response = None
    try:
        mycursor.execute(query, multi=False)
        result = mycursor.fetchone()
    except mysql.connector.errors.InterfaceError as e:
        print(e)
        result = None
        response = {'status': 'error',
                    'message': 'Query error. Here is the first part of the flag: [FIA{$QL_!nj3ct10n]'}

    if not response:
        if result:
            # If the username exists, return a JSON response with a success message
            response = {'status': 'success', 'message': 'Username exists'}
        else:
            # If the username doesn't exist, return a JSON response with an error message
            response = {'status': 'error',
                        'message': 'Username does not exist'}

    # Convert the response data to JSON and return it
    return jsonify(response)


@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')


@app.route('/api/feedback', methods=['POST'])
def submit_feedback():
    # code to process the feedback form data
    return jsonify({'status': 'success', 'message': 'Feedback submitted successfully'})


@app.route('/thankyou')
def thankyou():
    return render_template('thankyou.html')


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
