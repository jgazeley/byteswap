#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void reverseBytes(uint8_t* buffer, int size);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
         printf("Usage: ./byteswap [path_to_file]\n");
         exit(1);
    }

    // backup input file as *.bak
    FILE* bak = fopen(argv[1], "rb");
    if (!bak)
    {
        char errmesg[500];
        sprintf(errmesg, "Can't open %s for reading", argv[1]);
        perror(errmesg);
        exit(1);
    }

    char backup[20];
    sprintf(backup, "%s.bak", argv[1]);
    fclose(bak);               // close file for rename()
    rename(argv[1], backup);   // add .bak to filename          

    bak = fopen(backup, "rb");

    // open output file
    FILE* out = fopen(argv[1], "wb");
    if (!out)
    {
        char errmesg[500];
        sprintf(errmesg, "Can't open %s for writing", "test.out");
        perror(errmesg);
        exit(1);
    }

    fseek(bak, 0, SEEK_END);    // find end of file
    long fsize = ftell(bak);    // determine file size
    rewind(bak);                // go back to start of file

    int dword = 4;   // double word = 4 bytes
    uint8_t* buffer = (uint8_t*) malloc(dword * sizeof(uint8_t));

    for(int i = 0; i < fsize / dword; i++)    
    {
        fread(buffer, dword, 1, bak);    // read a double word
        reverseBytes(buffer, dword);     // byte/word swap
        fwrite(buffer, dword, 1, out);   // write swapped bytess to output file
    }     

    free(buffer);
    fclose(bak);
    fclose(out);
}

// reverses the order of bytes (0xABCD1234 --> 0x3412CDAB)
void reverseBytes(uint8_t* buffer, int size)
{
    for (int i = 0; i < size / 2; i++)
    {
        int temp = buffer[size-1-i];
        buffer[size-1-i] = buffer[i];
        buffer[i] = temp;
    }
}