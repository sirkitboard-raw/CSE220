#include<stdio.h>
#define HELP "\t-h\tDisplays this help menu\n\t-i\tDisplays statistics about instructions type usages.\n\t-m\tDisplays all the immediate values used in I-Type and J-Type instructions\n\t-r\tDisplays information about the registers\n\t-u\tDisplays human readable headers for different information displayed.\n\t\tShould only be used with the -i, -r, and -m flags."

void printHelp() {
  printf("%s\n",HELP);
}

int main(int argc, char *argv[]) {
  if(argc == 1) {
    printHelp();
    return 4;
  }
  else {
    if(argc==2) {
      if(argv[1][1]=='h'){
        printHelp();
        return 0;
      }
      else {
        printHelp();
        return 4;
      }
    }
  }
  return 100;
}
