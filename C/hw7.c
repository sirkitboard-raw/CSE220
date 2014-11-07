/*
 * Name : Aditya Balwani
 * SBUID: 109353920
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hw7.h"
#define HELP "usage: ./a.out [-s | -a | -h]\n\t-s\tSubstitution cipher\n\t\tAdditional parameters: [-e | -d] n INPUT_FILE OUTPUT_FILE\n\t\t-e\tEncrypt using the substitution cipher.\n\t\t-d\tDecrypt using the substitution cipher.\n\t\tn\tThe amount of position to shift by.\n\t\tINPUT_FILE This can be any file on the file system or - which specifies stdin.\n\t\tOUTPUT_FILE\tThis can be any file on the system or - which specifies stdout.\n\n\t-a\tAutokey cipher\t\tAdditional parameters: [-e | -d] n INPUT_FILE KEY_FILE OUTPUT_FILE\n\t\t-e\t\tEncrypt using the autokey cipher\n\t\t-d\t\tDecrypt using the autokey cipher\n\t\tn\t\tThe initial shift value\n\t\tINPUT_FILE\tThis can be any file on the file system or - which specifies stdin.\n\t\tKEY_FILE\tThis can be any file on the file system or - which specifies stdin.\n\t\tOUTPUT_FILE\tThis can be any file on the system or - which specifies stdout.\n\t-h\tDisplays this help menu\n"

#ifdef CSE220
  #define debug(fmt, ...) printf("DEBUG:%s:%s:%d " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
  #define debug(fmt,...)
#endif

void printHelp() {
  printf("%s",HELP);
}

void createTabula() {
  char** t = tabula;
  char* tr;
}

int encryptCaeser(int shift, FILE *fp, FILE *fc) {
  char c;
  int temp;
  while(!feof(fp)) {
    c = fgetc(fp);
    if(feof(fp)) {
      return EXIT_SUCCESS;
    }
    temp = (char)c;
    if((temp>=65 && temp<91) || (temp>=97 && temp<123)) {
      if(temp>=97) {
        c = (char)((int)(c) - 32);
        temp = (int)(c);
      }
      temp-=65;
      temp+=shift;
      temp%=26;
      temp+=65;
      c = (char)(temp);
      fputc((int)(c),fc);
    }
    else {
      fputc((int)(c), fc);
    }
  }
  return EXIT_SUCCESS;
}

int decryptCaeser(int shift, FILE *fr, FILE *fw) {
  char c;
  int temp;
  while(!feof(fr)) {
    c = fgetc(fr);
    if(feof(fr)) {
      return EXIT_SUCCESS;
    }
    temp = (char)(c);
    if((temp>=65 && temp<91) || (temp>=97 && temp<123)) {
      if(temp>=97) {
        c = (char)((int)(c) - 32);
        temp = (int)(c);
      }
      temp-=65;
      temp+=26-shift;
      temp%=26;
      temp+=65;
      fputc(temp,fw);
    }
    else {
      fputc((int)(c),fw);
    }
  }
  return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
  debug("Shift amount 7");
  printf("%s\n",alphabet);
  FILE *fr = fopen("new.txt","r");
  FILE *fw = fopen("plain.txt","w");
  decryptCaeser(3,fr,fw);
  fclose(fr);
  fclose(fw);
  return EXIT_SUCCESS;
}
