#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_valid(const int *numbers_array, const int length, const int skip) {
  if (length < 2) {
    return true;
  }

  bool valid = true;
  bool increasing = numbers_array[0] < numbers_array[1];
  if (skip == 0) {
    increasing = numbers_array[1] < numbers_array[2]; 
  } if (skip == 1) {
    increasing = numbers_array[0] < numbers_array[2];
  }

  int length_mod = 1;
  if (skip > -1) {
    length_mod += 1;
  }

  for (int i = 0; i < length - 1; i++) {
    if (i == skip) {
      continue;
    }

    if (skip > length - 2 && i > length - 3) {
      continue;
    }

    int next_amount = 1;
    if (i + 1 == skip) {
      next_amount += 1;
    }

    int curr = numbers_array[i];
    int next = numbers_array[i + next_amount];
    
    if (abs(next - curr) > 3) {
      valid = false;
    }

    if (increasing != next > curr) {
      valid = false;
    } else if (curr == next) {
      valid = false;
    }
  }

  return valid;
}

int main() {
  FILE *file = fopen("input1.txt", "r");

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
    counter = 0;
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

    printf(" // checking");
    bool valid = is_valid(numbers, counter, -1);

    if (!valid) {
      bool skip_valid = false;

      for (int i = 0; i <= counter - 1; i++) {
        valid = is_valid(numbers, counter, i);
        
        if (valid) {
          skip_valid = true;
        }
      }

      if (skip_valid) {
        valid_rows += 1;
      }

      printf(" // skipped, valid: %d\n", skip_valid);
    } else {
      if (valid) {
        valid_rows += 1;
      }

      printf(" // valid: %d\n", valid);
    }
 }

  printf("Total: %i\n", valid_rows);

  fclose(file);
  free(numbers);
  return 0;
}

