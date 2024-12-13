#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
  FILE *file = fopen("input1.txt", "r");

  if (file == NULL) {
    perror("Unable to open file");
    return 1;
  }

  char line[100];
  size_t rule_counter = 0;
  size_t rule_capacity = 0;
  int *rules = malloc(10 * sizeof(int));

  bool rules_complete = false;

  while (!rules_complete && fgets(line, sizeof(line), file)) {
    if (strcmp(line, "\n") == 0) {
      printf("rules complete!\n");
      rules_complete = true;
      continue;
    }

    char *left_char = strtok(line, "|");
    char left_num = strtol(left_char, NULL, 10);

    if (left_num > rule_capacity) {
      rule_capacity = left_num;
      rules = realloc(rules, rule_capacity * sizeof(int));
    }
    
    rules[left_num] += 1;
    rule_counter += 1;
  }

  printf("Rules (%zu) :\n", rule_counter);
  for (int i = 0; i <= rule_capacity; i++) {
    if (rules[i] > 0) {
      printf("i: %d / %d\n", i, rules[i]);
    }
  }

  int count = 0;
  int *line_numbers = malloc(100 * sizeof(int));

  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\r\n")] = 0;
    printf("line: %s\ncompares: ", line);
    int prev_count = 9999;
    int counter = 0;
    char *number_char = strtok(line, ",");
    bool valid = true;

    while (number_char != NULL && valid) {
      int number = strtol(number_char, NULL, 10);
      line_numbers[counter] = number;
      int curr_count = rules[number];

      printf("%d|%d/%d ", number, prev_count, curr_count);

      if (curr_count > prev_count) {
        valid = false;
        continue;
      } else {
        prev_count = curr_count;
      }

      number_char = strtok(NULL, ",");
      counter += 1;
    }

    if (valid) {
      count += line_numbers[((counter + 1) / 2) - 1];
    }

    printf(" // done %d // adding %d\n", valid, line_numbers[((counter + 1) / 2) - 1]);
  }

  printf("total: %d", count);

  free(line_numbers);
  free(rules);

  return 0;
}
