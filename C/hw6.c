/*
 * Homework 6
 * Name Aditya Balwani
 * SUBID : 109353920
 */
#include <stdio.h>
#define HELP "\t-h\tDisplays this help menu\n\t-i\tDisplays statistics about instructions type usages.\n\t-m\tDisplays all the immediate values used in I-Type and J-Type instructions\n\t-r\tDisplays information about the registers\n\t-u\tDisplays human readable headers for different information displayed.\n\t\tShould only be used with the -i, -r, and -m flags."
#define ERROR_SUCCESS 0
#define ERROR_FLAGS 4
void printHelp() {
  printf("%s\n",HELP);
}

int main(int argc, char *argv[]) {
  int iflag=0,hflag=0,uflag=0,rflag=0,mflag=0;
  char c;
  if(argc == 1) {
    printHelp();
    return ERROR_FLAGS;
  }
  while((c= getopt(argc,argv,"himru:")) != -1) {
    switch(c) {
      case 'h':
        hflag=1;break;
      case 'i':
        iflag=1;break;
      case 'm':
        mflag=1;break;
      case 'r':
        rflag=1;break;
      case 'u':
        uflag=1;break;
      default:
        printHelp();
        return ERROR_FLAGS;
    }
  }
  if(argc==2) {
    if(hflag){
      printHelp();
      return ERROR_SUCCESS;
    }
  }
}
