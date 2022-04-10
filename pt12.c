#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int best_x,best_y;
int minD;
int h,w;

typedef struct img_data {
  char magic[3];
  int width;
  int height;
  int max;
  int image[500][500];
} img;

img data,t;

void readTmp(){
  int i , j, n, m,d,wb;
  char infile[20];
  FILE *infp;
  /* テンプレートファイルを読み込む */
  printf("input template file name ?\n");
  scanf("%s",infile);
  infp = fopen(infile,"r");
  fscanf(infp,"%s",t.magic);
  fscanf(infp,"%d%d",&t.width,&t.height);
  fscanf(infp,"%d",&t.max);
  for(i=0;i <= (t.height-1);i++){
    for(j=0;j <= (t.width-1); j++){
      fscanf(infp,"%d",&t.image[i][j]);
    }
  }
  h = t.height;
  w = t.width;
  minD = INT_MAX;
  for(i = 0;i <= data.height - h;i++){
    for(j = 0;j <= data.width - w;j++){
      d = 0;
      wb = 0;
      for(m = 0;m < h;m++){
        if(wb) break;
        for(n = 0;n < w ;n++){
          d += abs(data.image[i+m][j+n] - t.image[m][n]);
          if(d > minD){
            wb = 1;
            break;
          }
        }
      }
      if(d < minD){
        minD = d;
        best_x = j;
        best_y = i;
      }
    }
  }
  printf("bestx = %d , besty = %d\n",best_x,best_y);
  fclose(infp);
}

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

void writeImg(FILE **outfp, FILE **tefp){
  int i,j;
  fprintf(*outfp,"%s\n",data.magic);
  fprintf(*outfp,"%d %d\n",data.width,data.height);
  fprintf(*outfp,"%d\n",data.max);
  
  //carteを書き出す
  fprintf(*tefp,"%s\n",data.magic);
  fprintf(*tefp,"%d %d\n",w,h);
  fprintf(*tefp,"%d\n",data.max);
  for(i = best_y; i < best_y+h;i++){
    for(j=best_x;j < best_x+w; j++){
      fprintf(*tefp,"%d ",data.image[i][j]);
    }
  }

  for(j = best_x; j < best_x+w ; j++){
    data.image[best_y][j] = data.max;
    data.image[best_y + h][j] = data.max;
  }
  for ( i = best_y; i < best_y+h; i++){
    data.image[i][best_x] = data.max;
    data.image[i][best_x+w] = data.max;
  }
  for(i=0;i <= (data.height-1);i++){
    for(j=0;j <= (data.width-1); j++){
      fprintf(*outfp,"%d ",data.image[i][j]);
    }
  }


}


int main(){
  char infile[20],outfile[20];
  FILE *infp, *outfp,*tefp;
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
  readTmp();

  printf("output file name ?\n");
  scanf("%s",outfile);
  outfp = fopen(outfile,"w");
  tefp = fopen("carte.pgm","w");
  writeImg(&outfp,&tefp);
  fclose(outfp);
  fclose(tefp);
  printf("minD = %d\n",minD);
  return 0;
} 