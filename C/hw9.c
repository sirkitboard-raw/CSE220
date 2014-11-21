#include <stdio.h>
#include "hw9.h"
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/stat.h>

int reverseflag;
char numHuman[32][5];
FILE *fInstructStream=NULL,*fInStream=NULL, *fOutStream=NULL;
InstrType *superhead = NULL;

#ifdef CSE220
  #define cse220(fmt, ...) printf("CSE220:" fmt "\n", ##__VA_ARGS__);
#else
  #define cse220(fmt,...)
#endif

void printMenu() {
  printf("Usage: ./a.out [-h] [-m INSTRUCTION_MAPPING] -i INPUT_FILE -o OUTPUT_FILE\n\t-h\tDisplays this help menu.\n\t-m\tINSTRUCTION_MAPPING File that contains the instruction mapping.\n\t\tIf this option is not provided it defaults to instruction_mapping.txt.-\n\ti\tINPUT_FILE This should be a binary file that contains the .text section of a Mars220 MIPS binary.\n\t-o\tOUTPUT_FILE This can be any file on the system or \"-\" which specifies stdout.");
}

void freeInstrSpace(Instr* head) {
  if(head==NULL) {
    return;
  }
  Instr* temp = head->next;
  free(head->mnemonic);
  free(head);
  freeInstrSpace(temp);
}


void freeTypeSpace(InstrType* head) {
  if(head==NULL) {
    return;
  }
  InstrType* temp = head->next;
  freeInstrSpace(head->head);
  free(head);
  freeTypeSpace(temp);
}

void exitThingy(FILE* fins,FILE* fin,FILE* fout, InstrType*head) {
  fclose(fins);
  fclose(fout);
  fclose(fin);
  freeTypeSpace(head);
}

void initData() {
  strcpy(numHuman[0],"zero");
  strcpy(numHuman[1],"at");
  strcpy(numHuman[2],"v0");
  strcpy(numHuman[3],"v1");
  strcpy(numHuman[4],"a0");
  strcpy(numHuman[5],"a1");
  strcpy(numHuman[6],"a2");
  strcpy(numHuman[7],"a3");
  strcpy(numHuman[8],"t0");
  strcpy(numHuman[9],"t1");
  strcpy(numHuman[10],"t2");
  strcpy(numHuman[11],"t3");
  strcpy(numHuman[12],"t4");
  strcpy(numHuman[13],"t5");
  strcpy(numHuman[14],"t6");
  strcpy(numHuman[15],"t7");
  strcpy(numHuman[16],"s0");
  strcpy(numHuman[17],"s1");
  strcpy(numHuman[18],"s2");
  strcpy(numHuman[19],"s3");
  strcpy(numHuman[20],"s4");
  strcpy(numHuman[21],"s5");
  strcpy(numHuman[22],"s6");
  strcpy(numHuman[23],"s7");
  strcpy(numHuman[24],"t8");
  strcpy(numHuman[25],"t9");
  strcpy(numHuman[26],"k0");
  strcpy(numHuman[27],"k1");
  strcpy(numHuman[28],"gp");
  strcpy(numHuman[29],"sp");
  strcpy(numHuman[30],"fp");
  strcpy(numHuman[31],"ra");
}

InstrType* initInstrTypeList(InstrType *head) {
  char type;
  size_t count;
  InstrType *cursor,*temp = NULL;
  Instr *headInstr = NULL;
  size_t mallocType = sizeof(type)+sizeof(count)+(sizeof(InstrType*)*3);
  head = (InstrType*)(malloc(mallocType));
  if(head == NULL) {
    exitThingy(fInStream,fInstructStream, fOutStream, superhead);
    exit(EXIT_FAILURE);
  }
  cursor = head;
  (*cursor).type = 'R';
  (*cursor).count=0;
  (*cursor).prev = NULL;
  (*cursor).head = headInstr;
  temp=cursor;
  (*cursor).next = (InstrType*)(malloc(mallocType));
  if(cursor->next == NULL) {
    exitThingy(fInStream,fInstructStream, fOutStream, superhead);
    exit(EXIT_FAILURE);
  }
  cursor = (*cursor).next;
  (*cursor).type = 'I';
  (*cursor).count=0;
  (*cursor).prev = temp;
  (*cursor).head = headInstr;
  temp = cursor;
  (*cursor).next = (InstrType*)(malloc(mallocType));
  if(cursor->next == NULL) {
    exitThingy(fInStream,fInstructStream, fOutStream, superhead);
    exit(EXIT_FAILURE);
  }
  cursor = (*cursor).next;
  (*cursor).type = 'J';
  (*cursor).count=0;
  (*cursor).prev = temp;
  (*cursor).head = headInstr;
  (*cursor).next = NULL;
  return head;
}

