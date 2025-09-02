#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infilename outfilename\n", argv[0]);
        return 1;
    }

    char *input_filename = argv[1];
    char *output_filename = argv[2];

    FILE *input_file = fopen(input_filename, "r");
    if (!input_file) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", input_filename);
        return 1;
    }

    int rows = 0, cols = 0;
    if (fscanf(input_file, "%d %d", &rows, &cols) != 2) {
        fprintf(stderr, "Error: Failed to read matrix dimensions from '%s'\n", input_filename);
        fclose(input_file);
        return 1;
    }

    // Allocate memory for the matrix
    float **matrix = (float **)malloc(rows * sizeof(float *));
    if (!matrix) {
        fprintf(stderr, "Error: Memory allocation failed for matrix rows\n");
        fclose(input_file);
        return 1;
    }
    for (int i = 0; i < rows; ++i) {
        matrix[i] = (float *)malloc(cols * sizeof(float));
        if (!matrix[i]) {
            fprintf(stderr, "Error: Memory allocation failed for matrix row %d\n", i);
            // Free previously allocated rows
            for (int k = 0; k < i; ++k) free(matrix[k]);
            free(matrix);
            fclose(input_file);
            return 1;
        }
    }

    // Read the matrix values
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (fscanf(input_file, "%f", &matrix[i][j]) != 1) {
                fprintf(stderr, "Error: Not enough matrix values in '%s'\n", input_filename);
                // Free memory
                for (int k = 0; k < rows; ++k) free(matrix[k]);
                free(matrix);
                fclose(input_file);
                return 1;
            }
        }
    }
    fclose(input_file);

    // Open output file
    FILE *output_file = fopen(output_filename, "w");
    if (!output_file) {
        fprintf(stderr, "Error: Cannot open output file '%s'\n", output_filename);
        for (int k = 0; k < rows; ++k) free(matrix[k]);
        free(matrix);
        return 1;
    }

    // Write transposed dimensions
    fprintf(output_file, "%d %d\n", cols, rows);

    // Write transposed matrix
    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            fprintf(output_file, "%.6g", matrix[i][j]);
            if (i < rows - 1)
                fprintf(output_file, " ");
        }
        fprintf(output_file, "\n");
    }

    // Free memory
    for (int k = 0; k < rows; ++k) free(matrix[k]);
    free(matrix);
    fclose(output_file);

    return 0;
}
