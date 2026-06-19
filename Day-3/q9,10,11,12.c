//9.check prime no.//
#include<stdio.h>
int main(){
  int n,i,prime=0;
  printf("enter the number\n");
  scanf("%d",&n);
  for(i=2;i<=n/2;i++){
    if(n%i==0){
      prime=1;
      break;
    }
  }if(prime==0){
    printf("the given number is prime");
  }else{
    printf("the given number is not prime");
  }
  return 0;
}

//10.print prime numbers in a range//
#include<stdio.h>
int main(){
  int i,j,n1,n2,prime=0;
  printf("enter the range\n");
  scanf("%d %d",&n1,&n2);
  for(i=n1;i<=n2;i++){
    prime=0;
    for(j=2;j<=i/2;j++){
      if(i%j==0){
        prime=1;
        break;
      }
    }if(prime==0 && i!=1){
      printf("%d ",i);
    }
  }
  return 0;
}

//11.find gcd of a number//
#include<stdio.h>
int gcd(int a,int b){
  if(b!=0){
    int temp=b;
    b=a%b;
    a=temp;
  }
  return a;
}
int main(){
  int a,b;
  printf("enter two numbers\n");
  scanf("%d %d",&a,&b);
  if(a<0) a=-a;
  if(b<0) b=-b;
  printf("gcd of %d and %d is=%d",a,b,gcd(a,b));
  return 0;
}

//12.find lcm of a number//
#include<stdio.h>
int gcd(int a,int b){
  if(b!=0){
    int temp=b;
    b=a%b;
    a=temp;
  }
  return a;
}
int main(){
  int a,b;
  printf("enter two numbers\n");
  scanf("%d %d",&a,&b);
  if(a<0) a=-a;
  if(b<0) b=-b;
  printf("lcm of %d and %d is=%d",a,b,(a*b)/gcd(a,b));
  return 0;
}