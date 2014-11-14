/*
 * Name : Aditya Balwani
 * SBUID: 109353920
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "hw7.h"
#define HELP "usage: ./a.out [-s | -a | -h]\n\t-s\tSubstitution cipher\n\t\tAdditional parameters: [-e | -d] n INPUT_FILE OUTPUT_FILE\n\t\t-e\tEncrypt using the substitution cipher.\n\t\t-d\tDecrypt using the substitution cipher.\n\t\tn\tThe amount of position to shift by.\n\t\tINPUT_FILE This can be any file on the file system or - which specifies stdin.\n\t\tOUTPUT_FILE\tThis can be any file on the system or - which specifies stdout.\n\n\t-a\tAutokey cipher\t\tAdditional parameters: [-e | -d] n INPUT_FILE KEY_FILE OUTPUT_FILE\n\t\t-e\t\tEncrypt using the autokey cipher\n\t\t-d\t\tDecrypt using the autokey cipher\n\t\tn\t\tThe initial shift value\n\t\tINPUT_FILE\tThis can be any file on the file system or - which specifies stdin.\n\t\tKEY_FILE\tThis can be any file on the file system or - which specifies stdin.\n\t\tOUTPUT_FILE\tThis can be any file on the system or - which specifies stdout.\n\t-h\tDisplays this help menu\n"

#ifdef CSE220
  #define cse220(fmt, ...) printf("CSE220:" fmt "\n", ##__VA_ARGS__);
#else
  #define cse220(fmt,...)
#endif

#ifdef DEBUG
  #define debug(fmt, ...) printf("DEBUG:%s:%s:%d " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
  #define debug(fmt,...)
#endif


void printHelp() {
  printf("%s",HELP);
}

void createTabula(int shift) {
  char* t = *tabula;
  int i,j;
  for(i=0;i<ALPHABET_SIZE;i++) {
    for(j=0;j<ALPHABET_SIZE;j++) {
      t = *tabula + (sizeof(char)*ALPHABET_SIZE*i);
      t = t + (sizeof(char)*j);
      *t = (int)(((j+shift+i)%ALPHABET_SIZE)+65);
    }
  }
}

int encryptCaeser(int shift, FILE *fp, FILE *fc) {
  char c;
  int temp;
  debug("encrypt started");
  while((c=fgetc(fp))!=EOF) {
    temp = (char)c;
    debug("step");
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
  debug("encrupt ended");
  return EXIT_SUCCESS;
}

int decryptCaeser(int shift, FILE *fr, FILE *fw) {
  char c;
  int temp;
  while((c=fgetc(fr))!=EOF) {
    debug("%c",c);
    temp = (char)c;
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

int encryptAuto(int shift, FILE *fr, FILE *fk, FILE *fw) {
  char c;
  int temp;
  char*k;
  int charctr=0, keyflag=1,charctr2 = 0;
  char *plain = plaintext;
  char *tab = *tabula;
  k = key;

  while((c=fgetc(fk))!=EOF) {
    temp = (char)c;
    if((temp>=65 && temp<91) || (temp>=97 && temp<123)) {
      if(temp>=97) {
        c-=32;
      }
      *k = c;
      k+=sizeof(char);
    }
  }
  while((c=fgetc(fr))!=EOF) {
    temp = (char)c;
    if((temp>=65 && temp<91) || (temp>=97 && temp<123)) {
      if(temp>=97) {
        c-=32;
      }
      if(keyflag) {
        plain = plaintext+(sizeof(char)*charctr);
        k = key + (sizeof(char)*charctr);
        *plain = c;
        temp = ( *k +shift-65)%ALPHABET_SIZE;
        tab = *tabula + (sizeof(char)*ALPHABET_SIZE*temp);
        c = (c+shift-65)%ALPHABET_SIZE;
        tab+= sizeof(char)*c;
        c+=65;
        debug("%c , %c -> %c",*k,c,*tab);
        fputc((int)(*tab),fw);
        charctr++;
        if(charctr>=strlen(key)) {
          keyflag=0;
          charctr=0;
        }
      }
      else {
        charctr%=BUFFER_SIZE;
        charctr2%=BUFFER_SIZE;
        plain = plaintext+sizeof(char)*charctr2;
        temp = (*plain+shift-65)%ALPHABET_SIZE;
        plain = plaintext+sizeof(char)*charctr;
        *plain = c;
        c = (c+shift-65)%ALPHABET_SIZE;
        tab = *tabula + (sizeof(char)*ALPHABET_SIZE*temp);
        temp+=65;
        tab+= sizeof(char)*c;
        c+=65;
        debug("%c , %c -> %c",temp,c,*tab);
        fputc((int)(*tab),fw);
        charctr++;
        charctr2++;
      }
    }
    else {
      fputc((int)(c),fw);
    }
  }
  debug("END");
  return EXIT_SUCCESS;
}

int decryptAuto(int shift, FILE *fr, FILE *fk, FILE *fw) {
  char c;
  int temp,found=1;
  char*k;
  int charctr=0, keyflag=1,charctr2 = 0, ctr=0;
  char *plain = plaintext;
  char *tab = *tabula;
  k = key;

  while((c=fgetc(fk))!=EOF) {
    temp = (char)c;
    if((temp>=65 && temp<91) || (temp>=97 && temp<123)) {
      if(temp>=97) {
        c-=32;
      }
      *k = c;
      k+=sizeof(char);
    }
  }
  while((c=fgetc(fr))!=EOF) {
    temp = (char)c;
    if((temp>=65 && temp<91) || (temp>=97 && temp<123)) {
      if(temp>=97) {
        c-=32;
      }
      if(keyflag) {
        k = key + (sizeof(char)*charctr);
        temp = ( *k-shift-65+ALPHABET_SIZE)%ALPHABET_SIZE;
        tab = *tabula + (sizeof(char)*ALPHABET_SIZE*temp);
        found = 0;
        ctr = 0;
        while(!found) {
          if(*tab == c) {
            found = 1;
          } else {
            ctr++;
            tab+=sizeof(char);
          }
        }
        tab = *tabula + (sizeof(char)*ctr);
        fputc((int)(*tab),fw);
        plain = plaintext+(sizeof(char)*charctr);
        *plain = *tab;
        debug("%c , %c -> %c",*k,c,*tab);
        charctr++;
        if(charctr>=strlen(key)) {
          keyflag=0;
          charctr=0;
        }
      }
      else {
        charctr%=BUFFER_SIZE;
        charctr2%=BUFFER_SIZE;
        plain = plaintext + (sizeof(char)*charctr2);
        temp = ( *plain -shift-65+ALPHABET_SIZE)%ALPHABET_SIZE;
        tab = *tabula + (sizeof(char)*ALPHABET_SIZE*temp);
        found = 0;
        ctr = 0;
        while(!found) {
          if(*tab == c) {
            found = 1;
          } else {
            ctr++;
            tab+=sizeof(char);
          }
        }
        tab = *tabula + (sizeof(char)*ctr);
        fputc((int)(*tab),fw);
        plain = plaintext+(sizeof(char)*charctr);
        *plain = *tab;
        temp+=65;
        debug("%c , %c -> %c",temp,c,*tab);
        charctr++;
        charctr2++;
      }
    }
    else {
      fputc((int)(c),fw);
    }
  }
  debug("END");
  return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
  int sflag=0,aflag=0,hflag=0,eflag=0,dflag=0,shift,ret,inflag = 0;
  char **argptr = argv;
  char *ptr;
  char c;
  FILE* fr,*fw,*fk;
  while((c= getopt(argc,argv,"sahed")) != -1) {
    switch(c) {
      case 's':
        sflag=1;break;
      case 'a':
        aflag=1;break;
      case 'h':
        hflag=1;break;
      case 'e':
        eflag=1;break;
      case 'd':
        dflag=1;break;
      case '3':
      default:
        printHelp();
        return EXIT_FAILURE;
    }
  }

  if(hflag) {
    printHelp();
  }
  if(sflag && !aflag){
    if(argc - optind != 3) {
      return EXIT_FAILURE;
    }
    ptr= *(argv + optind);
    if((sscanf(ptr, "%d",&shift)!=1)) {
      return EXIT_FAILURE;
    }
    cse220("shift amount: %d",shift);
    ptr= *(argptr+optind+1);
    if(!strcmp(ptr,"-")) {
      fr = stdin;
    }
    else {
      fr = fopen(ptr,"r");
      if(fr==0) {
        return EXIT_FAILURE;
      }
    }
    cse220("input file: %s", ptr);
    ptr= *(argptr +optind+2);
    if(!strcmp(ptr,"-")) {
      fw = stdout;
    }
    else {
      fw = fopen(ptr,"w");
      if(fw==0) {
        return EXIT_FAILURE;
      }
    }
    cse220("output file: %s", ptr);
    cse220("cipher type : substitution cipher");
    if(eflag &&! dflag) {
      cse220("cipher operation: encryption");
      ret = encryptCaeser(shift, fr,fw);
      fclose(fr);
      fclose(fw);
      return ret;
    }
    else if (dflag && !eflag) {
      cse220("cipher operation: decryption");
      ret = decryptCaeser(shift, fr, fw);
      fclose(fr);
      fclose(fw);
      return ret;
    }
    else return EXIT_FAILURE;
  }
  else if(!sflag && aflag){
    if(argc - optind != 4) {
      return EXIT_FAILURE;
    }
    ptr= *(argv + optind);
    if((sscanf(ptr, "%d",&shift)!=1)) {
      return EXIT_FAILURE;
    }
    cse220("shift amount: %d",shift);
    ptr= *(argptr+optind+1);
    if(!strcmp(ptr,"-")) {
      fr = stdin;
      inflag = 1;
    }
    else {
      fr = fopen(ptr,"r");
      if(fr==0) {

        return EXIT_FAILURE;
      }
    }
    cse220("input file: %s", ptr);
    ptr= *(argptr +optind+2);
    if(!strcmp(ptr,"-")) {
      if(!inflag) {
        fk = stdin;
      }
      else {
        return EXIT_FAILURE;
      }
    }
    else {
      fk = fopen(ptr,"r");
      if(fk==0) {
        return EXIT_FAILURE;
      }
    }
    cse220("key file: %s", ptr);

    ptr= *(argptr+optind+3);
    if(!strcmp(ptr,"-")) {
      fw = stdout;
    }
    else {
      fw = fopen(ptr,"w");
      if(fw==0) {
        return EXIT_FAILURE;
      }
    }
    cse220("output file: %s", ptr);
    cse220("cipher function : Autokey");

    if(eflag &&! dflag) {
      cse220("cipher mode : encrypt");

      createTabula(shift);
      ret = encryptAuto(shift, fr,fk,fw);
      fclose(fr);
      fclose(fw);
      return ret;
    }
    else if (dflag && !eflag) {
      cse220("cipher mode : decrypt");
      createTabula(shift);
      ret = decryptAuto(shift, fr, fk,fw);
      fclose(fr);
      fclose(fw);
      fclose(fk);
      return ret;
    }
    else return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
