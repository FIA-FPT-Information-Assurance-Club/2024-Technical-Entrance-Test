from pathlib import Path
import random, time

try:
    p = Path(__file__).with_name('flag.txt')
    with p.open('r') as fin:
        flag = fin.read()
except:
    print("Problem is misconfigured - ping us on discord if this is happening on the shell server")
    exit()

timestamp = round(time.time())
structured_time = time.localtime(timestamp)
formatted_time = time.strftime("%Y-%m-%d %H:%M:%S", structured_time)

random.seed(timestamp)
print("Date and Time:", formatted_time)
print("Welcome to Randomteuz's Restless Guessing Game!")
print("[r] Print a new random number")
print("[g] Guess the next 200 random numbers and receive the flag!")
print("[q] Quit")

def guess_numbers():
    print("Guess the next 200 random numbers for a flag!")
    print("Good luck!")
    for i in range(1, 201):
        print(f"Enter your guess {i}:")
        guess = input("> ")
        if guess != str(random.randint(1, 100000000)):
            print("That's incorrect. Get out of here!")
            return
    print("What? You must have psychic powers... Well here's your flag:")
    print(flag)

while True:
    inp = input("\n> ")
    if inp == "r":
        print(random.randint(1, 100000000))
    elif inp == "g":
        guess_numbers()
        break
    elif inp == "q":
        print("Goodbye!")
        break