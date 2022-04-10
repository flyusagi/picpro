#include<stdio.h>

int width,height;
float bigWidth,bigHeight;

typedef struct img_data {
  char magic[3];
  int width;
  int height;
  int max;
  int image[400][400];
  int imageout[800][800];
} img;

img readImg(FILE **infp){
  int i,j;
  img data;
  printf("readimg開始\n");
  fscanf(*infp,"%s",data.magic);
  fscanf(*infp,"%d%d",&data.width,&data.height);
  printf("width * ? \n");
  scanf("%f",&bigWidth);
  printf("height * ? \n");
  scanf("%f",&bigHeight);
  height = data.height * bigHeight;
  width = data.width * bigWidth;
  fscanf(*infp,"%d",&data.max);
  for(i=0;i <= (data.height-1);i++){
    for(j=0;j <= (data.width-1); j++){
      fscanf(*infp,"%d",&data.image[i][j]);
    }
  }

  return data;
}

void writeImg(FILE **outfp, img data){
  int i,j,u,v;
  float x0,y0,alpha,beta,ans;
  fprintf(*outfp,"%s\n",data.magic);
  fprintf(*outfp,"%d %d\n",width,height);
  fprintf(*outfp,"%d\n",data.max);
  for(i=0;i <= (height-1);i++){
    for(j=0;j <= (width-1); j++){
      x0 = j/bigWidth;
      y0 = i/bigHeight;
      if(i==0 && j==3){
        printf("%f,%f",x0,y0);
      }
      if((0 <= x0 && x0 < data.width - 1) && (0 <= y0 && y0 < data.height - 1)){
        if(i == 0 && j == 3) printf("if==1");
        u = (int)x0;
        v = (int)y0;
        alpha = x0 - u;
        beta = y0 - v;

        ans = (data.image[v][u]*(1-alpha)*(1-beta)) + (data.image[v][u+1]*alpha
        *(1-beta))+(data.image[v+1][u] * (1-alpha) * beta)+(data.image[v+1][u+1] * alpha * beta);

        if(i == 0 && j == 3) printf("ans = %f",ans);

        data.imageout[i][j] = ans;
      }
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