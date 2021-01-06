#include <stdio.h>
#include "base58check.h"

int main(int argc, char *argv[]) {
  if(argc < 2)
    return 1;
  char *s = b58encode(argv[1]);
  puts(s);
}
