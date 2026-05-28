#include<stdio.h>
int main(){
  int i,n;
  int fact=1;
  printf("enter the number\n");
  scanf("%d",&n);
  for(i=1;i<=n;i++){
    fact=fact*i;
  }
  printf("fact of %d=%d",n,fact);
  return 0;
}