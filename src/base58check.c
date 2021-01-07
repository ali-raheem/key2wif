#include "base58check.h"
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

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

  strrev(output);

  mpz_clears(x, r, d, t, NULL);
  return output;
}

void strrev(char *str) {
  size_t len = strlen(str);
  if (len < 2)
    return;
  char t;
  size_t i;
  for(i = 0; i < (len/2); i++) {
    t = str[i];
    str[i] = str[len - i - 1];
    str[len - i - 1] = t;
  }
}
