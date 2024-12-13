#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
  FILE *file = fopen("example-input1.txt", "r");

  if (file == NULL) {
    perror("Unable to open file");
    return 1;
  }

  char line[100];
  size_t rule_capacity = 10;
  size_t rule_counter = 0;
  char **rules = malloc(rule_capacity * sizeof(char *));

  bool rules_complete = false;

  while (fgets(line, sizeof(line), file) && !rules_complete) {
    if (strcmp(line, "\n") == 0) {
      printf("rules complete!\n");
      rules_complete = true;
      continue;
    }

    char *left_char = strtok(line, "|");
    char *right_char = strtok(NULL, "|");

    char left_num = strtol(left_char, NULL, 10);
    char right_num = strtol(right_char, NULL, 10);

    if (rule_counter < rule_capacity) {
      rule_capacity *= 2;
      rules = realloc(rules, rule_capacity * sizeof(char *));
    }

    printf("rule: %d|%d\n", left_num, right_num);
    rules[rule_counter] = malloc(2 * sizeof(int));
    
    rules[rule_counter][0] = left_num;
    rules[rule_counter][1] = right_num;
    rule_counter += 1;
  }

  printf("Rules (%zu) :\n", rule_counter);
  for (int i = 0; i < rule_counter; i++) {
    printf("i: %d / %d : %d\n", i, rules[i][0], rules[i][1]);
  }

  int count = 0;

  while (fgets(line, sizeof(line), file)) {
    printf("line: %s", line);
    char *prev_char = strok(line, ",");
    char *curr_char = strtok(NULL, ",");

    while (curr_char != NULL) {
      for (int i = 0; i < rule_counter; i++) {
        
      }

      curr_char = strtok(NULL, ",");
    }
  }

  for (int i = 0; i < rule_capacity; i++) {

    free(rules[i]);
  }
  free(rules);

  return 0;
}
