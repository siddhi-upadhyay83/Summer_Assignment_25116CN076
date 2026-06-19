//21.covert decimal to binary//
#include<stdio.h>
int main(){
  int ans=0,n,ld,contribution=1;
  printf("Enter a decimal number:\n ");
  scanf("%d",&n);
  while(n>0){
    ld=n%2;
    ans=ans+ld*contribution;
    n=n/2;
    contribution=contribution*10;
  }
  printf("Binary equivalent: %d",ans);
  return 0;
}

//22.convert binary to decimal//
#include<stdio.h>
int main(){
  int ans=0,n,ld,contribution=1;
  printf("Enter a binary number:\n ");
  scanf("%d",&n);
  while(n>0){
    ld=n%10;
    ans=ans+ld*contribution;
    n=n/10;
    contribution=contribution*2;
  }
  printf("Decimal equivalent: %d",ans);
  return 0;
}

//23.count set bits in a number//
#include<stdio.h>
int main(){
  int n,count=0;
  printf("Enter a number:\n ");
  scanf("%d",&n);
  while(n>0){
    if(n%2==1){
      count++;
    }
    n=n/2;
  }
  printf("Number of set bits: %d",count);
  return 0;
}

//24.find x^n without using pow function//
#include<stdio.h>
int main(){
  int x,n,ans=1;
  printf("Enter base and exponent:\n ");
  scanf("%d%d",&x,&n);
  for(int i=1;i<=n;i++){
    ans=ans*x;
  }
  printf("%d^%d = %d",x,n,ans);
  return 0;
}