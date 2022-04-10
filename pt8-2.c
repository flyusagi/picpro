#include<stdio.h>

float a,b;
int label = 1;

typedef struct img_data {
  char magic[3];
  int width;
  int height;
  int max;
  int image[500][500];
} img;

img data;


void readImg(FILE **infp){
  int i,j;
  printf("readimg開始\n");
  fscanf(*infp,"%s",data.magic);
  fscanf(*infp,"%d%d",&data.width,&data.height);
  fscanf(*infp,"%d",&data.max);
  for(i=0;i <= (data.height-1);i++){
    for(j=0;j <= (data.width-1); j++){
      fscanf(*infp,"%d",&data.image[i][j]);
    }
  }
}

void writelabel(int i, int j, int label){
  data.image[i][j] = label;
  if(i != 0 && j != 0){
    if(data.image[i-1][j-1] == data.max){
      writelabel(i-1,j-1,label);
    }
    if(data.image[i-1][j] == data.max){
      writelabel(i-1,j,label);
    }
    if(data.image[i-1][j+1] == data.max){
      writelabel(i-1,j+1,label);
    }
    if(data.image[i][j-1] == data.max){
      writelabel(i,j-1,label);
    }
    if(data.image[i][j+1] == data.max){
      writelabel(i,j+1,label);
    }
    if(data.image[i+1][j-1] == data.max){
      writelabel(i+1,j-1,label);
    }
    if(data.image[i+1][j] == data.max){
      writelabel(i+1,j,label);
    }
    if(data.image[i+1][j+1] == data.max){
      writelabel(i+1,j+1,label);
    }
  }
}

void writeImg(FILE **outfp){
  int i,j;
  fprintf(*outfp,"%s\n",data.magic);
  fprintf(*outfp,"%d %d\n",data.width,data.height);
  fprintf(*outfp,"%d\n",data.max);
  for(i = 0;i < data.height ;i++){
    for(j = 0;j < data.width;j++){
      if(data.image[i][j] == data.max){
        writelabel(i,j,label);
        label++;
      }
    }
  }
  for(i=0;i <= (data.height-1);i++){
    for(j=0;j <= (data.width-1); j++){
      if(data.image[i][j] < a || (i == 0 && j == 0) ){
        a = data.image[i][j];
      }
      if(data.image[i][j] > b || (i == 0 && j == 0)){
        b = data.image[i][j];
      }
    }
  }
  for(i=0;i <= (data.height-1);i++){
    for(j=0;j <= (data.width-1); j++){
      data.image[i][j] = (data.image[i][j]-a)/(b-a) * data.max;
      fprintf(*outfp,"%d ",(int)data.image[i][j]);
    }
  }
}


int main(){
  char infile[20],outfile[20];
  FILE *infp, *outfp;
  printf("input file name ?\n");
  scanf("%s",infile);
  printf("ファイル読み込み完了\n");
  infp = fopen(infile,"r");
  printf("fopen終了\n");
  if(infp == NULL){
    printf("null\n");
  }
  readImg(&infp);
  fclose(infp);
  printf("output file name ?\n");
  scanf("%s",outfile);
  outfp = fopen(outfile,"w");
  writeImg(&outfp);
  fclose(outfp);
  return 0;
} 