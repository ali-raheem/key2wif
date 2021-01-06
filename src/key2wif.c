#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <openssl/sha.h>
#include "base58check.h"

char *hexdigest(const unsigned char const *d, const size_t l) {
  if(0 == l)
    puts("zero length data");
  size_t i;
  char *str = (char *) malloc(2 * l + 1);
  if(NULL == str)
    return NULL;
  for(i = 0; i < l; i++)
    sprintf(str + (2 * i), "%02x", d[i]);
  str[2*l+1] = 0;
  return str;
}

void print_hexdigest(const unsigned char const *d, const size_t l) {
  char *str = hexdigest(d, l);
  if (NULL == str)
    return;
  puts(str);
  free(str);
}

int main(int argc, char* argv[]) {
  if(argc < 2) {
    printf("Usage:\n\t%s KEY_FILE\n\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  const char const *key_file = argv[1];
  FILE *fp;
  size_t length;
  fp = fopen(key_file, "rb");
  assert(NULL != fp);
  fseek(fp, 0L, SEEK_END);
  length = ftell(fp);
  rewind(fp);

  unsigned char *key = (unsigned char *) malloc(length + 5);
  assert(NULL != key);
  memset(key, 0x80, 1);
  assert(length ==
	 fread(key + 1, 1, length, fp));
  fclose(fp);
  fp = NULL;

  unsigned char hash[SHA256_DIGEST_LENGTH];
  unsigned char hash1[SHA256_DIGEST_LENGTH];
  SHA256(key, length + 1, hash);
  SHA256(hash, SHA256_DIGEST_LENGTH, hash1);
  
  memcpy(key + length + 1, hash1, 4);

  char *hd = hexdigest(key, length + 5);
  printf("key: %s\n", hd);  
  char *wif = b58encode(hd);
  printf("WIF: %s\n", wif);
  free(key);
  key = NULL;
}
