//13.generate fibonacci series
#include<stdio.h>
int main(){
 int i,n,a=0,b=1,sum=a+b;
  printf("enter the number of terms\n");
  scanf("%d",&n);
  printf("%d %d",a,b);
  for(i=1;i<=n-2;i++){
    printf(" %d",sum);
    a=b;
    b=sum;
    sum=a+b;

  }
  return 0;
}
 

//14.find nth term of fibonacci series//
#include<stdio.h>
int main(){
  int n,a=0,b=1,i,temp;
  printf("enter the term number\n");
  scanf("%d",&n);
  for (i=1;i<=n;i++){
    temp=a+b;
    a=b;
    b=temp;
  }
  printf("fibonacci(%d)=%d",n,a);
  return 0;
}

//15.check armstrong number//
#include<stdio.h>
int main(){
  int n,ld,sum=0,temp;
  printf("enter the number\n");
  scanf("%d",&n);
  temp=n;
  while(n>0){
    ld=n%10;
    sum=sum+ld*ld*ld;
    n=n/10;
  }if(sum==temp){
    printf("yes,given number is an armstrong number");
  }else{
    printf("no,given number is not an armstrong number");
  }
  return 0;
}

//16.check armstrong number in a range//
#include<stdio.h>
int main(){
  int i,n1,n2,ld,sum,temp;
  printf("enter the range\n");
  scanf("%d%d",&n1,&n2);
  printf("armstrong numbers between %d and %d are:\n",n1,n2);
  for(i=n1;i<=n2;i++){
    temp=i;
    sum=0;
    while(temp>0){
      ld=temp%10;
      sum=sum+ld*ld*ld;
      temp=temp/10;
    }if(sum==i){
      printf("%d\n",i);
    }
  }
  return 0;
}