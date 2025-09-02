#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
  // Check if correct number of arguments provided
  if (argc != 3) {
    fprintf(stderr, "Usage: %s infilename outfilename\n", argv[0]);
    return 1;
  }

  char *input_filename = argv[1];
  char *output_filename = argv[2];

  FILE *input_file_ptr = fopen(input_filename, "r");
  if (input_file_ptr == NULL) {
    fprintf(stderr, "Error: Cannot open input file '%s'\n", input_filename);
    return 1;
  }

  int input_size = 0;
  // Read the first number and store it
  if (fscanf(input_file_ptr, "%d", &input_size) != 1) {
    fprintf(stderr, "Error: No numbers found in the file '%s'\n", input_filename);
    fclose(input_file_ptr);
    return 1;
  }

  float *data = (float*) malloc(input_size * sizeof(float));
  if (data == NULL) {
    fprintf(stderr, "Error: Memory allocation failed\n");
    fclose(input_file_ptr);
    return 1;
  }

  float num = 0;
  int i = 0;

  while (fscanf(input_file_ptr, "%f", &num) == 1) {
    data[i] = num;
    i++;
  }

  // Calculate min, max, avg, and standard deviation of the data set
  float min = data[0];
  float max = data[0];
  float sum = 0.0f;
  for (int i = 0; i < input_size; ++i) {
    if (data[i] < min) min = data[i];
    if (data[i] > max) max = data[i];
    sum += data[i];
  }
  float avg = sum / input_size;

  float variance_sum = 0.0f;
  for (int i = 0; i < input_size; ++i) {
    variance_sum += (data[i] - avg) * (data[i] - avg);
  }
  float stddev = 0.0f;
  if (input_size > 1) {
    stddev = sqrt(variance_sum / input_size);
  }

  // Print statistics to output file
  FILE *output_file_ptr = fopen(output_filename, "w");
  fprintf(output_file_ptr, "Min: %1.1f\n", min);
  fprintf(output_file_ptr, "Max: %1.1f\n", max);
  fprintf(output_file_ptr, "Avg: %1.1f\n", avg);
  fprintf(output_file_ptr, "Std: %.8f", stddev);

  // close the files
  fclose(output_file_ptr);
  fclose(input_file_ptr);
  // free the memory
  free(data);
  return 0;
}
