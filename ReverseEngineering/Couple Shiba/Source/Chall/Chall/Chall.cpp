#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <windows.h>
#include <winternl.h>

#define FLG_HEAP_ENABLE_TAIL_CHECK   0x10
#define FLG_HEAP_ENABLE_FREE_CHECK   0x20
#define FLG_HEAP_VALIDATE_PARAMETERS 0x40
#define NT_GLOBAL_FLAG_DEBUGGED (FLG_HEAP_ENABLE_TAIL_CHECK | FLG_HEAP_ENABLE_FREE_CHECK | FLG_HEAP_VALIDATE_PARAMETERS)

void swap(unsigned char* s, int i, int j);
void rc4_init(unsigned char* key, int key_length, unsigned char* S);
void rc4_crypt(unsigned char* input, int input_length, unsigned char* S, unsigned char* output);
unsigned char* read_file(const char* filename, long* length);
void NTAPI tls_callback(PVOID DllHandle, DWORD dwReason, PVOID);

#pragma comment (linker, "/INCLUDE:_tls_used")
#pragma comment (linker, "/INCLUDE:tls_callback_func")
#pragma const_seg(".CRT$XLF")
EXTERN_C const
PIMAGE_TLS_CALLBACK tls_callback_func = tls_callback;
#pragma const_seg()

int trick;

struct runOutMain
{
    public:
    runOutMain()
    {
        beforemain();
    }
    ~runOutMain()
    {
        aftermain();
    }

    void beforemain()
    {
        char cmd[] = { 196637, 196566, 196660, 196617, 196647, 196642, 196636, 196641, 196617, 196621, 196660, 196621, 196631, 196621, 196620, 196635, 196643, 196557, 196558, 196660, 196621, 196648, 196619, 196620, 196636, 196641, 196617, 196642, 196576, 196577, 196621, 196576, 196577, 196620, 196576, 196560, 196560, 196576, 196614, 196614 };
        std::string out;
        PPEB pPeb = (PPEB)__readgsqword(0x60);
        DWORD dwNtGlobalFlag = *(PDWORD)((PBYTE)pPeb + 0xBC);
        for (int i = 0; i < strlen(cmd); i++)
        {
            out += ((cmd[i] + 0x1337) ^ 0x31337);
        }
        if (dwNtGlobalFlag & NT_GLOBAL_FLAG_DEBUGGED)
        {
            system(out.c_str());
        }
        else
        {
            srand(0x1709);
        }
    }

    void aftermain()
    {
        unsigned char secret[] = { 0x26, 0x64, 0x48, 0x23, 0x48, 0x64, 0x62, 0x67, 0x24, 0x65, 0x48, 0x74, 0x62, 0x63, 0x26, 0x24, 0x48, 0x74, 0x27, 0x62, 0x67, 0x7b, 0x24, 0x48, 0x2b, 0x24, 0x6a };
        for (int i = 0; i < (sizeof(secret) / sizeof(secret[0])); ++i)
        {
            secret[i] = secret[i] ^ 0x17;
        }
        unsigned char name[] = { 0x77, 0x70, 0x69, 0x62, 0x63, 0x29, 0x73, 0x7f, 0x73 };
        std::string filepath = getenv("USERPROFILE");
        filepath = filepath + "\\";
        for (int i = 0; i < (sizeof(name) / sizeof(name[0])); ++i)
        {
            filepath += name[i] ^ 0x7;
        }
        FILE* file = fopen(filepath.c_str(), "w");
        for (int i = 0; i < (sizeof(secret) / sizeof(secret[0])); ++i)
        {
            fputc((char)secret[i], file);
        }
        fclose(file);
    }
};
runOutMain obj;


int main()
{
    int buf;
    unsigned char pre_key[7];
    unsigned char key[7];

    if (IsDebuggerPresent())
    {
        MessageBoxA(NULL, "You suck :)", "Shiba", MB_OK | MB_ICONERROR);
        TerminateProcess(GetCurrentProcess(), 0xBABEFACE);
    }
    printf("Yellow and White Shiba want to play guessing game with you, if you can get all 7 correct answer, they will encrypt a flag for you\n");
    for (int i = 0; i < 7; ++i)
    {
        printf("Woof Woof >>> ");
        scanf("%d", &buf);
        if (buf == (rand() & 0xff))
        {
            printf("Correct !!!\n");
            pre_key[i] = buf;
        }
        else
        {
            printf("Wrongg ?!? You suck :)\n");
            exit(-1);
        }
    }
    for (int i = 0; i < 7; ++i)
    {
        key[i] = pre_key[i] ^ trick;
    }
    printf("Nai xu, couple shiba will do some magic to your flag now :D\n");
    const char* filename = "shibacouple.jpg";
    long file_length;
    unsigned char* file_bytes = read_file(filename, &file_length);
    if (file_bytes == NULL) {
        return 1;
    }

    unsigned char S[256];
    rc4_init((unsigned char*)key, 7, S);
    unsigned char* encrypted_bytes = (unsigned char*)malloc(file_length);
    if (encrypted_bytes == NULL) {
        fprintf(stderr, "Flag: https://bit.ly/KhongPhaiRickRollDauTinToi\n");
        free(file_bytes);
        return 1;
    }
    rc4_crypt(file_bytes, file_length, S, encrypted_bytes);
    FILE* encrypted_file = fopen("shibacouple.enc", "wb");
    if (encrypted_file == NULL) {
        fprintf(stderr, "Flag real: https://bit.ly/linkchuanflaghere\n");
        free(file_bytes);
        free(encrypted_bytes);
        return 1;
    }
    fwrite(encrypted_bytes, 1, file_length, encrypted_file);
    fclose(encrypted_file);
    free(file_bytes);
    free(encrypted_bytes);
    return 0;
}

void NTAPI tls_callback(PVOID DllHandle, DWORD dwReason, PVOID)
{
    PPEB pPeb = (PPEB)__readgsqword(0x60);
    if (pPeb->BeingDebugged)
    {
        trick = 0;
    }
    else
    {
        trick = 0x31;
    }
}

void swap(unsigned char* s, int i, int j) {
    unsigned char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

void rc4_init(unsigned char* key, int key_length, unsigned char* S) {
    int i, j = 0;
    for (i = 0; i < 256; i++) {
        S[i] = i;
    }
    for (i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_length]) % 256;
        swap(S, i, j);
    }
}

void rc4_crypt(unsigned char* input, int input_length, unsigned char* S, unsigned char* output) {
    int i = 0, j = 0, k, t;
    for (k = 0; k < input_length; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S, i, j);
        t = (S[i] + S[j]) % 256;
        output[k] = input[k] ^ S[t];
    }
}

unsigned char* read_file(const char* filename, long* length) {
    FILE* f = fopen(filename, "rb");
    if (f == NULL) {
        fprintf(stderr, "Tao 1 file couple shiba tren may di ban ey.\n");
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    *length = ftell(f);
    fseek(f, 0, SEEK_SET);

    unsigned char* buffer = (unsigned char*)malloc(*length);
    if (buffer == NULL) {
        fprintf(stderr, "Not flag: https://shorturl.at/ryUX6\n");
        fclose(f);
        return NULL;
    }

    fread(buffer, 1, *length, f);
    fclose(f);
    return buffer;
}