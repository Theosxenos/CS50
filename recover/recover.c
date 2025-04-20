#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open forensic image
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open %s for reading.\n", argv[1]);
        return 1;
    }

    // Buffer for reading 512 bytes at a time
    BYTE buffer[512];
    
    // Track if we're currently writing to a JPEG
    bool jpeg_found = false;
    
    // File pointer for recovered JPEGs
    FILE *output = NULL;
    
    // Filename buffer
    char filename[8]; // ###.jpg\0
    
    // Counter for JPEG files
    int jpeg_count = 0;

    // Read 512-byte blocks from input file
    while (fread(buffer, sizeof(BYTE), 512, input) == 512)
    {
        // Check if block starts with JPEG signature
        // JPEG signatures start with 0xff 0xd8 0xff followed by 0xe0-0xef
        bool is_jpeg_header = (buffer[0] == 0xff && 
                              buffer[1] == 0xd8 && 
                              buffer[2] == 0xff && 
                              (buffer[3] & 0xf0) == 0xe0);

        // If found a new JPEG signature
        if (is_jpeg_header)
        {
            // If already writing to a file, close it
            if (jpeg_found)
            {
                fclose(output);
            }
            
            // Generate new filename
            sprintf(filename, "%03i.jpg", jpeg_count);
            
            // Open new file for writing
            output = fopen(filename, "w");
            if (output == NULL)
            {
                fclose(input);
                printf("Could not create %s.\n", filename);
                return 1;
            }
            
            // Update flags and counter
            jpeg_found = true;
            jpeg_count++;
        }
        
        // If we've found a JPEG, write the current block
        if (jpeg_found)
        {
            fwrite(buffer, sizeof(BYTE), 512, output);
        }
    }

    // Close any remaining files
    if (jpeg_found)
    {
        fclose(output);
    }
    fclose(input);
    
    return 0;
}