//41.wap to print sum of two number//
#include<stdio.h>
int sum(int a,int b){
  return a+b;
}
int main(){
  int a,b,sum;
  printf("enter two numbers\n");
  scanf("%d %d",&a,&b);
  sum=suma(a+b);
  printf("sum of %d and %d=%d",a,b,sum);
  return 0;
}

