#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>

void processFile(const char* inputFilePath, const char* outputFilePath);
void stage1(FILE* inputFile, FILE* outputFile, int size);
void stage2(FILE* inputFile, FILE* outputFile, int size, unsigned char* tool);
void stage3(FILE* inputFile, FILE* outputFile);
void printBanner();
void misdirection1();
void misdirection2();
void misdirection3();
void misdirection4();
void misdirection5();
void misdirection6();
void misdirection7();
void misdirection8();

int main()
{
    char anon1667[] = "C:\\Users\\Shiba\\Album\\shibapuppy";
    char anonvn76[] = "C:\\Users\\Shiba\\Album\\shibapuppy.encrypted";
    printBanner();
    processFile(anon1667, anonvn76);
    printf("All gone, muahaha!!!\n");
    Sleep(5000);
    return 0;
}

void processFile(const char* inputFilePath, const char* outputFilePath)
{
    FILE* sourceFile = fopen(inputFilePath, "rb");
    FILE* destinationFile = fopen(outputFilePath, "wb");

    if (sourceFile == NULL && destinationFile == NULL)
    {
        perror("Cannot file the secret album!!!");
        return;
    }
    unsigned char signature[4];
    fread(signature, sizeof(unsigned char), 4, sourceFile);
    fseek(sourceFile, 0, SEEK_END);
    long sizefile = ftell(sourceFile);
    fseek(sourceFile, 0, SEEK_SET);

    stage1(sourceFile, destinationFile, sizefile);
    stage2(sourceFile, destinationFile, sizefile, signature);
    stage3(sourceFile, destinationFile);

    fclose(sourceFile);
    fclose(destinationFile);
}

void stage1(FILE* inputFile, FILE* outputFile, int size)
{
    srand(size);
    int partition_size = size / 3;
    for (int i = 0; i < partition_size; ++i)
    {
        int byte = fgetc(inputFile);
        int magic = byte ^ (rand() % 256);
        fputc(magic, outputFile);
    }
}

void stage2(FILE* inputFile, FILE* outputFile, int size, unsigned char* tool)
{
    int partition_size = size / 3;
    for (int i = 0; i < partition_size; ++i)
    {
        int magic = tool[i % 4] ^ fgetc(inputFile);
        fputc(magic, outputFile);
    }
}

void stage3(FILE* inputFile, FILE* outputFile)
{
    int tool = time(NULL);
    int byte;
    int zacian = (tool & 0xffff0000) >> 16;
    int zamazenta = tool & 0xffff;
    srand(tool);
    fwrite(&zacian, 2, 1, outputFile);
    while ((byte = fgetc(inputFile)) != EOF)
    {
        int magic = byte ^ (rand() % 256);
        fputc(magic, outputFile);
    }
    fwrite(&zamazenta, 2, 1, outputFile);
}

void misdirection1()
{
    return;
}
void misdirection2()
{
    return;
}
void misdirection3()
{
    return;
}
void misdirection4()
{
    return;
}
void misdirection5()
{
    return;
}
void misdirection6()
{
    return;
}
void misdirection7()
{
    return;
}
void misdirection8()
{
    return;
}

void printBanner()
{
    char a = 177, b = 219;
    system("color 0A");
    printf("\n");
    printf("  ______                             _      _____ _     _ _                      _ _                     \n");
    printf(" |  ____|                           | |    / ____| |   (_) |               /\\   | | |                    \n");
    printf(" | |__   _ __   ___ _ __ _   _ _ __ | |_  | (___ | |__  _| |__   __ _     /  \\  | | |__  _   _ _ __ ___  \n");
    printf(" |  __| | '_ \\ / __| '__| | | | '_ \\| __|  \\___ \\| '_ \\| | '_ \\ / _` |   / /\\ \\ | | '_ \\| | | | '_ ` _ \\ \n");
    printf(" | |____| | | | (__| |  | |_| | |_) | |_   ____) | | | | | |_) | (_| |  / ____ \\| | |_) | |_| | | | | | |\n");
    printf(" |______|_| |_|\\___|_|   \\__, | .__/ \\__| |_____/|_| |_|_|_.__/ \\__,_| /_/    \\_\\_|_.__/ \\__,_|_| |_| |_|\n");
    printf("                          __/ | |                                                                        \n");
    printf("                         |___/|_|                                                                        \n");
    printf("\n\n");
    printf("Loading ...\n\n");
    for (int i = 0; i < 26; i++)
    {
        printf("%c", a);
    }
    printf("\r");
    for (int i = 0; i < 26; i++)
    {
        printf("%c", b);
        Sleep(1000);
    }
    Sleep(5000);
    printf("\n");
}