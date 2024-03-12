



<font size="10">Restless Gamble</font>

​		10<sup>th</sup> March 2024

​		Challenge Author(s): Randomteuz

​		

 



### Description:

Gambling is all about anticipating the possibilities to win more than lose, I don't want that. I want to win all the time, 200 times, and fast! Can you help me beat this game?

### Objective

Understanding how random functions work, learn about random seed and automation and connection in ctf using pwntools

### Difficulty:

`easy`

### Flag:

`FIA{1s_R4ndoM_bU7_n0T_RaNd0M}`



# Challenge

```
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
```

# Solver

When connecting to the server, and in the given server python file, there's the line
```
print("Date and Time:", formatted_time)
```
The server also set a random seed
```
random.seed(timestamp)
```
The timestamp is rounded, then formatted and given to the players. Meaning one can extract the time given, turn it back into a timestamp and use it in their own random number generator which will give out exact numbers as the server's generating

Make a function like this to read data and extract the time information using ```re``` library, which is about regex
```
def extract_time(s):
    # Define a regular expression pattern to match the date and time
    pattern = r"Date and Time: (\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})"

    # Search for the pattern in the text
    match = re.search(pattern, s)

    # Extract the date and time if the pattern is found
    return match.group(1)
```
And another one to turn the time extracted into timestamp so it can be used as the seed using the ```pytz``` library. The key problem here is indicating the timezone that the timestamp is gonna be in, but mostly  it's either the local timezone, or GMT+0. After testing, one can find out that the correct timezone is GMT+0
```
def produce_seed(s):
    date_string = s

    # Convert string to datetime object
    datetime_object_local = datetime.strptime(date_string, "%Y-%m-%d %H:%M:%S")

    # Convert local datetime object to UTC datetime object
    datetime_object_utc = datetime_object_local.replace(tzinfo=pytz.utc)

    # Convert UTC datetime object to epoch timestamp
    epoch_timestamp_utc = datetime_object_utc.timestamp()
    return epoch_timestamp_utc
```

After that, use the output as the seed, generate that numbers, and submit them to the server
```
from pwn import *
import re
import random
from datetime import datetime
import pytz

def extract_time(s):
    # Define a regular expression pattern to match the date and time
    pattern = r"Date and Time: (\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})"

    # Search for the pattern in the text
    match = re.search(pattern, s)

    # Extract the date and time if the pattern is found
    return match.group(1)

def produce_seed(s):
    date_string = s

    # Convert string to datetime object
    datetime_object_local = datetime.strptime(date_string, "%Y-%m-%d %H:%M:%S")

    # Convert local datetime object to UTC datetime object
    datetime_object_utc = datetime_object_local.replace(tzinfo=pytz.utc)

    # Convert UTC datetime object to epoch timestamp
    epoch_timestamp_utc = datetime_object_utc.timestamp()
    return epoch_timestamp_utc


time = extract_time(data_str)
seed = produce_seed(time)

random.seed(seed) 
conn = remote('14.225.204.145', 3001)
data=conn.recvuntil(b'>')
data_str=data.decode()
print(data_str)

conn.sendline(b'g')
test=conn.recvuntil(b'>')
print(test.decode())

for i in range(200):
    number = str(random.randint(1, 100000000))
    conn.sendline(number)
    print(number)
    data=conn.recvline()
    print(data.decode())
data=conn.recvline()
print(data.decode())
```
