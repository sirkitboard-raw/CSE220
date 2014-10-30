/*
 * Homework 6
 * Name Aditya Balwani
 * SUBID : 109353920
 */
#include <stdio.h>
#define HELP "\t-h\tDisplays this help menu\n\t-i\tDisplays statistics about instructions type usages.\n\t-m\tDisplays all the immediate values used in I-Type and J-Type instructions\n\t-r\tDisplays information about the registers\n\t-u\tDisplays human readable headers for different information displayed.\n\t\tShould only be used with the -i, -r, and -m flags."
#define ERROR_SUCCESS 0
#define ERROR_REG 1
#define ERROR_INSTR 2
#define ERROR_IMMEDIATE 3
#define ERROR_FLAGS 4

void printHelp() {
  printf("%s\n",HELP);
}

void displayStatistics() {
  int i=0, j=0, r=0, sum=0;
  int readHex,opcode;
  float avgi, avgj, avgr;
  while(scanf("%x\n",&readHex) == 1) {
    opcode = readHex >> 26;
    if(opcode == 0) {
      r++;
    }
    else if (opcode== 2 || opcode == 3) {
      j++;
    }
    else{
      i++;
    }
  }
  sum = i+j+r;
  avgi=((float)i/sum)*100;
  avgj=((float)j/sum)*100;
  avgr=((float)r/sum)*100;
  printf("R-Type\t%d\t%.2f%%\nJ-Type\t%d\t%.2f%%\nI-Type\t%d\t%.2f%%\n",r,avgr,j,avgj,i,avgi);
}

void displayAll() {

}

void displayRegisters() {

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
    else if(iflag) {
      displayStatistics();
      return ERROR_SUCCESS;
    }
    else if(mflag) {
      displayAll();
    }
    else if(rflag) {
      displayRegisters();
    }
  }
}
