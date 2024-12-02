#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main() {
  FILE *file = fopen("input1.txt", "r");

  if (file == NULL) {
    perror("Unable to open file");
    return 1;
  }

  int valid_rows = 0;
  char line[100];

  while (fgets(line, sizeof(line), file)) {
    char *token = strtok(line, " ");

    int prev = strtol(token, NULL, 10);
    int curr = -1;

    bool valid = true;
    bool last_increased = true;

    token = strtok(NULL, " ");

    while (token != NULL && valid == true) {
      if (curr == -1) {
        curr = strtol(token, NULL, 10);
        last_increased = curr > prev;
      }

      curr = strtol(token, NULL, 10);

      if (abs(curr - prev) > 3) {
        valid = false;
      }

      if (last_increased && curr < prev) {
        valid = false;
      } else if (!last_increased && curr > prev) {
        valid = false;
      } else if (curr == prev) {
        valid = false;
      }

      prev = curr;
      token = strtok(NULL, " ");
    }

    if (valid) {
      valid_rows += 1;
    }
 }

  printf("Total: %i\n", valid_rows);

  fclose(file);
  return 0;
}

