#include<stdio.h>
#include<math.h>

int width,height,cx,cy;
float rad,c,s;

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
  printf("rad ? \n");
  scanf("%f",&rad);
  printf("cx ?\n");
  scanf("%d",&cx);
  printf("cy ?\n");
  scanf("%d", &cy);
  c = cos(rad * M_PI / 180);
  s = sin(rad * M_PI / 180);
  fscanf(*infp,"%d",&data.max);
  for(i=0;i <= (data.height-1);i++){
    for(j=0;j <= (data.width-1); j++){
      fscanf(*infp,"%d",&data.image[i][j]);
    }
  }

  return data;
}

void writeImg(FILE **outfp, img data){
  int y,x,u,v;
  float x0,y0,alpha,beta,ans;
  fprintf(*outfp,"%s\n",data.magic);
  fprintf(*outfp,"%d %d\n",data.width,data.height);
  fprintf(*outfp,"%d\n",data.max);
  for(y=0;y <= (data.height-1);y++){
    for(x=0;x <= (data.width-1); x++){
      x0 = c * (x-cx) + s * (y - cy) + cx;
      y0 = -s*(x-cx) + c * (y - cy)+ cy;
      if((0 <= x0 && x0 < data.width - 1) && (0 <= y0 && y0 < data.height - 1)){
        u = (int)x0;
        v = (int)y0;
        alpha = x0 - u;
        beta = y0 - v;

        ans = (data.image[v][u]*(1-alpha)*(1-beta)) + (data.image[v][u+1]*alpha
        *(1-beta))+(data.image[v+1][u] * (1-alpha) * beta)+(data.image[v+1][u+1] * alpha * beta);

        data.imageout[y][x] = ans;
      }
      fprintf(*outfp,"%d ",data.imageout[y][x]);
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