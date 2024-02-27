from Crypto.Util.number import bytes_to_long, getPrime
from secret import flag


def RSA_encrypt(message):
    m = bytes_to_long(message)
    p = getPrime(1024)
    q = getPrime(1024)
    hint1 = p + q
    hint2 = (p -1)*(p-1)
    N = p * q
    e = 65537
    c = pow(m, e, N)
    return N, e, c,hint1,hint2


m=flag
N, e, c,hint1,hint2 = RSA_encrypt(m)
print(f"n = {N}")
print(f"e = {e}")
print(f"c = {c}")
print(f"hint1 = {hint1}")
print(f"hint2 = {hint2}")