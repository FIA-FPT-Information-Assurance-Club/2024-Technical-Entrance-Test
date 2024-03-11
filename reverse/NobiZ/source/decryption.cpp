#include <windows.h>
#include <wincrypt.h>
#include <cstdio>
// Function to encrypt a file
bool EncryptFile(const char* inputFile, const char* outputFile, const BYTE* key, DWORD keySize) {
    HCRYPTPROV hCryptProv = NULL;
    HCRYPTKEY hKey = NULL;
    HANDLE hInFile, hOutFile;
    DWORD bytesRead, bytesWritten;
    BYTE buffer[1024];

    if (!CryptAcquireContext(&hCryptProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        return false;
    }

    if (!CryptImportKey(hCryptProv, key, keySize, 0, 0, &hKey)) {
        CryptReleaseContext(hCryptProv, 0);
        return false;
    }

    hInFile = CreateFile(inputFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    hOutFile = CreateFile(outputFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    while (ReadFile(hInFile, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0) {
        if (!CryptDecrypt(hKey, 0, TRUE, 0, buffer, &bytesRead)) {
            CryptReleaseContext(hCryptProv, 0);
            CloseHandle(hInFile);
            CloseHandle(hOutFile);
            return false;
        }
        WriteFile(hOutFile, buffer, bytesRead, &bytesWritten, NULL);
    }

    CryptDestroyKey(hKey);
    CryptReleaseContext(hCryptProv, 0);
    CloseHandle(hInFile);
    CloseHandle(hOutFile);

    return true;
}

int main() {
    const char* inputFile = "encrypted.txt";
    const char* encryptedFile = "decrypted.txt";
    const BYTE key[] = {0x07,0x02,0x00,0x00,0x00,0xA4,0x00,0x00,0x52,0x53,0x41,0x32,0x00,0x10,0x00,0x00,0x01,0x00,0x01,0x00,0xB5,0xB4,0xDC,0x55,0xFE,0x6B,0xC0,0x05,0x65,0xD1,0xD0,0x07,0x5F,0xDF,0xFA,0x18,0x40,0xE0,0xD5,0xC2,0xD2,0xF8,0xFB,0xDA,0x37,0xF7,0x1D,0xD6,0x90,0x8C,0xE6,0xC0,0x67,0x33,0x91,0xAA,0x3E,0x9A,0x99,0xFA,0x21,0x41,0x64,0xE0,0x41,0x78,0x10,0xB7,0x36,0x17,0x59,0x6F,0xA1,0xD3,0x7E,0x5B,0x0B,0xC6,0xBF,0xF5,0x89,0xFB,0x6F,0xF4,0xE8,0xC2,0xEC,0x96,0xD6,0x98,0xCD,0xFD,0x58,0xFB,0xA5,0xDF,0xD8,0x15,0x40,0x6F,0x34,0x7D,0xF1,0xFB,0xE1,0xEB,0x4E,0xD2,0x4E,0x63,0x70,0x5E,0x68,0x8E,0x42,0x1E,0xAD,0x7E,0x85,0x40,0xFE,0x84,0xAD,0xB6,0xE0,0xA4,0x60,0x60,0xBB,0x01,0xC8,0xF3,0x36,0x35,0x84,0xE1,0xD0,0x58,0x1B,0xBE,0x58,0xCC,0x27,0x75,0x7C,0xC5,0xB1,0xE4,0xDE,0x3A,0x4B,0x8C,0xD8,0x35,0x24,0x8A,0x88,0x84,0x74,0x59,0x21,0xA2,0x3B,0xD7,0x82,0xB2,0x17,0x00,0x89,0x83,0xE0,0x70,0x54,0xE3,0xDF,0x5C,0x55,0x67,0x19,0x49,0xE6,0x44,0xA0,0x20,0x22,0x3A,0x53,0x9A,0xBF,0xCD,0x4C,0x73,0x39,0x5A,0x53,0xA2,0xDE,0xA5,0xFC,0x1C,0x5F,0x5C,0x83,0xBF,0x98,0x6E,0xBC,0x21,0x2F,0x2F,0x50,0x77,0x79,0xF3,0x4B,0x0D,0xB0,0xE1,0xFC,0xE7,0x8E,0xD5,0xDA,0x46,0x89,0xAE,0x53,0x4F,0x5C,0xB0,0x63,0xFA,0x3F,0x62,0x4F,0x88,0xE0,0x27,0x4D,0x61,0xB0,0x1E,0xDE,0x74,0x60,0x81,0xDD,0xB5,0x52,0x74,0x0E,0x28,0x91,0x18,0xBA,0x5C,0x94,0x99,0x45,0x8A,0xBB,0xCD,0x89,0xE0,0x0D,0xCC,0x2F,0x91,0x0D,0xA4,0xBF,0x50,0xDC,0xBC,0x45,0x0B,0x42,0xAE,0x32,0xAB,0x1F,0x15,0xC1,0x29,0xA3,0x7C,0x55,0x24,0x95,0xB9,0x7D,0x17,0x03,0x32,0x81,0xC6,0x63,0x08,0x32,0xEE,0x37,0x29,0xBE,0x91,0xC2,0x26,0x54,0xC8,0x34,0x47,0x41,0x2C,0x51,0xFB,0x70,0x8A,0x0C,0x35,0x3A,0xE3,0x35,0x64,0x2A,0x4D,0xB9,0xF2,0xD8,0x02,0x8A,0xFE,0xBF,0xD0,0x54,0x7F,0xDE,0x35,0xBF,0xCC,0xD1,0x25,0xEC,0x42,0x93,0xBE,0x0C,0xAE,0x17,0x0E,0xB8,0x06,0x64,0x3B,0x30,0x7A,0x37,0x14,0x18,0x83,0x6A,0x5B,0xD7,0xB7,0x21,0x47,0x18,0xEC,0xF1,0x93,0x75,0xBC,0xD2,0x31,0x92,0x48,0xB2,0x8E,0x1F,0xB5,0x78,0x10,0x0B,0x10,0x7D,0x22,0x89,0xF0,0x5A,0x83,0xC4,0x04,0xAF,0xA5,0x44,0x90,0xC1,0xB6,0x82,0xBB,0x03,0x09,0x45,0x87,0xEC,0x49,0xE4,0x46,0x58,0x70,0x96,0x07,0x6D,0x93,0xAD,0xB6,0x47,0x4B,0xDE,0x11,0x23,0x44,0x67,0x67,0x3E,0xE0,0x59,0x5B,0xCD,0x6C,0x56,0x78,0xD4,0x3B,0x17,0xBA,0x9C,0xA1,0x40,0x86,0x16,0xFB,0xA7,0x5C,0xDC,0x4C,0x80,0x09,0xBF,0xDD,0xB4,0xA8,0x0B,0xE5,0xD4,0x44,0x0E,0x5E,0xBD,0xC4,0xD0,0x40,0x52,0x0D,0x42,0x13,0x10,0x2E,0xF7,0xA6,0xA1,0xE0,0x40,0xB1,0xB9,0x71,0x72,0xDF,0xF1,0x92,0x85,0xCA,0x2A,0x66,0xC6,0xA3,0x13,0x89,0x2E,0xBB,0x1D,0x32,0xE9,0x1E,0xDD,0x2B,0x46,0xE3,0xDE,0xF9,0x9A,0xE3,0x4F,0xE2,0x9B,0x02,0xE8,0x31,0x90,0xB7,0x58,0x97,0x9F,0x43,0x0F,0x51,0x36,0xD9,0xAE,0x58,0xAC,0x18,0xFC,0x0E,0x13,0xB0,0x79,0xBA,0xD3,0xBD,0x9F,0x58,0x55,0xB1,0x0F,0xF2,0x0C,0x24,0x49,0x55,0xB1,0xB7,0xBF,0x03,0xE3,0xD1,0xA4,0xEF,0xB5,0x3F,0x7C,0x75,0x58,0x48,0xAA,0x97,0x12,0x35,0xA0,0xEE,0x63,0x22,0x29,0x0D,0xD8,0x1A,0x57,0x58,0x7F,0x58,0xC0,0x4E,0x50,0xF2,0xA8,0x1D,0x0F,0x65,0xB5,0xE7,0x14,0x38,0x73,0x45,0x47,0x4D,0x0B,0x4D,0x49,0x0F,0xD4,0x06,0x96,0xB7,0xE0,0x4E,0x84,0xC6,0x64,0x26,0x34,0xCD,0xA8,0x64,0xFD,0xE2,0x51,0xE2,0x46,0x70,0x46,0x04,0x65,0x03,0x72,0xEC,0xC7,0x4B,0x60,0xB8,0x41,0x3A,0x6A,0x60,0x12,0xE3,0x67,0x77,0x17,0x0C,0x63,0x76,0x99,0xEB,0x04,0x1E,0xDD,0x8D,0x62,0xBC,0xAA,0x96,0xE6,0x6A,0x1F,0xEE,0xFE,0x91,0x89,0xA7,0x95,0x35,0x6A,0x19,0xCC,0x22,0x0D,0x37,0x60,0xFC,0x92,0x33,0xF4,0x06,0x38,0x1E,0xEA,0x9C,0x9C,0x2A,0x5D,0x39,0xD4,0xF9,0xE7,0xBA,0x79,0xDD,0x6E,0x0E,0xEB,0x76,0x34,0x28,0x4E,0x85,0xDF,0xE2,0xA4,0xC6,0x47,0x42,0x98,0x28,0xD0,0x37,0xDB,0x38,0x35,0xDD,0x36,0x3B,0x44,0x2B,0x59,0x21,0x18,0x31,0x31,0xA1,0xD3,0xB6,0x9D,0x25,0x0B,0xDC,0x0F,0x5F,0x88,0x21,0x67,0xB5,0x54,0xF4,0x3D,0xDE,0x16,0x84,0xAB,0xE8,0x94,0x85,0x83,0x99,0xD0,0xA3,0xA9,0x1D,0x0E,0x34,0x40,0x03,0xE0,0x11,0x59,0x3B,0x69,0x90,0x01,0xA4,0x3B,0x6F,0x90,0xD7,0x50,0xC0,0xD9,0x50,0x7E,0x55,0x79,0x2B,0x4E,0xB8,0x36,0x9D,0x41,0x7D,0xC8,0xC2,0x59,0xD1,0xCB,0x84,0xE2,0xD6,0xB9,0xCD,0x07,0x77,0xA5,0x2D,0x61,0x68,0x81,0x22,0x12,0x31,0x14,0xC9,0xFB,0xA0,0xFE,0x95,0xAB,0x57,0x02,0x1A,0x04,0x0B,0xC4,0xB4,0xDB,0x36,0x8B,0x58,0x00,0x35,0xF2,0x4C,0xAD,0xEB,0x75,0x7B,0x49,0xE7,0x85,0x27,0x51,0x14,0x14,0x90,0xF6,0xB8,0x8B,0xDC,0x69,0xA1,0x36,0x62,0xCB,0x63,0x3A,0x94,0x9D,0xDF,0x25,0x33,0x8E,0xFB,0x87,0x47,0xAB,0x75,0xF8,0xEB,0x2C,0xB5,0x91,0x9C,0xA0,0xD2,0xE2,0x06,0xB5,0xAD,0x32,0x73,0x9C,0x50,0x28,0x44,0x53,0x35,0xFA,0x7A,0x32,0x83,0x67,0x39,0x20,0x47,0x7D,0xA8,0x96,0x4D,0x03,0xC1,0x7E,0xD1,0xF5,0xA8,0x5E,0x11,0xF0,0x44,0x19,0x1D,0x03,0xC7,0xBB,0xFD,0x13,0x75,0xD8,0xC3,0xFE,0xF4,0xFE,0xBD,0xBB,0x24,0xC6,0x75,0xAA,0x7B,0x4B,0x8B,0xB9,0xA6,0x62,0x43,0xE5,0x63,0x0E,0xC8,0xEC,0xC6,0x25,0x5C,0x4A,0xAF,0xA0,0x37,0x86,0x87,0xB7,0x07,0x61,0x17,0x8F,0xC0,0x37,0xA0,0xE0,0x6F,0x09,0x78,0x10,0x63,0x6A,0xAC,0x1E,0xB3,0x7C,0x1A,0xD7,0xB3,0x7C,0x6B,0x1A,0x75,0x34,0x94,0x5F,0xAB,0xD7,0x39,0xF5,0x03,0xFB,0x2D,0x38,0x30,0x5C,0xF0,0x35,0x15,0x2E,0xE8,0xC4,0x8D,0xEA,0x2B,0x7C,0x6C,0xB4,0x94,0x5B,0x7F,0x81,0x1A,0xFF,0x96,0xD5,0xBD,0xBC,0x9E,0x89,0x5C,0xD8,0x45,0xE9,0x48,0xCE,0x2B,0x70,0x5F,0xA2,0x93,0x37,0xFC,0x27,0x7A,0xA1,0xEE,0x27,0x08,0xA8,0x3B,0x5F,0x1A,0xC3,0xE1,0x1E,0xC9,0x3D,0x50,0x52,0x84,0xEB,0x31,0xC2,0x27,0xCC,0x15,0xF7,0x62,0x54,0xA4,0x10,0xD1,0xB0,0x4B,0x33,0xCA,0xA1,0x4F,0x9C,0x64,0x71,0xC8,0x62,0xD3,0xC4,0xE1,0xAB,0xCB,0x50,0x4C,0xB9,0x97,0x51,0xCA,0xE8,0x3A,0x4D,0x13,0x6E,0x9D,0xFB,0xCC,0x11,0xA6,0xBC,0x48,0xCE,0x74,0x37,0x4E,0x4F,0xAD,0xE1,0xE1,0x8A,0x40,0xD2,0xF7,0x00,0x24,0x3C,0x08,0x22,0x16,0xA4,0x3F,0x5D,0x90,0xB8,0x29,0x27,0xD1,0x31,0x75,0xCD,0xAE,0xAA,0xB7,0xF2,0xE0,0xB7,0xCF,0x2F,0x31,0x2C,0xCA,0x9C,0x83,0xDD,0x27,0x9F,0x14,0xAC,0x88,0x9B,0xC0,0xCF,0xB5,0xF9,0x9D,0x6E,0xA7,0xC5,0x04,0xDB,0x3C,0x84,0xB5,0x37,0x49,0x86,0xD0,0x3C,0x77,0x07,0x06,0xB7,0x1D,0xE4,0xA4,0x56,0x07,0x9B,0xDA,0xE2,0x4D,0x2E,0x39,0x16,0xE1,0x8C,0xF4,0xAF,0xDC,0x12,0x28,0xE8,0x9A,0x79,0xCE,0x74,0xAE,0xB5,0xFF,0x10,0xE5,0x4F,0x7D,0x16,0xB8,0x2A,0x1E,0x99,0x0B,0xCB,0xF8,0x0E,0xBD,0xC2,0x00,0x4D,0xFF,0xDF,0x86,0x77,0x32,0xA4,0xCB,0xAA,0xFD,0x96,0x80,0xB2,0xFE,0xC1,0xAB,0xB1,0x87,0x43,0x9D,0x28,0x65,0xD5,0x80,0x77,0xB8,0x4C,0x31,0xB7,0x3E,0xA2,0x5B,0xC4,0x12,0x45,0x28,0x59,0x19,0xD9,0xC0,0xA7,0x22,0xFF,0x9B,0xAF,0xE7,0x4B,0x00,0x07,0xB6,0x96,0xCF,0x6B,0x9C,0x17,0x89,0x6A,0xDA,0x61,0xC7,0x0E,0x15,0x82,0xFA,0x93,0x53,0x8D,0x2E,0x11,0x26,0xC2,0x01,0xE2,0xBE,0x2B,0x11,0x7A,0xEB,0x57,0x63,0xCF,0xB3,0x29,0xE8,0xA0,0x45,0x5C,0x60,0x1D,0x3F,0x44,0x5F,0x46,0x88,0x9E,0x06,0x36,0xF2,0x41,0xCA,0xAA,0xC5,0x26,0xFD,0x62,0xD5,0xF9,0x68,0xFC,0x15,0x8C,0xE3,0x90,0x82,0xEC,0x4F,0xD2,0x44,0xAB,0x1A,0x3A,0x96,0x6F,0x1C,0xCE,0x91,0x96,0xED,0xD6,0xDC,0x27,0x3E,0xC7,0x63,0x21,0x3A,0xD7,0x67,0x6E,0x1C,0x37,0xBC,0xF3,0x37,0x60,0x1C,0x33,0xC7,0x77,0x4B,0xDE,0x19,0xEB,0x09,0x1D,0xE8,0x9F,0x7C,0x31,0xB6,0xE2,0xEE,0x15,0x17,0x1A,0x39,0xE2,0xF8,0x6D,0xD1,0x43,0x3B,0x75,0x17,0xE8,0x20,0x88,0x76,0x50,0x51,0x66,0xD8,0x61,0xB9,0x6D,0x53,0x57,0xA7,0xDD,0x46,0x74,0x84,0xF2,0x3F,0xF7,0x2B,0xE9,0x14,0xF1,0xF3,0xBD,0x09,0xCC,0x9B,0x5B,0x18,0xD3,0xF9,0x1E,0x6D,0x1A,0x21,0xB4,0x50,0x05,0x7B,0x1A,0x5F,0xF5,0x5A,0x93,0x89,0xA3,0x38,0xA4,0x50,0x2C,0x56,0xBE,0xC3,0xDC,0x85,0x8E,0xED,0xB9,0x99,0x57,0xD8,0xD7,0xCE,0xB5,0xBD,0x1E,0xD2,0xAD,0x18,0x09,0x4E,0xF1,0x2F,0xFA,0xCA,0x2D,0xCF,0x7B,0xB9,0x00,0x9B,0x70,0xFB,0xB1,0x61,0x12,0x1A,0xE1,0x3D,0x30,0xDD,0xC2,0x83,0xF4,0xD3,0x7C,0xF8,0xF0,0x49,0xE9,0x01,0x02,0xE3,0x25,0x1C,0xE7,0x21,0x00,0xAF,0xBF,0xCD,0x28,0x66,0xCF,0x1C,0x0C,0xD4,0xF6,0x61,0x69,0x3C,0x23,0x77,0xD4,0xA6,0x33,0xA3,0xB7,0xD9,0x38,0xAF,0x8D,0xFF,0x5B,0x4A,0x83,0x06,0xE2,0x9D,0xEC,0x41,0x30,0x8B,0xFC,0x76,0x7F,0x2B,0x62,0xDE,0x38,0xB8,0x87,0xDC,0x0A,0x76,0xFF,0xE2,0xE0,0xDF,0x2D,0x63,0xFA,0x83,0x6C,0x28,0x0D,0xBC,0x95,0xC7,0x4C,0x53,0xD3,0x9E,0x69,0x93,0x4A,0xE3,0x7E,0x90,0xA1,0x5E,0xB0,0x49,0xF4,0x27,0x68,0x0C,0xA9,0x82,0x0C,0xF3,0xB3,0x54,0xA5,0xA3,0xC7,0x6F,0x3E,0xDE,0x08,0x5F,0xA5,0x57,0xBA,0x51,0xFB,0xD6,0x4B,0x10,0xF4,0x62,0x94,0x08,0x0D,0x34,0xAC,0x6A,0x58,0x4B,0xC0,0x15,0xE7,0xDD,0x29,0xD2,0xFD,0x95,0x9C,0x5A,0x4F,0xE2,0x6C,0x29,0xEB,0xD4,0x7A,0xA0,0xDA,0x69,0xE7,0x45,0x53,0xDB,0x06,0x52,0x5F,0x81,0x31,0xCD,0x1A,0x8C,0x35,0x92,0x62,0x8B,0x09,0xBC,0xCF,0x57,0xC2,0x0A,0x61,0x04,0x73,0x5B,0xAF,0xBB,0xA5,0xA5,0x80,0xE8,0x3A,0xC1,0x80,0xB5,0x51,0x1E,0x23,0x41,0xC3,0xC1,0x0A,0x80,0x52,0xC5,0xB1,0x91,0x84,0xDC,0xED,0x28,0xB2,0xC1,0x39,0x36,0x81,0x15,0xB8,0x94,0x31,0x49,0x19,0xDE,0x0A,0xD0,0x0F,0xA2,0x5C,0xFA,0xAA,0xD2,0x02,0x82,0xB7,0x3E,0x37,0x56,0x9D,0x3F,0x4B,0x96,0xD6,0x0F,0x87,0x69,0x87,0x10,0x00,0xFB,0x18,0x9D,0xD2,0xE8,0xFA,0xC4,0x51,0x4D,0x64,0x69,0x7D,0x07,0xEC,0xE3,0x96,0x63,0xD2,0x2F,0x09,0xA2,0x15,0x75,0xCB,0x68,0x37,0x5F,0xB4,0xE4,0x49,0x55,0xCF,0x5B,0x85,0x8B,0x8E,0x15,0x65,0x28,0xB7,0x5B,0x73,0x65,0x18,0x5A,0x71,0xEE,0xB3,0xEF,0xF0,0x9A,0x31,0xE9,0x53,0x0E,0xDC,0xFA,0x96,0x53,0x3D,0xCA,0xB0,0x7D,0x47,0x55,0xC9,0x55,0xA7,0x40,0x18,0x9D,0xFE,0x7C,0x8D,0xC8,0x74,0xE3,0x7D,0x96,0x82,0xA5,0x88,0xF4,0x15,0xB6,0x87,0x14,0x30,0x60,0x89,0x02,0x7D,0xEE,0x51,0xE3,0x4F,0x4F,0xFE,0x00,0x4D,0x09,0x92,0x61,0x3B,0x9F,0xBB,0xDE,0xC9,0x05,0x2A,0x0C,0x3F,0x25,0x53,0xC1,0xD7,0x23,0x6A,0xAE,0x44,0x3A,0x2B,0xFA,0xC7,0xAF,0xCA,0xC4,0xD6,0x26,0xF9,0xDF,0x9A,0x45,0xC0,0xBC,0xF9,0xFB,0x2C,0xE4,0x9B,0x99,0xA6,0xB2,0xAD,0xFF,0x70,0x0C,0x4B,0x1E,0xB2,0x5F,0x4B,0x91,0x52,0xDA,0x34,0x57,0x9E,0xB2,0x3B,0x4F,0xD9,0x24,0x41,0x2C,0x7D,0x96,0x0A,0x26,0xDC,0x0C,0xF0,0xB2,0x73,0x00,0x47,0xDC,0x38,0x53,0x82,0x6E,0x25,0x7F,0x76,0x4B,0x41,0xEF,0x6F,0x81,0x0A,0xC3,0x98,0x56,0x5E,0x21,0xC8,0x49,0x38,0x6E,0x21,0x24,0xE5,0x11,0x9C,0x0F,0xE9,0x62,0x96,0x6D,0x0B,0x67,0xCB,0x42,0xFA,0x48,0x8A,0x57,0x8D,0x73,0xC8,0x88,0x04,0xA8,0x9B,0xCE,0x1D,0x96,0xF5,0xB4,0x83,0xAD,0xA3,0xFF,0xF5,0x61,0x14,0xBD,0xF0,0x67,0x9B,0xE3,0x5C,0x7F,0x12,0xFF,0x61,0x50,0xFA,0x7E,0xC5,0x45,0x21,0xE2,0xFF,0x38,0x7C,0x71,0xD0,0xAF,0xE9,0xF9,0xA1,0xAE,0x75,0x1D,0xE8,0xFA,0x22,0xBE,0xE2,0x71,0xF7,0x07,0x1E,0xBD,0x14,0x4B,0x00,0x4C,0x3E,0xA0,0x15,0xCC,0xA3,0x5E,0x2E,0x6C,0x40,0x9A,0x21,0x29,0x2C,0x78,0x14,0xEC,0xEE,0x80,0x24,0x5C,0xCC,0x32,0xA6,0x39,0x4B,0xBA,0xA9,0x6A,0xE9,0x29,0xB3,0x48,0x37,0xCF,0x0A,0x44,0x1C,0x6A,0x43,0xB8,0x29,0x7D,0xDC,0x6D,0x34,0x8B,0xA0,0x55,0x3D,0xDD,0x9B,0x5F,0x2E,0x2E,0x81,0xAF,0x2F,0x84,0xA4,0x01,0xAC,0xEA,0x9D,0x69,0xF9,0xB4,0x29,0x03,0x50,0x0C,0x54,0x8C,0x02,0x90,0x31,0xC7,0x70,0xC6,0x9C,0x76,0x8D,0xA0,0x09,0x3B,0x94,0x01,0xAC,0x2F,0x0B,0x56,0xC9,0x1F,0x86,0x1D,0x99,0xF4,0x71,0xF6,0x94,0x83,0x9C,0x39,0xE4,0xDF,0x73,0x9A,0x1D,0x6C,0x43,0xA4,0x28,0x18,0xFA,0xB9,0xB6,0x02,0x70,0x66,0x34,0xAC,0xF9,0x9B,0x16,0x25,0x8B,0xB2,0x4B,0x45,0xC2,0x51,0xD6,0x0F,0x63,0x80,0xDB,0xD0,0x51,0xEB,0x41,0xCC,0x13,0xD6,0x17,0x59,0xD7,0xCC,0x1E,0x45,0x91,0x2B,0x3E,0x0E,0x33,0x0C,0x09,0xB7,0x1B,0x63,0x6E,0xA2,0x28,0x18,0xEA,0x43,0x34,0x99,0x60,0xBC,0xC5,0x97,0x41,0xF8,0x7C,0x50,0xF3,0x8B,0x6F,0xE0,0x07,0xA4,0xCF,0xC9,0x0F,0x66,0x44,0xB1,0xC3,0xBC,0x6A,0xFB,0xFD,0x62,0x42,0x74,0x7D,0x23,0x70,0x9F,0x7B,0x37,0xFF,0x69,0x9E,0xF8,0x6A,0xC3,0x3F,0x27,0xC5,0xAA,0xBB,0xD9,0xD4,0x42,0xF1,0x8A,0xCA,0x89,0x71,0xC9,0xEC,0xDF,0xB1,0x83,0x27,0xCD,0xA5,0xBE,0x97,0xDE,0xE7,0x78,0xD4,0xA9,0xE0,0xE8,0x38,0x75,0x3F,0x98,0x6C,0x61,0xDC,0x7B,0xC6,0xEE,0xEA,0xA5,0xE4,0x9A,0xA3,0xCF,0x52,0xD0,0xC8,0x8A,0xD1,0xDA,0xF1,0x2B,0x0D,0x4E,0x2E,0xCF,0x16,0x8D,0x16,0x92,0x07,0x14,0xF9,0x68,0x97,0x15,0x4A,0x21,0xA7,0x32,0x44,0x89,0x12,0xDC,0xA4,0x2B,0xE8,0x83,0xC1,0xDB,0xED,0xB1,0x86,0xBD,0x39,0x76,0x65,0x79,0x02,0x9E,0xBA,0xD5,0xB4,0xEE,0xE0,0x98,0x4B,0xF8,0xC0,0x48,0x2B,0x31,0x02,0x13,0xFF,0x32,0x15,0x53,0x3B,0xC8,0x31,0x91,0x10,0x00,0x83,0x3D,0x2C,0xA7,0x34,0xDC,0xD7,0xDC,0x97,0x9B,0x41,0x74,0xEE,0x6D,0xC8,0x9B,0x81,0x9E,0x8C,0xBA,0xB9,0x61,0x81,0xDE,0xBA,0xFD,0x7B,0xCF,0xFA,0xE7,0x68,0xD7,0xF0,0x9A,0xC7,0x5C,0x3F,0x16,0x78,0x6E}; // Replace with your encryption key
    DWORD keySize = 4096;

    // Encrypt the file
    if (EncryptFile(inputFile, encryptedFile, key, keySize)) {
    	printf("File decrypted successfully.\n");
    } else {
    	printf("Decryption failed.\n");
        return 1;
    }

    return 0;
}