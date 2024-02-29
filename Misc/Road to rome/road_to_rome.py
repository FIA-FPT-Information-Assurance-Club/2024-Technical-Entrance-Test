#!/usr/bin/python3
import random
from inputimeout import inputimeout 
equations = ['*','+']
number = [0,1,5]
def romanToInt(s):
    roman_numeral_dict = {"I": 1, "V": 5, "X": 10, "L": 50, "C": 100, "D": 500, "M": 1000}
    result = 0
    prev = 0
    for letter in s:
        current_value = roman_numeral_dict[letter]
        if current_value > prev:
            result += current_value - 2 * prev
        else:
            result += current_value
        prev = current_value
    return result
def intToRoman(num):
    roman_numeral_dict = {
        1: "I", 4: "IV", 5: "V", 9: "IX",
        10: "X", 40: "XL", 50: "L", 90: "XC",
        100: "C", 400: "CD", 500: "D", 900: "CM",
        1000: "M"
    }
    
    result = ""
    for value, letter in sorted(roman_numeral_dict.items(), reverse=True):
        while num >= value:
            result += letter
            num -= value
    return result
def solve(left, right, equation):
    ans = []
    result = ""
    roman_numeral_dict = {1: "I", 5: "V", 10: "X"}
    for number in [left, right]:
        roman_letter = ""
        for i in range(len(number)):
            if number[i:i+2] == "10":
                roman_letter += "X"
                i += 1
            elif int(number[i]) in roman_numeral_dict:
                roman_letter += roman_numeral_dict[int(number[i])]
        ans.append(romanToInt(roman_letter))
    
    if(equation == "+"):
        answer =  ans[0] + ans[1]
    else:
        answer =  ans[0] * ans[1]
    answer = intToRoman(answer)
    for i in answer: 
        result += str(romanToInt(i))
    return result


print("[+] Welcome to the game")
print("[+] Answering 1000 questions below will get your flag")
print("[+] You have 3 seconds for each question. It's kinda hard but we belive in you!")
    

for i in range (1000):
    eq1=str(number[random.randint(1,2)])
    eq2=str(number[random.randint(1,2)])
    
    for j in range(random.randint(1,10)):
        eq1 += str(number[random.randint(0,2)])
    
    for j in range(random.randint(1,10)):
        eq2 += str(number[random.randint(0,2)])
    equation = random.choice(equations)
    try:
        inp = inputimeout(prompt=eq1 + " " + equation + " " + eq2 + " =", timeout=3)
        result = solve(eq1,eq2,equation)
        if(inp != result):
            print("[-] Nah, see you again!")
            exit()
        else:
            if(i == 175):
                print("[+] You're half a way, keep it up")
                continue
    except Exception: 
        print("[-] Time limit exceed!")
        exit()


print("[+] Good job, here is your flag: FIA{c0untry_r04d_t4k3_m3_r0me_2c50dde9bb0802ff427e306fdb229838}")
