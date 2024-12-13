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

    if (rule_counter < left_num) {
      rule_capacity = left_num;
      rule_counter = left_num;
      rules = realloc(rules, rule_capacity * sizeof(char *));
    }

    printf("rule: %d|%d\n", left_num, right_num);
    
    if (rules[left_num] == NULL) {
      rules[left_num] = malloc(200 * sizeof(char));
      rules[left_num][-1] = 0;
    }

    int next_index = rules[left_num][-1];
    rules[left_num][next_index] = right_num;
    rules[left_num][-1] += 1;
    rule_counter += 1;
  }

  printf("Rules (%zu) :\n", rule_counter);
  for (int i = 0; i < rule_counter; i++) {
    printf("i: %d", i);
    if (rules[i]) {
      printf(" // empty\n");
      continue;
    }

    int length = rules[i][-1];
    for (int j = 0; j < length; j++) {
      printf("line?");
      // putchar(rules[i][j]);
    }
    printf("\n");
  }

  for (int i = 0; i < rule_capacity; i++) {
    free(rules[i]);
  }
  free(rules);

  return 0;
}
