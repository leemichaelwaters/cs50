#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Program should accept one command-line argument, the name of a forensic image from which to recover JPEGS.\n");
        return 1;
    }

    // open memory card
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("The forensic image cannot be opened for reading.\n");
        return 1;
    }

    typedef uint8_t BYTE;
    BYTE buffer[BLOCK_SIZE];
    char filename[8];  // "000.jpg\0"
    int img_count = 0;

    // read 512 bytes into buffer and repeat until end of card
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // look for beginning of jpeg
        // first three bytes: 0xff 0xd8 0xff
        // last byte: 0xe0, 0xe1, 0xe2, ..., 0xef
        if (buffer[0] == 0xff & buffer[1] == 0xd8 & buffer[2] == 0xff & (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", img_count);
            FILE *img = fopen(filename, "w");
            fwrite(buffer, 1, BLOCK_SIZE, img);
            fclose(img);
            img_count += 1;
        }
        else
        {
            if (img_count > 0)
            {
                FILE *img = fopen(filename, "a");
                fwrite(buffer, 1, BLOCK_SIZE, img);
                fclose(img);
            }
        }
    }
    fclose(raw_file);
}