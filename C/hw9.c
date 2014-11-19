#include <stdio.h>
#include "hw9.h"
#include <stdint.h>
#include <string.h>
#include <netinet/in.h>

int reverseflag;
char numHuman[32][5];

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
  cursor = head;
  (*cursor).type = 'R';
  (*cursor).count=0;
  (*cursor).prev = NULL;
  (*cursor).head = headInstr;
  temp=cursor;
  (*cursor).next = (InstrType*)(malloc(mallocType));
  cursor = (*cursor).next;
  (*cursor).type = 'I';
  (*cursor).count=0;
  (*cursor).prev = temp;
  (*cursor).head = headInstr;
  temp = cursor;
  (*cursor).next = (InstrType*)(malloc(mallocType));
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

void initInstrList(InstrType *head) {
  char BUFFER[256];
  char type;
  char *mnemo;
  uint32_t pretty, uid;
  FILE *fi = fopen("instruction_mapping.txt","r");
  while(!feof(fi)) {
    if(fscanf(fi,"%c %x %s %u\n",&type, &uid, BUFFER, &pretty) ==4){
      mnemo = malloc(strlen(BUFFER));
      strcpy(mnemo,BUFFER);
      addInstr(head,type, uid, mnemo, pretty);
      printf("%c %x %s %u\n",type, uid, BUFFER, pretty);
    }
  }
}


int reverse(int i) {
  int ret=0,j;
  int buffer[4];
  buffer[0] = (i >> 24) & 0x000000FF;
  buffer[1] = (i >> 16) & 0x000000FF;
  buffer[2] = (i >> 8) & 0x000000FF;
  buffer[3] = i & 0x000000FF;
  ret = 0x00000000;
  for(j=3;j>=0;j--) {
    ret = ret<<8;
    ret+=buffer[j];
    printf("%x ",ret);
  }
  printf("\n");
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

void printByte(int i, InstrType* head) {
  Instr* found;
  int rd,rs,rt,imm16, imm26,shamt;
  found = findInstr(i,head);
  if(found==NULL) printf("\n");
  else {
    rd = i>>11 & 0x0000001F;
    rt = i>>16 & 0x0000001F;
    rs = i>>21 & 0x0000001F;
    shamt = i>>6 & 0x0000001F;
    imm16 = i&0x0000ffff;
    imm26 = i&0x03ffffff;
    if(found->pretty == 0) {
      printf("%s $%s\n",found->mnemonic,numHuman[rd]);
    }
    else if(found->pretty == 1) {
      printf("%s $%s, $%s\n",found->mnemonic,numHuman[rs],numHuman[rt]);
    }
    else if(found->pretty == 2) {
      printf("%s $%s, $%s, 0x%x\n",found->mnemonic,numHuman[rt],numHuman[rs], imm16);
    }
    else if(found->pretty == 3) {
      printf("%s $%s, $%s, $%s\n",found->mnemonic,numHuman[rd],numHuman[rt], numHuman[rs]);
    }
    else if(found->pretty == 4) {
      printf("%s $%s, 0x%x($%s)\n",found->mnemonic,numHuman[rt], imm16,numHuman[rs]);
    }
    else if(found->pretty == 5) {
      printf("%s\n",found->mnemonic);
    }
    else if(found->pretty == 6) {
      printf("%s 0x%x\n",found->mnemonic,imm26);
    }
    else if(found->pretty == 7) {
      printf("%s $%s, 0x%x\n",found->mnemonic,numHuman[rt], imm16);
    }
    else if(found->pretty == 8) {
      printf("%s $%s, $%s, 0x%x\n",found->mnemonic,numHuman[rd], numHuman[rs],shamt);
    }
    else if(found->pretty == 9) {
      printf("%s $%s, $%s, 0x%x\n",found->mnemonic,numHuman[rs],numHuman[rt], imm16);
    }
  }
}

void readFile(FILE *fp, InstrType* head) {
  int i;
  fread(&i,sizeof(int),1,fp);
  while(!feof(fp)){
    printf("0x%x\n",i);
    if(reverseflag) i = reverse(i);
    printf("0x%x\n",i);
    printByte(i, head);
    fread(&i,sizeof(int),1,fp);
  }
}

int main(int argc, char* argv[]) {
  InstrType *head = NULL;
  char bom[4];
  int mLittleFlag = 0, fLittleFlag = 0;
  head = initInstrTypeList(head);
  initInstrList(head);
  printList(head);
  if(htonl(42) != 42) {
    mLittleFlag = 1;
  }
  FILE *fp = fopen("program.bin","rb");
  fread(&bom,sizeof(char),4,fp);
  if(bom[0]!=0x57 || bom[1]!=0x6f || bom[2]!=0x6e || bom[3] != 0x67) {
    fLittleFlag = 1;
  }
  if(fLittleFlag!=mLittleFlag) {
    reverseflag = 1;
  }
  initData();
  readFile(fp, head);
  return 1;
}
