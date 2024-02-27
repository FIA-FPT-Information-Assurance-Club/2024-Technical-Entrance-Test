import base64 
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad,unpad

#AES ECB mode without IV

flag='FIA{is_not_as_secured_as_I_thought}'
key = 'Youdoneyourworks'

def encrypt(raw):
        raw = pad(raw.encode(),16)
        cipher = AES.new(key.encode('utf-8'), AES.MODE_ECB)
        return base64.b64encode(cipher.encrypt(raw))

def decrypt(enc):
        enc = base64.b64decode(enc)
        cipher = AES.new(key.encode('utf-8'), AES.MODE_ECB)
        return unpad(cipher.decrypt(enc),16)

encrypted = encrypt(flag)
print('encrypted ECB Base64:',encrypted.decode("utf-8", "ignore"))

decrypted = decrypt(encrypted)
print('data: ',decrypted.decode("utf-8", "ignore"))