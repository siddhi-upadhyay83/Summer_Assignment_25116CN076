//wap for fibonacci series//
#include<stdio.h>
int fibNum(int num){
  int a=0,b=1;
  printf("%d %d ",a,b);
  for(int i=0;i<num-2;i++){
    int sum=a+b;
     printf("%d ",sum);
     a=b;
     b=sum;
  }
  return 0;
}
int main(){
  int num;
  printf("enter the no. of terms\n");
  scanf("%d",&num);
  fibNum(num);
}