#include <stdio.h>
#include <stdint.h>
#include <cs50.h>

#define BUFFER_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *fp = NULL, *img = NULL;

    // Open memory card
    fp = fopen(argv[1], "r");

    // File not open
    if (fp == NULL)
    {
        perror("Failed to open file\n");
        return 2;
    }

    BYTE buffer[BUFFER_SIZE];
    char filename[8];
    int file_count = 0;

    // Repeat until end of card
    // Read 512 bytes into buffer
    while (fread(buffer, BUFFER_SIZE, 1, fp) == 1)
    {
        // JPEG found
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xe0) == 0xe0))
        {
            // If file is already open close current one first
            if (file_count)
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", file_count);

            // Create new file
            img = fopen(filename, "w");

            file_count++;
        }

        // If already found JPEG
        if (file_count)
        {
            // Write data to file
            fwrite(&buffer, BUFFER_SIZE, 1, img);
        }
    }

    // Close any remaining files
    fclose(img);
    fclose(fp);
}