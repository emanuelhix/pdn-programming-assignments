#include <stdio.h>
#include <stdlib.h>

// Selection sort function
void selectionSort(float arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
      
        // Assume the current position holds
        // the minimum element
        int min_idx = i;
        
        // Iterate through the unsorted portion
        // to find the actual minimum
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
              
                // Update min_idx if a smaller element is found
                min_idx = j;
            }
        }
        
        // Move minimum element to its
        // correct position
        float temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

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
  // Print all numbers after the first one
  while (fscanf(input_file_ptr, "%f", &num) == 1) {
    data[i] = num;
    i++;
  }

  // sort the data using selection sort
  selectionSort(data, input_size);

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
  
  printf("Successfully sorted %d numbers from '%s' to '%s'\n", input_size, input_filename, output_filename);
  return 0;
}
