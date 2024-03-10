from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
import base64 

flag='[REDACTED]'
key = 'Dwufzhfdwuthispa'

def encrypt(raw):
        raw = pad(raw.encode(),16)
        cipher = AES.new(key.encode('utf-8'), AES.MODE_ECB)
        return base64.b64encode(cipher.encrypt(raw))

encrypted = encrypt(flag)
print(encrypted)
#encrypted: wIukL48oO66zaqOyIBmD8SpnrWw3Ba4tWCUF4PxWuiMNGtJXFlwfRURh17jfKa3O