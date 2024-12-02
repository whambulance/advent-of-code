#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main() {
  FILE *file = fopen("example-input1.txt", "r");

  if (file == NULL) {
    perror("Unable to open file");
    return 1;
  }

  int valid_rows = 0;
  char line[100];

  while (fgets(line, sizeof(line), file)) {
    printf("line: %s", line);
    char *token = strtok(line, " ");

    int prev = strtol(token, NULL, 10);
    int curr = -1;

    bool line_valid = true;
    bool skip_used = false;
    bool last_increased = true;

    token = strtok(NULL, " ");

    while (token != NULL && line_valid) {
      bool token_valid = true;
      if (curr == -1) {
        curr = strtol(token, NULL, 10);
        last_increased = curr > prev;
      }

      curr = strtol(token, NULL, 10);

      if (abs(curr - prev) > 3) {
        token_valid = false;
      }

      if (last_increased && curr < prev) {
        token_valid = false;
      } else if (!last_increased && curr > prev) {
        token_valid = false;
      } else if (curr == prev) {
        token_valid = false;
      }

      if ((!token_valid && !skip_used) || token_valid) {
        prev = curr;
        skip_used = true;
      } else if (!token_valid && skip_used) {
        line_valid = false;
      }

      printf("%i,", curr);
      token = strtok(NULL, " ");
    }

    if (line_valid) {
      valid_rows += 1;
      printf(" // valid\n");
    } else {
      printf(" // not valid\n");
    }
 }

  printf("Total: %i\n", valid_rows);

  fclose(file);
  return 0;
}

