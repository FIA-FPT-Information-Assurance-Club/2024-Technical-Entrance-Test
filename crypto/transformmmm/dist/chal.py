from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import base64 

flag='[REDACTED]'
key = 'Unlgjqwtwdnvfufv'

def encrypt(raw):
        raw = pad(raw.encode(),16)
        cipher = AES.new(key.encode('utf-8'), AES.MODE_ECB)
        return base64.b64encode(cipher.encrypt(raw))

encrypted = encrypt(flag)
print(encrypted)
#encrypted: vFRlEU8WZEuEZz05XPRx0Yi9LkjndH6VxLJkwReOney7NeUylpK8QsULAo8lyqAe