/*
 * Homework 6
 * Name Aditya Balwani
 * SUBID : 109353920
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HELP "\t-h\tDisplays this help menu\n\t-i\tDisplays statistics about instructions type usages.\n\t-m\tDisplays all the immediate values used in I-Type and J-Type instructions\n\t-r\tDisplays information about the registers\n\t-u\tDisplays human readable headers for different information displayed.\n\t\tShould only be used with the -i, -r, and -m flags."
#define ERROR_SUCCESS 0
#define ERROR_REG 1
#define ERROR_INSTR 2
#define ERROR_IMMEDIATE 3
#define ERROR_FLAGS 4

void printHelp() {
  printf("%s\n",HELP);
}

int displayStatistics() {
  int i=0, j=0, r=0, sum=0,ctr,flag=0;
  int readHex,opcode;
  float avgi, avgj, avgr;
  char buff[30];
  for(ctr=0;ctr<30;ctr++) {
    buff[ctr] = '\0';
  }
  fgets(buff,sizeof(buff),stdin);
  while(sscanf(buff,"%[x0123456789abcdefABCDEF]",buff) == 1) {
    for(ctr=0;ctr<30;ctr++) {
      if(buff[ctr]=='\n') {
        buff[ctr]='\0';
      }
    }
    if(strlen(buff) !=10) {
      return ERROR_INSTR;
    }
    flag=1;
    sscanf(buff,"%x",&readHex);
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
    for(ctr=0;ctr<30;ctr++) {
      buff[ctr] = '\0';
    }
    fgets(buff,sizeof(buff),stdin);
  }
  if(flag) {
    sum = i+j+r;
    avgi=((float)i/sum)*100;
    avgj=((float)j/sum)*100;
    avgr=((float)r/sum)*100;
    printf("R-Type\t%d\t%.2f%%\nJ-Type\t%d\t%.2f%%\nI-Type\t%d\t%.2f%%\n",r,avgr,j,avgj,i,avgi);
  }
  return ERROR_SUCCESS;
}

int displayRegisters() {
  int readHex,opcode, reg, i,sum2, sum=0,ctr,flag=0;
  int idata[32], rdata[32];
  float avg;
  char buff[30];
  for(i=0;i<32;i++) {
    idata[i] = 0;
    rdata[i] = 0;
  }
  for(ctr=0;ctr<30;ctr++) {
    buff[ctr] = '\0';
  }
  fgets(buff,sizeof(buff),stdin);
  while(sscanf(buff,"%x\n",&readHex) == 1) {
    if(strlen(buff) !=11) {
      return ERROR_INSTR;
    }
    flag = 1;
    opcode = readHex >> 26;
    if(opcode == 0) {
      reg = readHex >> 21;
      reg = reg & 0x0000001F;
      rdata[reg]++;
      sum++;
      reg = readHex >> 16;
      reg = reg & 0x0000001F;
      rdata[reg]++;
      sum++;
      reg = readHex >> 11;
      reg = reg & 0x0000001F;
      rdata[reg]++;
      sum++;
    }
    else if (opcode== 2 || opcode == 3) {

    }
    else{
      reg = readHex >> 21;
      reg = reg & 0x0000001F;
      idata[reg]++;
      sum++;
      reg = readHex >> 16;
      reg = reg & 0x0000001F;
      idata[reg]++;
      sum++;
    }
    for(ctr=0;ctr<30;ctr++) {
      buff[ctr] = '\0';
    }
    fgets(buff,sizeof(buff),stdin);
  }
  if(flag){
    for(i = 0;i<32;i++){
      sum2 = idata[i]+rdata[i];
      avg = 100 * ((float)(sum2))/sum;
      printf("$%-2d%6d%8d%8d%8d%9.2f\n",i,sum2, rdata[i],idata[i],0, avg);
    }
  }
  return ERROR_SUCCESS;
}

int displayAll() {
  int readHex,opcode, addr;
  while(scanf("%x\n",&readHex) == 1) {
    opcode = readHex >> 26;
    if(opcode == 0) {

    }
    else if (opcode== 2 || opcode == 3) {
      addr = readHex & 0x03FFFFFF;
      printf("0x%x\n",addr);
    }
    else{
      addr = readHex & 0x0000FFFF;
      printf("0x%x\n",addr);
    }
  }
  return ERROR_SUCCESS;
}

int main(int argc, char *argv[]) {;
  int iflag=0,hflag=0,uflag=0,rflag=0,mflag=0,ret;
  char c;
  if(argc == 1) {
    printHelp();
    return ERROR_FLAGS;
  }
  while((c= getopt(argc,argv,"abcdefghijklmnopqrtstuvwxyz:")) != -1) {
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
  if(hflag){
    printHelp();
    return ERROR_SUCCESS;
  }

  if(iflag && !mflag && !rflag && !uflag) {
    ret = displayStatistics();
    return ret;
  }
  else if(!iflag && mflag && !rflag && !uflag) {
    ret = displayAll();
    return ret;
  }
  else if(!iflag && !mflag && rflag && !uflag) {
    ret = displayRegisters();
    return ret;
  }

  else if(iflag && !mflag && !rflag && uflag) {
    printf("%6s%7s%9s\n","TYPE","COUNT","PERCENT");
    ret = displayStatistics();
    return ret;
  }
  else if(!iflag && mflag && !rflag && uflag) {
    printf("IMMEDIATE-VALUE\n");
    ret = displayAll();
    return ret;
  }
  else if(!iflag && !mflag && rflag && uflag) {
    printf("REG%5s%8s%8s%8s%11s\n","USE","R-TYPE","I-TYPE", "J-TYPE", "PERCENT");
    ret = displayRegisters();
    return ret;
  }
  else {
    return ERROR_FLAGS;
  }
}
