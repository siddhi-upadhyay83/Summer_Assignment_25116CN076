//wap to to check prime using function//
#include<stdio.h>
int isPrime(int n){
  int i;
  if(n<=1)
  return 0;
  for(i=2;i<=n/2;i++){
    if(n%i==0)
    return 0;
  }
  return 1;
}
int main(){
  int n;
  printf("enter a number\n");
  scanf("%d",&n);
  if(isPrime(n))
     printf("%d is prime\n",n);
  else
    printf("%d is not prime\n",n);
    return 0;
}