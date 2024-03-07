from pwn import *
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



def equation(exp):
    ans = []
    roman_numeral_dict = {1: "I", 5: "V", 10: "X"}
    
    if '+' in exp:
        left, right = exp.split(" + ")
        for num_str in [left, right]:
            romanLetter = ""
            for i in range(len(num_str)):
                if num_str[i:i+2] == "10":
                    romanLetter += "X"
                    i += 1
                elif int(num_str[i]) in roman_numeral_dict:
                    romanLetter += roman_numeral_dict[int(num_str[i])]  
            ans.append(romanToInt(romanLetter))
        return ans[0] + ans[1]
    
    elif '*' in exp:
        left, right = exp.split(" * ")
        for num_str in [left, right]:
            romanLetter = ""
            for i in range(len(num_str)):
                if num_str[i:i+2] == "10":
                    romanLetter += "X"
                    i += 1
                elif int(num_str[i]) in roman_numeral_dict:
                    romanLetter += roman_numeral_dict[int(num_str[i])]
            ans.append(romanToInt(romanLetter))
        return ans[0] * ans[1]

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

def final(s):
    ans = ""
    for i in s: 
        ans += str(romanToInt(i))

    return ans
# a = equation("101010111 + 1015")
# print(a)
# print(intToRoman(47))
# print(final("XLVII"))

# Đổi thành romanian sau đó conver sang decimal cộng theo lại
# rồi convert lại romain sau đó convert lại decimal  

# io = remote("", )
# for i in range(500):
    exp = io.recv().strip().decode()[:-2]
    a = equation(exp)
    b = intToRoman(a)
    res = final(b)
    # res = str(eval(left))
    print(exp + "= " + res)
    io.send(res.encode() + b"\n")

# io.interactive()
exp = "11000010 * 1555000"
a = equation(exp)
b = intToRoman(a)
res = final(b)
# res = str(eval(left))
print(exp + "= " + res)
# io.send(res.encode() + b"\n")