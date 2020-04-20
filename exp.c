#include <stdio.h>
#include <stdlib.h>

typedef struct Pgm {
  unsigned int alt,larg;
  char magic[2];
  unsigned char **data;
} Pgm;

Pgm binaliza(Pgm img, unsigned int c);
Pgm normaliza(Pgm img);
Pgm loadPgm(char *filename);
int savePgm(Pgm img, unsigned int c, char *filename);

int main(int argc, char *argv[]){
  Pgm input;
  input = loadPgm(argv[1]);
  savePgm(normaliza(input),255,"output.pgm");
  return 0;
}

Pgm binaliza(Pgm img,unsigned int c){
  for(unsigned int i=0;i<img.alt;i++){
    for(unsigned int j=0;j<img.larg;j++){
      if(img.data[i][j]>c){
        img.data[i][j]=1;
      } else {
        img.data[i][j]=0;
      }
    }
  }
  return img;
}

Pgm normaliza(Pgm img){

  unsigned char ker[3][3];
  float pix_s=0;

  for(unsigned int i=1;i<img.alt-1;i++){
    for(unsigned int j=1;j<img.larg-1;j++){
      //  i-1,j-1  i-1,j  i-1,j+1
      //  i,j-1    i,j    i,j+1
      //  i+1,j-1  i+1,j  i+1,j+1
      for(unsigned int k=i-1;k<=i+1;k++){
        for(unsigned int l=j-1;l<=j+1;l++){
          pix_s+=img.data[k][l];
        }
      }
      img.data[i][j]=(int)(pix_s/9.0);
      pix_s=0;
    }
  }

  return img;
}


Pgm loadPgm(char *filename){
  Pgm img;
  FILE *f = NULL;
  f=fopen(filename, "rb");
  fscanf(f, "%s\n", img.magic);
  if(img.magic[1]=='5'){
    fscanf(f,"%d",&img.larg);
    fscanf(f,"%d",&img.alt);
    img.data=calloc(img.alt,img.alt*sizeof(char*));
    for(unsigned int i=0;i<img.alt;i++){
      img.data[i]=calloc(img.larg,img.larg*sizeof(char));
      for(unsigned int j=0;j<img.larg;j++) fscanf(f,"%c",&img.data[i][j]);
    }
  }
  fclose(f);
  return img;
}

int savePgm(Pgm img, unsigned int c, char *filename){

  FILE *f;
  f=fopen(filename, "wb");
  fprintf(f,"%s %d %d\n%d\n",img.magic,img.larg,img.alt,c);
  for(unsigned int i=0;i<img.alt;i++){
    for(unsigned int j=0;j<img.larg;j++){
      fprintf(f,"%c",img.data[i][j]);
    }
  }
  fclose(f);
  return 0;
}
