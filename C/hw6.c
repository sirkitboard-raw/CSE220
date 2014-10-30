#include<stdio.h>
#define HELP "\t-h\tDisplays this help menu\n\t-i\tDisplays statistics about instructions type usages.\n\t-m\tDisplays all the immediate values used in I-Type and J-Type instructions\n\t-r\tDisplays information about the registers\n\t-uDisplays human readable headers for different information displayed.\n\t\tShould only be used with the -i, -r, and -m flags."

int main(int argc, char *argv[]) {
  if(argc ==0) {
    printf("%s\n",HELP);
    return 4;
  }
  else {
    if(argc==1) {
      if(argv[1]=='h'){
        printf("%s\n",HELP);
        return 0;
      }
    }
  }
}
