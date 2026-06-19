//25.recursive factorial//
#include<stdio.h>
int fact(int);
int main(){
    int n,result;
    printf("enter the number\n");
    scanf("%d",&n);
    result=fact(n);
    printf("the fact is =%d",result);
   return 0;
}
int fact(int n){
  if(n==0)
    return(1);
  else
    return(n*fact(n-1));
  
}

//26.recursive fibonacci//
#include<stdio.h>
int fib(int);
int main(){
  int n,i;
  printf("enter the number\n");
  scanf("%d",&n);
  for(i=0;i<n;i++){
    printf("%d\t",fib(i));
  }
  return 0;
}
int fib(int i){
  if(i==0)
  return 0;
  if(i==1)
  return 1;
  return ((fib(i-1)+fib(i-2)));
}


//27.recursive sum of digits//
#include<stdio.h>
int sum(int n);
int main(){
  int n;
  printf("enter the number\n");
  scanf("%d",&n);
  printf("sum of digits=%d",sum(n));
  return 0;
}
int sum(int n){
  int sum=0;
  while(n>0){
   int ld=n%10;
   sum=sum+ld;
   n=n/10;
} 
return sum;
}

//28.recursion reverse number//
#include<stdio.h>
int rev(int n);
int main(){
  int n;
  printf("enter the number\n");
  scanf("%d",&n);
  printf("rev of number=%d",rev(n));
  return 0;
}
int rev(int n){
  int rev=0;
  while(n>0){
   int ld=n%10;
   rev=rev*10+ld;
   n=n/10;
} 
return rev;
}


