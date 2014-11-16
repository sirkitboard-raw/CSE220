#include <netinet/in.h>
#include <stdio.h>

void main() {
    if(htonl(42) == 42) {
      printf("Big E");
    }
    else {
      printf("Little E");
    }
}
