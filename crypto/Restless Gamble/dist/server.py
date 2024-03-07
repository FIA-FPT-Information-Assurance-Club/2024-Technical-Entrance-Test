from pathlib import Path
import random, time

try:
    p = Path(__file__).with_name('flag.txt')
    with p.open('r') as fin:
        flag = fin.read()
except:
    print("Problem is misconfigured - ping us on discord if this is happening on the shell server")
    exit()


random.seed(round(time.time() / 100, 69))
print("Welcome to Randomteuz's Random Number Generator!")
print("[r] Print a new random number")
print("[g] Guess the next two random numbers and receive the flag!")
print("[q] Quit")


while True:
    inp = input("\n> ")
    if inp == "r":
        print(random.randint(1, 100000000))
    elif inp == "g":
        print("Guess the next three random numbers for a flag!\nGood luck!\nEnter your first guess:")
        if input("> ") == str(random.randint(1, 100000000)):
            print("Wow, lucky guess... You won't be able to guess right a second time\nEnter your second guess:")
            if input("> ") == str(random.randint(1, 100000000)):
                print("Tsk, Nice try, but can you guess the third number?\nEnter your third guess:")
                if input("> ") == str(random.randint(1, 100000000)):
                    print("What? You must have psychic powers... Well here's your flag: ")
                    print(flag)
                    break
                else:
                    print("That's incorrect. Get out of here!")
                break
            else:
                print("That's incorrect. Get out of here!")
                break
        else:
            print("That's incorrect. Get out of here!")
            break
    elif inp == "q":
        print("Goodbye!")
        break