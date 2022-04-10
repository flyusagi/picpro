#include<stdio.h>

int a,b;
int c[9];

typedef struct img_data {
  char magic[3];
  int width;
  int height;
  int max;
  int image[500][500];
  int imageout[500][500];
} img;

img readImg(FILE **infp){
  int i,j;
  img data;
  printf("readimg開始\n");
  fscanf(*infp,"%s",data.magic);
  fscanf(*infp,"%d%d",&data.width,&data.height);
  fscanf(*infp,"%d",&data.max);
  for(i=0;i <= (data.height-1);i++){
    for(j=0;j <= (data.width-1); j++){
      fscanf(*infp,"%d",&data.image[i][j]);
    }
  }

  return data;
}

void writeImg(FILE **outfp, img data){
  int i,j,k,l,tmp;
  fprintf(*outfp,"%s\n",data.magic);
  fprintf(*outfp,"%d %d\n",data.width,data.height);
  fprintf(*outfp,"%d\n",data.max);
  for(i=1;i < (data.height-1);i++){
    for(j=1;j < (data.width-1); j++){
      c[0] = data.image[i-1][j-1];
      c[1] = data.image[i-1][j];
      c[2] = data.image[i-1][j+1];
      c[3] = data.image[i][j-1];
      c[4] = data.image[i][j];
      c[5] = data.image[i][j+1];
      c[6] = data.image[i+1][j-1];
      c[7] = data.image[i+1][j];
      c[8] = data.image[i+1][j+1];
      for(k=0; k<9; k++){
        for(l=k+1; l<9; l++){
          if(c[k] > c[l]){
            tmp = c[k];
            c[k] = c[l];
            c[l] = tmp;
          }
        }
      }
      data.imageout[i][j] = c[4];
    }
  }
  for(i=0; i<=(data.height-1); i++){
    for(j=0; j<=(data.width-1); j++){
      fprintf(*outfp,"%d ",data.imageout[i][j]);
    }
  }
}


int main(){
  char infile[20],outfile[20];
  FILE *infp, *outfp;
  img data;
  printf("input file name ?\n");
  scanf("%s",infile);
  printf("ファイル読み込み完了\n");
  infp = fopen(infile,"r");
  printf("fopen終了\n");
  if(infp == NULL){
    printf("null\n");
  }
  data = readImg(&infp);
  fclose(infp);

  printf("output file name ?\n");
  scanf("%s",outfile);
  outfp = fopen(outfile,"w");
  writeImg(&outfp,data);
  fclose(outfp);
  return 0;
}