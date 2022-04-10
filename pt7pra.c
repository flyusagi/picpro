#include<stdio.h>

int lim;

typedef struct img_data {
  char magic[3];
  int width;
  int height;
  int max;
  int image[1000][1000];
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
  printf("lim : ?\n");
  scanf("%d",&lim);

  return data;
}

void writeImg(FILE **outfp, img data){
  int i,j;
  fprintf(*outfp,"%s\n",data.magic);
  fprintf(*outfp,"%d %d\n",data.width,data.width);
  fprintf(*outfp,"%d\n",data.max);
  for(i=0;i <= (data.height-1);i++){
    for(j=0;j <= (data.width-1); j++){
      if(data.image[i][j] > lim){
        data.image[i][j] = data.max;
      }else{
        data.image[i][j] = 0;
      }
      fprintf(*outfp,"%d ",data.image[i][j]);
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