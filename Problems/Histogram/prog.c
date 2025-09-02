#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check if correct number of arguments provided
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infilename outfilename\n", argv[0]);
        return 1;
    }

    char *input_filename = argv[1];
    char *output_filename = argv[2];

    // Open input file
    FILE *input_file = fopen(input_filename, "r");
    if (!input_file) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", input_filename);
        return 1;
    }

    // Initialize letter count array (26 letters)
    int letter_counts[26] = {0};
    
    // Read characters from input file and count letters
    int ch;
    while ((ch = fgetc(input_file)) != EOF) {
        if (isalpha(ch)) {
            // Convert to lowercase and count
            char lower_ch = tolower(ch);
            letter_counts[lower_ch - 'a']++;
        }
    }
    fclose(input_file);

    // Open output file
    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        fprintf(stderr, "Error: Cannot open output file '%s'\n", output_filename);
        return 1;
    }

    // Find the maximum count to determine histogram height
    int max_count = 0;
    for (int i = 0; i < 26; i++) {
        if (letter_counts[i] > max_count) {
            max_count = letter_counts[i];
        }
    }

    // Middle section: Histogram bars
    for (int row = max_count; row > 0; row--) {
        for (int col = 0; col < 26; col++) {
            if (letter_counts[col] >= row) {
                fprintf(output_file, "x");
            } else {
                fprintf(output_file, " ");
            }
        }
        fprintf(output_file, "\n");
    }

    // Separator line
    fprintf(output_file, "-\n");

    // Bottom section: Full alphabet
    for (int i = 0; i < 26; i++) {
        fprintf(output_file, "%c", 'a' + i);
    }
    fprintf(output_file, "\n");

    fclose(output_file);
    
    printf("Successfully created histogram from '%s' to '%s'\n", input_filename, output_filename);
    return 0;
}
