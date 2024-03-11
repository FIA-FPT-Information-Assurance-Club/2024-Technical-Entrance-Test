



<font size="10">Symmetric Ciphers</font>

​		10<sup>th</sup> March 2024

​		Challenge Author(s): Randomteuz

​		

 



### Description:

So you want to become a member of FIACLUB? Better find the key for the key to solve this challenge!

### Objective

Find the original message that is encrypted

### Difficulty:

`easy`

### Flag:

`FIA{is_not_as_secured_as_I_thought}`



# Challenge

```
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
```

# Solver

Taking a look at the challenge code, it's a basic AES ECB mode with a redacted flag and the key.

Literally just use that key to decrypt the encrypted string to get the flag

```
from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad
import base64

key = 'Dwufzhfdwuthispa'

def decrypt(encrypted):
    cipher = AES.new(key.encode('utf-8'), AES.MODE_ECB)
    decrypted = cipher.decrypt(base64.b64decode(encrypted))
    return unpad(decrypted, AES.block_size).decode('utf-8')

encrypted_message = 'wIukL48oO66zaqOyIBmD8SpnrWw3Ba4tWCUF4PxWuiMNGtJXFlwfRURh17jfKa3O'
decrypted_flag = decrypt(encrypted_message)
print(decrypted_flag)

```
