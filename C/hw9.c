#include <stdio.h>
#include "hw9.h"
#include <stdint.h>
#include <string.h>

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

void printList(InstrType *cursor) {
  if(cursor==NULL)
    return;
  else {
    printf("%c-Type Count: %lo, List: \n",cursor->type, cursor->count);
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
    return cursor;
  }
}

void addInstr(InstrType *head, char type, uint32_t uid, char* name, uint32_t pretty) {
  Instr* cursor;
  if(type=='R') {
    cursor = head->head;
    head->head = addInstrToList(cursor,uid,name,pretty);
  }
  if(type=='I') {
    cursor = head->next->head;
    head->head = addInstrToList(cursor,uid,name,pretty);
  }
  if(type=='J') {
    cursor = head->next->next->head;
    head->head = addInstrToList(cursor,uid,name,pretty);
  }
}

void initInstrList(InstrType *head) {
  char BUFFER[256];
  char type;
  uint32_t pretty, uid;
  FILE *fi = fopen("instruction_mapping.txt","r");
  while(!feof(fi)) {
    if(fscanf(fi,"%c %x %s %u\n",&type, &uid, BUFFER, &pretty) ==4){
      addInstr(head,type, uid, BUFFER, pretty);
    }
  }
}

int main(int argc, char* argv[]) {
  InstrType *head = NULL;
  head = initInstrTypeList(head);
  initInstrList(head);
  printList(head);
  //initInstr(head);
  // char BUFFER[256];
  // char type;
  // int pretty, uid;
  // FILE *fi = fopen("instruction_mapping.txt","r");
  // while(!feof(fi)) {
  //   if(fscanf(fi,"%c %x %s %d\n",&type, &uid, BUFFER, &pretty) ==4){
  //     printf("%c %d %s %d\n",type, uid, BUFFER, pretty);
  //   }
  // }
 return 1;
}
