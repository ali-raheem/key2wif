#ifndef BASE58CHECK_H
#define BASE58CHECK_H

#include <gmp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *b58encode(const char const *);
char *b58decode(const char const *);
void strrev(char *);
signed long strpos(const char const *, const char);
#endif
