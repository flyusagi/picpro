#include<stdio.h>

float a,b;

typedef struct img_data {
  char magic[3];
  int width;
  int height;
  int max;
  float image[1000][1000];
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
      fscanf(*infp,"%f",&data.image[i][j]);
      if(data.image[i][j] < a || (i == 0 && j == 0) ){
        a = data.image[i][j];
      }
      if(data.image[i][j] > b || (i == 0 && j == 0)){
        b = data.image[i][j];
      }
    }
  }

  printf("min:%f,max:%f\n",a,b);
  return data;
}

void writeImg(FILE **outfp, img data){
  int i,j;
  fprintf(*outfp,"%s\n",data.magic);
  fprintf(*outfp,"%d %d\n",data.width,data.width);
  fprintf(*outfp,"%d\n",data.max);
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