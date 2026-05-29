//5.sum of digits of a number//
#include<stdio.h>
int main(){
  int ld,sum=0,n;
  printf("enter the number\n");
  scanf("%d",&n);
  while(n>0){
  ld=n%10;
  sum=sum+ld;
  n=n/10;
  }
  printf("%d",sum);
  return 0;
}

//6.reverse of a number//
#include<stdio.h>
int main(){
  int n,ld,rev=0;
  printf("enter the number\n");
  scanf("%d",&n);
  while(n>0){
    ld=n%10;
    rev=rev*10+ld;
    n=n/10;
  }
  printf("%d",rev);
    return 0;
}

//7.product of digits//
#include<stdio.h>
int main(){
  int n,ld,prod=1;
  printf("enter the number\n");
  scanf("%d",&n);
  while(n>0){
    ld=n%10;
    prod=prod*ld;
    n=n/10;
  }
  printf("%d",prod);
  return 0;
}

//8.check whtether the no is palindrome //
#include<stdio.h>
int main(){
  int n,ld,rev=0,temp=n;
  printf("enter the number\n");
  scanf("%d",&n);
  while(n>0){
    ld=n%10;
    rev=rev*10+ld;
    n=n/10;
  }if(rev==temp){
    printf("the given number is palindrome");
  }else{
    printf("the given number is not palindrome");
  }
  return 0;
}