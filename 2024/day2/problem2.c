#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_valid(const int *numbers_array, const int length) {
  if (length < 2) {
    return true;
  }

  bool valid = true;
  bool increasing = numbers_array[0] < numbers_array[1];

  for (int i = 1; i <= length; i++) {
    int prev = numbers_array[i - 1];
    int curr = numbers_array[i];

    if (abs(curr - prev) > 3) {
      valid = false;
    }

    // if (increasing != curr > prev) {
    //   valid = false;
    // } else if (curr == prev) {
    //   valid = false;
    // }
  }

  return valid;
}

int main() {
  FILE *file = fopen("example-input1.txt", "r");

  if (file == NULL) {
    perror("Unable to open file");
    return 1;
  }

  int valid_rows = 0;
  char line[100];

  int *numbers = NULL;
  size_t counter = 0;
  size_t capacity = 20;
  numbers = malloc(capacity * sizeof(int));

  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = 0;
    printf("line: %s", line);
    char *token = strtok(line, " ");
    numbers = malloc(capacity * sizeof(int));

    while (token != NULL) {
      if (counter > capacity) {
        capacity *= 2;
        int *temp_numbers = realloc(numbers, capacity * sizeof(int));

        if (temp_numbers == NULL) {
          perror("Unable to allocate memory");
          free(numbers);
          fclose(file);
          return 1;
        }

        numbers = temp_numbers;
      }

      numbers[counter] = strtol(token, NULL, 10);;
      counter += 1;
      token = strtok(NULL, " ");
    }

    bool valid = is_valid(numbers, counter);

    printf(" // valid: %d\n", valid);
 }

  printf("Total: %i\n", valid_rows);

  fclose(file);
  free(numbers);
  return 0;
}

