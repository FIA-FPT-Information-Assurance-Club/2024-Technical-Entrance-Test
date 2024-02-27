import os
from flask import Flask, make_response, render_template, request

app = Flask(__name__)
app.secret_key = os.urandom(32)

FLAG = "FIA{Y0u_h4v3_5ucceSSfully_c0mplEted_All_m1sSiOns-57656c636f6d6520746f20464941}"

USER_AGENT = "HACKER-1337"

missions = [
    """
user_input_path = os.path.abspath(os.path.join("/", user_input))
if (not user_input.startswith("/fia")) or user_input.endswith("/flag"):
    return False, f"Your input is {user_input} has been rejected!!!"
    
return user_input_path == "/flag", user_input_path
""",
    """
user_input2 = user_input.replace("../", "")
if user_input2 == "/flag":
    return False, f"Your input is {user_input} has been rejected!!!"

user_input_path = os.path.abspath(os.path.join("/", user_input2))
return user_input_path == "/flag", user_input_path
""",
    """
if "../" in user_input or user_input == "/flag":
    return False

user_input_path = os.path.abspath(os.path.join("/", user_input))
return user_input_path == "/flag"
"""
]

sessions = []

def create_session():
    session_id = os.urandom(32).hex()
    return {
        'id': session_id,
        'mission1': False,
        'mission2': False,
        'mission3': False,
    }

def pre_check(user_input):
    if not isinstance(user_input, str):
        return 1
    if len(user_input) > 512:
        return 2
    if user_input == "flag":
        return 3
    if user_input == "./flag":
        return 4

def mission1(user_input):
    user_input_path = os.path.abspath(os.path.join("/", user_input))
    if (not user_input.startswith("/fia")) or user_input.endswith("/flag"):
        return False, f"Your input is {user_input} has been rejected!!!"
    
    return user_input_path == "/flag", user_input_path

def mission2(user_input):
    user_input2 = user_input.replace("../", "")
    if user_input2 == "/flag":
        return False, f"Your input is {user_input} has been rejected!!!"

    user_input_path = os.path.abspath(os.path.join("/", user_input2))
    return user_input_path == "/flag", user_input_path

def mission3(user_input):
    if "../" in user_input or user_input == "/flag":
        return False

    user_input_path = os.path.abspath(os.path.join("/", user_input))
    return user_input_path == "/flag"

def check_user_agent():
    if request.headers.get('User-Agent') != USER_AGENT:
        return False
    return True

@app.route('/')
def index():
    return render_template('index.html', error='')

@app.route('/robots.txt')
def robots_txt():
    return "User-agent: *\nDisallow: /s3cr3t-p4g3", 200, {'Content-Type': 'text/plain'}

@app.route('/s3cr3t-p4g3')
def mission():
    if not check_user_agent():
        return render_template('error.html', error='You are must be a HACKER-1337 to access this page!!!')
    
    token = request.cookies.get("token")
    session = next((s for s in sessions if s["id"] == token), None)

    if not session:
        session = create_session()
        sessions.append(session)
        response = make_response(render_template("mission.html", mission=missions[0]))
        response.set_cookie("token", session["id"])
        return response
    
    if not session["mission1"]:
        return render_template("mission.html", mission=missions[0])
    elif not session["mission2"]:
        return render_template("mission.html", mission=missions[1])
    elif not session["mission3"]:
        return render_template("mission.html", mission=missions[2])
    else:
        return render_template("mission.html", mission=FLAG)
    
@app.route('/s3cr3t-p4g3', methods=['POST'])
def mission_post():
    if not check_user_agent():
        return render_template('error.html', error='You are must be a HACKER-1337 to access this page!!!')
    
    token = request.cookies.get("token")
    session = next((s for s in sessions if s["id"] == token), None)
    
    if not session:
        return render_template("error.html", error="You are not authorized to access this page!!!")
    
    user_input = request.form.get("user_input")

    if pre_check(user_input) == 1:
        return render_template('errori.html', error='Your input must be a string')
    elif pre_check(user_input) == 2:
        return render_template('errori.html', error='Your input is too long, it must be less than 512 characters')
    elif pre_check(user_input) == 3:
        return render_template('errori.html', error='Your input CANNOT be "flag"')
    elif pre_check(user_input) == 4:
        return render_template('errori.html', error='Your input CANNOT be "./flag"')

    if not session["mission1"]:
        result, message = mission1(user_input)
        if result:
            session["mission1"] = True
            # Show popup message and render next mission
            return render_template("mission.html", mission=missions[1], message="Congratulation!!! You have completed mission 1!!!")
        else:
            return render_template("errori.html", error=message)
    elif not session["mission2"]:
        result, message = mission2(user_input)
        if result:
            session["mission2"] = True
            # Show popup message and render next mission
            return render_template("mission.html", mission=missions[2], message="Congratulation!!! You have completed mission 2!!!")
        else:
            return render_template("errori.html", error=message)
    elif not session["mission3"]:
        result = mission3(user_input)
        if result:
            session["mission3"] = True
            # Show popup message and render next mission
            return render_template("mission.html", mission=FLAG, message="Congratulation!!! You have completed all missions!!!")
        else:
            return render_template("errori.html", error="Your user_input is incorrect!!!")

if __name__ == '__main__':
    app.run(debug=False, host='0.0.0.0', port=5000)