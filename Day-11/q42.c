//42.wap to find maximum//
#include<stdio.h>
int maxNum(int a,int b ){
  if(a>b)
  return a;
else
  return b;
}
int main(){
  int a,b,result;
  printf("enter two number\n");
  scanf("%d %d",&a,&b);
  result=maxNum(a,b);
  printf("maxNum=%d",result);
  return 0;
}