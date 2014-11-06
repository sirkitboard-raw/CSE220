#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char* createMemory() {
  char *x = malloc(19);
    if(x == NULL)
    {
        return NULL;
    }
    strcpy(x, "CSE 220 Rocks!\0");
    return x;
}

int main() {
  char *p = createMemory();
  char *s = p;
  *(s+4) = 'Q';
  printf("\n%s\n",s);
  return 0;
}
