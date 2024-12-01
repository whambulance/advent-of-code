#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

int main() {
  FILE *file = fopen("input1.txt", "r");

  if (file == NULL) {
    perror("Unable to open file");
    return 1;
  }

  int *left_numbers = NULL;
  int *right_numbers = NULL;
  size_t left_size = 0;
  size_t left_capacity = 10;
  size_t right_size = 0;
  size_t right_capacity = 10;

  left_numbers = malloc(left_capacity * sizeof(int));
  right_numbers = malloc(right_capacity * sizeof(int));
  if (left_numbers == NULL | right_numbers == NULL) {
    perror("unable to allocate memory");
    fclose(file);
    return 1;
  }

  char line[100];
  while (fgets(line, sizeof(line), file)) {
    char *left_num = strtok(line, " ");
    char *right_num = strtok(NULL, " ");

    if (left_size >= left_capacity) {
      left_capacity *= 2;
      int *temp_left = realloc(left_numbers, left_capacity * sizeof(int));
      if (temp_left == NULL) {
        perror("Unable to allocate memory");
        free(left_numbers);
        free(right_numbers);
        fclose(file);
        return 1;
      }

      left_numbers = temp_left;
    }
    
    left_numbers[left_size] = strtol(left_num, NULL, 10);
    left_size++;

    int right_num_val = strtol(right_num, NULL, 10);
    printf("new right size: %d\n", right_num_val);

    if (right_num_val >= right_size) {
      right_size = right_num_val + 1;
      int *temp_right = realloc(right_numbers, right_size * sizeof(int));
      right_numbers = temp_right;
    }
    right_numbers[right_num_val] += 1;
 }

  printf("finished printing lines, apparently?\n");

  int count = 0;

  for (size_t i = 0; i < left_size; i++) {
    int left_num_val = left_numbers[i];

    if (left_num_val < right_size && right_numbers[left_num_val] > 0) {
      count += left_num_val * right_numbers[left_num_val];
    }

    printf("%d / %d / %d\n", left_num_val, right_numbers[left_num_val], left_num_val * right_numbers[left_num_val]);
  }

  printf("\nTotal: %d", count);

  fclose(file);

  free(left_numbers);
  free(right_numbers);
  return 0;
}

