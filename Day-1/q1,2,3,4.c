//1.sum of natural number
#include<stdio.h>
int main(){
  int n,i,sum=0;
  printf("enter the natural no.\n");
  scanf("%d",&n);
  for(i=1;i<=n;i++){
    sum=sum+i;
  }
  printf("sum=%d",sum);
  return 0;
}

//2.multiplicatioin table
#include<stdio.h>
int main(){
  int i,n;
  printf("enter the number\n");
  scanf("%d",&n);
  for(i=n;i<=10*n;i=i+n){
    printf("%d ",i);
  }
  return 0;
}

//3.factorial of a number
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

//4.count digits in a number//
#include<stdio.h>
int main(){
  int n;
  printf("enter a number\n");
  scanf("%d ",&n);
  int count=0;
  while (n!=0){
    n=n/10;
    count++;
  }
  printf("the number of digits are=%d",count);
  return 0;

}