#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
  char input_filename[256];
  char output_filename[256];
  printf("Enter the input file name: ");
  scanf("%255s", input_filename);
  printf("Enter the output file name: ");
  scanf("%255s", output_filename);

  FILE *input_file_ptr = fopen(input_filename, "r");

  int input_size = 0;
  // Read the first number and store it
  if (fscanf(input_file_ptr, "%d", &input_size) != 1) {
    fprintf(stderr, "No numbers found in the file.\n");
    fclose(input_file_ptr);
    return 1;
  }

  float *data = (float*) malloc(input_size * sizeof(float));
  float num = 0;
  int i = 0;
  // Print all numbers after the first one
  while (fscanf(input_file_ptr, "%f", &num) == 1) {
    data[i] = num;
    i++;
  }

  // sort the data using bubble sort
  for (int i = 0; i < input_size - 1; ++i) {
    for (int j = 0; j < input_size - i - 1; ++j) {
      if (data[j] > data[j + 1]) {
        float temp = data[j];
        data[j] = data[j + 1];
        data[j + 1] = temp;
      }
    }
  }

  // Write the sorted data to the output file
  FILE *output_file_ptr = fopen(output_filename, "w");
  fprintf(output_file_ptr, "%d\n", input_size);
  for (int j = 0; j < input_size; ++j) {
    // Print the last number without a newline
    if (j == input_size - 1)
      fprintf(output_file_ptr, "%#2.1f", data[j]);
    else
      fprintf(output_file_ptr, "%#2.1f\n", data[j]);
  }

  // close the files
  fclose(output_file_ptr);
  fclose(input_file_ptr);
  // free the memory
  free(data);
  return 0;
}
