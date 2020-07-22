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
    if (argc != 2)
    {
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

    // Allocate memory for one block
    unsigned char *buffer = malloc(BLOCK);

    // Asign output file
    FILE *output = NULL;

    // Assign temp file name
    char *tempname = NULL;

    // Loop over buffer blocks of 512
    while (fread(buffer, BLOCK, 1, file) != 0)
    {
        // If start of new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close output if not yet refer to a file and END of JPEG
            if (output != NULL)
            {
                fclose(output);
            }

            // Open up new file with name
            tempname = generateName();

            output = fopen(tempname, "w");

            if (output != NULL)
            {
                fwrite(buffer, BLOCK, 1, output);
            }
        }
        // Else if already found JPEG
        else if (tempname != NULL)
        {
            fwrite(buffer, BLOCK, 1, output);
        }
        // Empty space
        else
        {
            tempname = NULL;
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