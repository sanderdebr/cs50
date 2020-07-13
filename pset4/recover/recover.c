#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK 512

typedef uint8_t BYTE;

// Prototypes
char *generateName();

int main(int argc, char *argv[])
{
    // Check if one argument is given
    if (argc != 2) {
        printf("Correct usage: ./recover image.raw");
        return 1;
    }

    // Open file
    char *filename = argv[1];
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        return 1;
    }

    unsigned n;
    sscanf("0xea", "%x", &n);
    printf("%u\n BEREND", n);

    return 1;

    // Allocate memory for one block
    unsigned char *buffer = malloc(BLOCK);

    // Asign output file
    FILE *output = NULL;

    // Loop over buffer blocks of 512
    while(fread(buffer, BLOCK, 1, file) != 0)
    {
        // Check if JPG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            // TODO: Check if fourth hexadecimal for JPEG is in range
            if (1 == 1)
                {
                // Close output if not referring to a file
                if (output != NULL)
                {
                    fclose(output);
                }

                output = fopen(generateName(), "w");

                fwrite(buffer, BLOCK, 1, output);
            }
        }
    }

    free(buffer);
    fclose(file);

    return 0;
}

int filenum = 0;
char filename[8];

char *generateName()
{
    sprintf(filename, "%03d.jpg", filenum);

    filenum++;
    return filename;
}