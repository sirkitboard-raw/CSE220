/*
 * Name : Aditya Balwani
 * SBUID: 109353920
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hw7.h"
#define HELP "usage: ./a.out [-s | -a | -h]\n\t-s\tSubstitution cipher\n\t\tAdditional parameters: [-e | -d] n INPUT_FILE OUTPUT_FILE\n\t\t-e\tEncrypt using the substitution cipher.\n\t\t-d\tDecrypt using the substitution cipher.\n\t\tn\tThe amount of position to shift by.\n\t\tINPUT_FILE This can be any file on the file system or - which specifies stdin.\n\t\tOUTPUT_FILE\tThis can be any file on the system or - which specifies stdout.\n\n\t-a\tAutokey cipher\t\tAdditional parameters: [-e | -d] n INPUT_FILE KEY_FILE OUTPUT_FILE\n\t\t-e\t\tEncrypt using the autokey cipher\n\t\t-d\t\tDecrypt using the autokey cipher\n\t\tn\t\tThe initial shift value\n\t\tINPUT_FILE\tThis can be any file on the file system or - which specifies stdin.\n\t\tKEY_FILE\tThis can be any file on the file system or - which specifies stdin.\n\t\tOUTPUT_FILE\tThis can be any file on the system or - which specifies stdout.\n\t-h\tDisplays this help menu\n"
#ifdef DEBUG
  #define debug(fmt, ...) printf("DEBUG:%s:%s:%d" fmt, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS)
#else
  #define debug(fmt,...)
#endif
void printHelp() {
  printf("%s",HELP);
}

int main(int argc, char* argv[]) {
  printHelp();
  debug("HELLLOOO!");
  return EXIT_SUCCESS;
}