void printNode(Instr *cursor) {
  if(cursor==NULL)
    return;
  else {
    printf("%p uid: %x, pretty: %d, mnemonic: %s, next: %p, prev: %p\n",cursor,cursor->uid,cursor->pretty, cursor->mnemonic,cursor->next,cursor->prev);
    cursor = cursor->next;
    printNode(cursor);
    return;
  }
}

void printList(InstrType *cursor) {
  if(cursor==NULL)
    return;
  else {
    printf("%c-Type Count: %lu, List : \n",cursor->type, cursor->count);
    printNode(cursor->head);
    cursor = cursor->next;
    printList(cursor);
    return;
  }
}

Instr* addInstrToList(Instr *head, uint32_t uid, char* name, uint32_t pretty) {
  Instr *cursor, *temp;
  cursor = head;
  if(cursor == NULL) {
    cursor = malloc(sizeof(uid) + sizeof(name) + sizeof(pretty) + (sizeof(Instr*)*2));
    if(cursor == NULL) {
      exitThingy(fInStream,fInstructStream, fOutStream, superhead);
      exit(EXIT_FAILURE);
    }
    cursor->uid = uid;
    cursor->mnemonic = name;
    cursor->pretty=pretty;
    cursor->prev=NULL;
    cursor->next=NULL;
    return cursor;
  }
  else {
    if(cursor->prev == NULL) {
      if(strcmp(cursor->mnemonic,name)==1) {
        temp = cursor;
        cursor = malloc(sizeof(uid) + sizeof(name) + sizeof(pretty) + (sizeof(Instr*)*2));
        if(cursor == NULL) {
          exitThingy(fInStream,fInstructStream, fOutStream, superhead);
          exit(EXIT_FAILURE);
        }
        cursor->uid = uid;
        cursor->mnemonic = name;
        cursor->pretty=pretty;
        cursor->prev=NULL;
        cursor->next=temp;
        temp->prev=cursor;
        return cursor;
      }
    }
    while(cursor->next != NULL) {
      if(strcmp(cursor->mnemonic,name)==-1 && strcmp(cursor->next->mnemonic,name)>1) {
        temp = cursor->next;
        cursor->next = malloc(sizeof(uid) + sizeof(name) + sizeof(pretty) + (sizeof(Instr*)*2));
        if(cursor->next == NULL) {
          exitThingy(fInStream,fInstructStream, fOutStream, superhead);
          exit(EXIT_FAILURE);
        }
        cursor->next->uid = uid;
        cursor->next->mnemonic = name;
        cursor->next->pretty=pretty;
        cursor->next->prev=cursor;
        cursor->next->next=temp;
        temp->prev = cursor->next;
        return head;
      }
      cursor = cursor->next;
    }
    cursor->next = malloc(sizeof(uid) + sizeof(name) + sizeof(pretty) + (sizeof(Instr*)*2));
    if(cursor->next == NULL) {
      exitThingy(fInStream,fInstructStream, fOutStream, superhead);
      exit(EXIT_FAILURE);
    }
    cursor->next->uid = uid;
    cursor->next->mnemonic = name;
    cursor->next->pretty=pretty;
    cursor->next->prev=cursor;
    cursor->next->next=NULL;
    return head;
  }
}

void addInstr(InstrType *head, char type, uint32_t uid, char* name, uint32_t pretty) {
  Instr* cursor;
  if(type=='r') {
    cursor = head->head;
    head->head = addInstrToList(cursor,uid,name,pretty);
    head->count++;
  }
  else if(type=='i') {
    cursor = head->next->head;
    head->next->head = addInstrToList(cursor,uid,name,pretty);
    head->next->count++;
  }
  else if(type=='j') {
    cursor = head->next->next->head;
    head->next->next->head = addInstrToList(cursor,uid,name,pretty);
    head->next->next->count++;
  }
}

