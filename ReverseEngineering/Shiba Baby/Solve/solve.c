#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int main()
{
    FILE *file = fopen("shibapuppy.encrypted", "rb");
    FILE *output = fopen("result", "wb");
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    size = size - 4;
    srand(size);
    int partition = size / 3;
    for (int i = 0; i < partition; ++i)
    {
        int magic = fgetc(file) ^ (rand() % 256);
        fputc(magic, output);
    }

    FILE* output_r = fopen("result", "rb");
    unsigned char key[4];
    fread(key, sizeof(unsigned char), 4, output_r);
    fclose(output_r);

    for (int i = 0; i < partition; ++i)
    {
        int magic = fgetc(file) ^ key[i % 4];
        fputc(magic, output);
    }
    int zacian;
    int zamazenta;
    fread(&zacian, 2, 1, file);
    fseek(file, -2, SEEK_END);
    fread(&zamazenta, 2, 1, file);
    printf("%d\n", zacian);
    printf("%d\n", zamazenta);
    int seed = (zacian << 16) | zamazenta;
    srand(seed);
    fseek(file, 2 * partition+2, SEEK_SET);
    int byte;
    while ((byte = fgetc(file)) != EOF)
    {
        int magic = (rand() % 256) ^ byte;
        fputc(magic, output);
    }
}