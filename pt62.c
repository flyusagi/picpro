#include<stdio.h>
#include<math.h>

int width,height,cx,cy;
float a,b,c,d,e,f;

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
  printf("a,b,c,d,e,f ?\n");
  scanf("%f%f%f%f%f%f",&a,&b,&c,&d,&e,&f);
  height = data.height * e;
  width = data.width * a;
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
  fprintf(*outfp,"%d %d\n",width,height);
  fprintf(*outfp,"%d\n",data.max);
  for(y=0;y <= (height-1);y++){
    for(x=0;x <= (width-1); x++){
      x0 = (1/(a*e-b*d)) * (e*x - b*y) + (1/(a*e-b*d)) *(b*f-e*c);
      if(x == 2 && y == 0) printf("%f",x0);
      y0 = (1/(a*e-b*d)) * (a*y-d*x) + (1/(a*e-b*d)) *(d*c-a*f);
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