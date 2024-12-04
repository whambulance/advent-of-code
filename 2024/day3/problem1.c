#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

unsigned concatenate(unsigned x, unsigned y) {
  unsigned pow = 10;
  while (y >= pow) {
    pow *= 10;
  }
  return x * pow + y;
}

int main() {
  FILE *file = fopen("input1.txt", "r");

  if (file == NULL) {
    perror("Unable to open file");
    return 1;
  }

  int ch_int;
  int counter = 0;
  int sequence_counter = 0;
  char sequence[10] = "mul(0,0)";

  int first_mult = -1;
  int second_mult = -1;
  bool number_mode = false;
  int total = 0;
  
  while ((ch_int = fgetc(file)) != EOF) {
    char ch = (char)ch_int;
    char seq_ch = sequence[sequence_counter];

    if (number_mode && counter > 0) {
      if (isdigit(ch) > 0) {
        counter += 1;

        if (second_mult == -1) {
          int num = ch - '0';
          first_mult = concatenate(first_mult, num);
        } else {
          int num = ch - '0';
          second_mult = concatenate(second_mult, num);
        }

        continue;
      } else {
        number_mode = false;
        sequence_counter += 1;
        seq_ch = sequence[sequence_counter];
      }
    }

    if (ch == seq_ch) {
      counter += 1;
      sequence_counter += 1;
      if (sequence_counter > 7) {
        total += first_mult * second_mult;
        
        first_mult = -1;
        second_mult = -1;
        counter = 0;
        sequence_counter = 0;
      }
    } else if (isdigit(seq_ch) > 0 && isdigit(ch) > 0) {
      counter += 1;
      number_mode = true;
      
      if (first_mult == -1) {
        first_mult = ch - '0';
      } else {
        second_mult = ch - '0';
      }
    } else {
      counter = 0;
      sequence_counter = 0;
      first_mult = -1;
      second_mult = -1;
    }
  }

  printf("\n total %i\n", total);

  fclose(file);
  return 0;
}

