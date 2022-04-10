#include<stdio.h>

typedef struct img_data {
  char magic[3];
  int width;
  int height;
  int max;
  float image[500][500];
  float imageout[500][500];
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
    }
  }

  return data;
}

void writeImg(FILE **outfp, img data){
  int i,j,k,l,bsize;
  float avg;
  scanf("%d",&bsize);
  fprintf(*outfp,"%s\n",data.magic);
  fprintf(*outfp,"%d %d\n",data.width,data.height);
  fprintf(*outfp,"%d\n",data.max);
  for(i=0;i <= (data.height-bsize);i += bsize){
    for(j=0;j <= (data.width-bsize); j += bsize){
      avg = 0;
      for(k = i;k <= i+bsize-1;k++){
        for(l = j;l <= j+bsize-1;l++){
          avg += data.image[k][l];
        }
      }
      avg = avg / (bsize*bsize);
      printf("avg = %f",avg);
      for(k = i;k <= i+bsize-1;k++){
        for(l = j;l <= j+bsize-1;l++){
          data.imageout[k][l] = avg;
        }
      }
      }
    }
  for(i=0; i<=(data.height-1); i++){
    for(j=0; j<=(data.width-1); j++){
      fprintf(*outfp,"%d ",(int)data.imageout[i][j]);
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