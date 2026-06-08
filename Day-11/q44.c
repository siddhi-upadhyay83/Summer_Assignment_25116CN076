//wap to find factorial using function//
#include<stdio.h>
int fact(int n){
  int i,fact=1;
  for(i=1;i<=n;i++){
    fact=fact*i;
  }
    return fact;
}
int main(){
  int result,n;
  printf("enter the number\n");
  scanf("%d",&n);
  result=fact(n);
  printf("factorial of %d=%d",n,result);
  return 0;
}