void initInstrList(InstrType *head, FILE *fi) {
  char BUFFER[256];
  char type;
  char *mnemo;
  uint32_t pretty, uid;
  while(!feof(fi)) {
    if(fscanf(fi,"%c %x %s %u\n",&type, &uid, BUFFER, &pretty) ==4){
      mnemo = malloc(strlen(BUFFER));
      if(mnemo == NULL) {
        exitThingy(fInStream,fInstructStream, fOutStream, superhead);
        exit(EXIT_FAILURE);
      }
      strcpy(mnemo,BUFFER);
      addInstr(head,type, uid, mnemo, pretty);\
    }
  }
}


int reverse(int i) {
  int ret=0,j;
  int buffer[4];
  buffer[0] = (i >> 24) & 0xFF;
  buffer[1] = (i >> 16) & 0xFF;
  buffer[2] = (i >> 8) & 0xFF;
  buffer[3] = i & 0xFF;
  ret = 0x00000000;
  for(j=3;j>=0;j--) {
    ret = ret<<8;
    ret+=buffer[j];
  }
  return ret;
}


// int reverse(int i) {
//   int ret=0,j;
//   int buffer[4];
//   buffer[0] = (i >> 24) & 0xFF;
//   buffer[1] = (i >> 8) & 0xFF00;
//   buffer[2] = (i << 8) & 0xFF0000;
//   buffer[3] = (i << 24) & 0xFF000000;
//   ret =buffer[0]+buffer[1]+buffer[2]+buffer[3];
//   printf("\n");
//   return ret;
// }

// int reverse(int num) {
//   int swapped = ((num>>24)&0xff) | // move byte 3 to byte 0
//                     ((num<<8)&0xff0000) | // move byte 1 to byte 2
//                     ((num>>8)&0xff00) | // move byte 2 to byte 1
//                     ((num<<24)&0xff000000); // byte 0 to byte 3
//   return swapped;
// }

Instr* findNode(int uid, Instr*cursor) {
  if(cursor == NULL) {
    return NULL;
  }
  if(uid==cursor->uid) {
    return cursor;
  }
  return findNode(uid,cursor->next);
}

Instr* findInstr(int byte,InstrType *cursor) {
  int uid,func;
  int opcode = byte>>26 & 0x3F;
  if(opcode == 0) {
    func = byte & 0x3F;
    uid = (opcode<<26) + func;
    return findNode(uid, cursor->head);
  }
  else if(opcode == 2 || opcode==3) {
    uid = opcode<<26;
    return findNode(uid, cursor->next->next->head);
  }
  else {
    uid = opcode<<26;
    return findNode(uid, cursor->next->head);
  }
}

void printByte(int i, InstrType* head, FILE* fout) {
  Instr* found;
  int rd,rs,rt,imm16, imm26,shamt;
  found = findInstr(i,head);
  if(found==NULL);
  else {
    rd = i>>11 & 0x0000001F;
    rt = i>>16 & 0x0000001F;
    rs = i>>21 & 0x0000001F;
    shamt = i>>6 & 0x0000001F;
    imm16 = i&0x0000ffff;
    imm26 = i&0x03ffffff;
    if(found->pretty == 0) {
      fprintf(fout,"%s $%s\n",found->mnemonic,numHuman[rd]);
    }
    else if(found->pretty == 1) {
      fprintf(fout,"%s $%s, $%s\n",found->mnemonic,numHuman[rs],numHuman[rt]);
    }
    else if(found->pretty == 2) {
      fprintf(fout,"%s $%s, $%s, 0x%x\n",found->mnemonic,numHuman[rt],numHuman[rs], imm16);
    }
    else if(found->pretty == 3) {
      fprintf(fout,"%s $%s, $%s, $%s\n",found->mnemonic,numHuman[rd],numHuman[rt], numHuman[rs]);
    }
    else if(found->pretty == 4) {
      fprintf(fout,"%s $%s, 0x%x($%s)\n",found->mnemonic,numHuman[rt], imm16,numHuman[rs]);
    }
    else if(found->pretty == 5) {
      fprintf(fout,"%s\n",found->mnemonic);
    }
    else if(found->pretty == 6) {
      fprintf(fout,"%s 0x%x\n",found->mnemonic,imm26);
    }
    else if(found->pretty == 7) {
      fprintf(fout,"%s $%s, 0x%x\n",found->mnemonic,numHuman[rt], imm16);
    }
    else if(found->pretty == 8) {
      fprintf(fout,"%s $%s, $%s, 0x%x\n",found->mnemonic,numHuman[rd], numHuman[rs],shamt);
    }
    else if(found->pretty == 9) {
      fprintf(fout,"%s $%s, $%s, 0x%x\n",found->mnemonic,numHuman[rs],numHuman[rt], imm16);
    }
  }
}

