#include <stdio.h>
#include <stdlib.h>

// https://www.geeksforgeeks.org/c/c-program-for-merge-sort
// used geeksforgeek's implementation

// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(float arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    float leftArr[n1], rightArr[n2];

    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArr[], if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArr[], if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// The subarray to be sorted is in the index range [left-right]
void mergeSort(float arr[], int left, int right) {
    if (left < right) {
      
        // Calculate the midpoint
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
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

  // sort the data using merge sort
  mergeSort(data, 0, input_size - 1);

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
