//wap for armstrong using function//
// wap for palindrome using function //
#include<stdio.h>
int armstrongOfNum(int num){
        int sum=0,ld;
        int temp=num;
        while(num>0){
          ld= num%10;
          sum=sum+ld*ld*ld;
          num/=10;
        }
        if(sum==temp){
          printf("%d is armstrong ",temp);
        }else{
         printf("%d is not armstrong",temp);
        }
        return 0;
}
int main(){
     int num;
     printf("enter the number\n");
     scanf("%d",&num);
  armstrongOfNum(num);
}