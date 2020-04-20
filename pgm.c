#include <stdio.h>
#include <stdlib.h>

int main(int *argc, char **argv){
  FILE *f = NULL;

  f=fopen(argv[1], "wb");
  fprintf(f,"P5%d%d%d", 255, 255, 255);
  for(int i=0; i<256; i++){
    for(int j=0;j<256;j++){
//      if(j<255) {fprintf(f,"%d",j);}
//      else {fprintf(f,"%d",j);}
      fprintf(f,"%d",j);
    }
  }
  fclose(f);
  return 0;
}