void readFile(FILE *fp, FILE* fout, InstrType* head) {
  int i;
  fread(&i,sizeof(int),1,fp);
  while(!feof(fp)){
    if(reverseflag) i = reverse(i);
    printByte(i, head,fout);
    fread(&i,sizeof(int),1,fp);
  }
}


int main(int argc, char* argv[]) {
  int hflag=0, iflag=0, oflag=0,fLittleFlag = 0,mLittleFlag = 0;
  char insFile[256], inFile[256], outFile[256], bom[4];
  char c;
  struct stat ins, in, out;
  strcpy(insFile,"instruction_mapping.txt");
  while((c= getopt(argc,argv,"hm:i:o:")) != -1) {
    switch(c) {
      case 'h':
        hflag=1;break;
      case 'm':
        strcpy(insFile,optarg);
        break;
      case 'i':
        iflag=1;
        strcpy(inFile, optarg);
        break;
      case 'o':
        oflag=1;
        strcpy(outFile,optarg);
        break;
      default:
        printMenu();
    }
  }
  if(hflag) {
    printMenu();
  }
  if(!iflag || !oflag) {
    exitThingy(fInStream,fInstructStream, fOutStream, superhead);
    return EXIT_FAILURE;
  }
  else {
    stat(outFile,&out);
    stat(inFile,&in);
    stat(insFile,&ins);
    if(out.st_ino == in.st_ino || out.st_ino == ins.st_ino || ins.st_ino == in.st_ino) {
      exitThingy(fInStream,fOutStream,fInStream,superhead);
      return EXIT_FAILURE;
    }
    if(strcmp("-",outFile)==0) {
      fOutStream = stdout;
    }
    else {
      fOutStream = fopen(outFile,"w");
    }

    fInStream = fopen(inFile,"rb");
    fInstructStream = fopen(insFile,"r");
    stat(outFile,&out);
    stat(inFile,&in);
    stat(insFile,&ins);
    if(out.st_ino == in.st_ino || out.st_ino == ins.st_ino || ins.st_ino == in.st_ino) {
      exitThingy(fInStream,fOutStream,fInStream,superhead);
      return EXIT_FAILURE;
    }
    fread(&bom,sizeof(char),4,fInStream);
    if(fOutStream==NULL || fInStream==NULL || fInstructStream==NULL) {
      return EXIT_FAILURE;
    }
    if(htonl(42) != 42) {
      mLittleFlag = 1;
    }
    if(bom[0]!=0x57 || bom[1]!=0x6f || bom[2]!=0x6e || bom[3] != 0x67) {
      fLittleFlag = 1;
    }
    else if(bom[0]!=0x67 || bom[1]!=0x6f || bom[2]!=0x6e || bom[3] != 0x57) {
      fLittleFlag = 0;
    }
    else {
      exitThingy(fInStream,fOutStream,fInStream,superhead);
      return EXIT_FAILURE;
    }
    if(fLittleFlag!=mLittleFlag) {
      reverseflag = 1;
    }
    superhead = initInstrTypeList(superhead);
    initInstrList(superhead,fInstructStream);
    initData();
    readFile(fInStream,fOutStream, superhead);
    exitThingy(fInStream,fInstructStream,fOutStream,superhead);
    return EXIT_SUCCESS;
  }
}
