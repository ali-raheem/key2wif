#include "base58check.h"
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char *b58encode(const char const *instr) {
  char charset[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
  mpz_t x, r, d, t;
  size_t bufflen = 100;
  char * output = (char *) malloc (bufflen);
  if (NULL == output)
    return NULL;
  size_t len = 0;
  mpz_inits(x, r, d, t, NULL);
  mpz_set_ui(d, 58);
  mpz_set_str(x, instr, 16);
  while ( mpz_cmp_ui(x, 0) > 0 ) {
    mpz_fdiv_r(r, x, d);
    mpz_fdiv_q(t, x, d);
    mpz_swap(x, t);
    sprintf(output + len, "%c", charset[mpz_get_ui(r)]);
    len ++;
    if (len == bufflen) {
      bufflen *= 2;
      output = (char *) realloc(output, bufflen);
      if (NULL == output)
	return output;
    }
  }
  
  output = realloc(output, len);
  if (NULL == output)
    return output;

  reversestr(output);

  mpz_clears(x, r, d, t, NULL);
  return output;
}

void reversestr(char *str) {
  size_t len = strlen(str);
  char t;
  size_t i = 0;
  while(i < (len/2)) {
    t = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = t;
    i++;
  }
}
