#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEF_LARG 100
#define DEF_ALT 100

typedef struct Pgm {
  unsigned int alt,larg;
  char magic[2];
  unsigned char **data;
} Pgm;

Pgm generateNoise(Pgm img);
Pgm binariza(Pgm img, unsigned int c);
Pgm normaliza(Pgm img);
Pgm loadPgm(char *filename);
int savePgm(Pgm img, unsigned int c, char *filename);
Pgm drawCircle(Pgm img,unsigned int x,unsigned int y,unsigned int r);

int main(int argc, char *argv[]){

  // initiate (and save) blank image
  Pgm img = loadPgm("blank.pgm");

  // generates a circle (x,y,r)
  Pgm circle = drawCircle(img,50,50,30);
  // add noise
  Pgm circle_noise = generateNoise(circle);
  savePgm(circle_noise,255,"noisecircle.pgm");

  // try to remove
  Pgm no_noise = binariza(normaliza(circle_noise),140);
  savePgm(no_noise,255,"no_noise.pgm");

//  Pgm noise = generateNoise(loadPgm(argv[1]));
//  savePgm(noise,255,"noise.pgm");
//
//  // draw circle over noise
//  Pgm noise_circle = drawCircle(noise,100,100,50);
//  savePgm(noise_circle,255,"noise_circle.pgm");

  // tries to remove noise around circle

  return 0;
}

Pgm generateNoise(Pgm img){
  srand(123);
  for(unsigned int i=0;i<img.alt;i++){
    for(unsigned int j=0;j<img.larg;j++){
      img.data[i][j]=(2*img.data[i][j]+rand()%255)/3;
    }
  }
  return img;
}

Pgm drawCircle(Pgm img,unsigned int x,unsigned int y,unsigned int r){

  if(x<img.larg && y<img.alt && r>0){
    // x**2 + y**2 = r**2
    for(unsigned int i=0;i<img.alt;i++){
      for(unsigned int j=0;j<img.larg;j++){
        if((x-i)*(x-i) + (y-j)*(y-j) <= r*r) img.data[i][j]=255;
        // (x-i)**2 + (y-j)**2 = r**2
      }
    }
  }

  return img;
}

Pgm binariza(Pgm img,unsigned int c){
  for(unsigned int i=0;i<img.alt;i++){
    for(unsigned int j=0;j<img.larg;j++){
      if(img.data[i][j]>c){
        img.data[i][j]=255;
      } else {
        img.data[i][j]=0;
      }
    }
  }
  return img;
}

Pgm normaliza(Pgm img){
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
  FILE *f;
  f=fopen(filename, "w+b");
  if(f!=NULL){
    fscanf(f, "%s\n", img.magic);
    if(img.magic[1]=='5'){
      fscanf(f,"%d",&img.larg);
      fscanf(f,"%d",&img.alt);
      img.data=calloc(img.alt,img.alt*sizeof(char*));
      for(unsigned int i=0;i<img.alt;i++){
        img.data[i]=calloc(img.larg,img.larg*sizeof(char));
        for(unsigned int j=0;j<img.larg;j++) fscanf(f,"%c",&img.data[i][j]);
      }
    } else {
      img.larg=DEF_LARG; img.alt=DEF_ALT;
      strcpy(img.magic,"P5");
      img.data=calloc(img.alt,img.alt*sizeof(char*));
      for(unsigned int i=0;i<img.alt;i++){
        img.data[i]=calloc(img.larg,img.larg*sizeof(char));
      }
    }
    fclose(f);
  }
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

