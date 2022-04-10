#include<stdio.h>

int lim;
float n[300];
/* var = 分散 omega = ω avg = μ  avgt = μt*/
float var = 0;
float tmp,omega,avg,avgt;

typedef struct img_data {
  char magic[3];
  int width;
  int height;
  int max;
  int image[1000][1000];
} img;

void calcLim(img data){
  int i,j,k;
  float alln = data.height * data.width;
  /* クラス間分散が最大のときのkをlimとする*/

  /* niを求める */
  for(k = 0;k <= data.max ; k++){
    n[k] = 0;
  }
  for(i = 0;i < data.height; i++){
    for(j = 0;j< data.width ; j++){
      n[data.image[i][j]]++;
    }
  }
  printf("n90 = %f\n",n[90]);

  /* μtを求める */
  for(i = 0; i<= data.max ; i++){
    avgt += i * (n[i]/alln);
  }

  /* kの値からμ(k),ω(k)を求め、分散を求める */
  for(k = 0;k <= (data.max-1) ; k ++){
    for(i = 0; i <= k; i++){
      avg += i * (n[i]/alln);
    }
    if(k == 75 || k == 90) printf("%f\n",avg);
    for(i = 0; i <= k; i++){
      omega += (n[i]/alln);
      printf("i = %d , omega = %f\n",i,omega);
    }
    if(k == 75 || k == 90) printf("%f\n",omega);
    if((omega * (1-omega)) > 0){
      tmp = ((avgt * omega - avg) * (avgt * omega -avg)) / (omega * (1-omega));
      if(k == 75 || k == 90) printf("%f\n",tmp);
    }
    if(tmp > var){
      var = tmp;
      lim = k;
    }
    omega = 0;
    avg = 0;
    
  }




}

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
  
  calcLim(data);
  printf("分散は %d です\n",lim);

  printf("output file name ?\n");
  scanf("%s",outfile);
  outfp = fopen(outfile,"w");
  writeImg(&outfp,data);
  fclose(outfp);
  return 0;
}