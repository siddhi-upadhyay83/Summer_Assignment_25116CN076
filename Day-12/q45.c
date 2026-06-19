// wap for palindrome using function //
#include<stdio.h>
int palindromeOfNum(int num){
        int rev=0,ld;
        int temp=num;
        while(num>0){
          ld= num%10;
          rev=rev*10+ld;
          num/=10;
        }
        if(rev==temp){
          printf("%d is palindrome",temp);
        }else{
         printf("%d is not palindrome",temp);
        }
        return 0;
}
int main(){
     int num;
     printf("enter the number\n");
     scanf("%d",&num);
  palindromeOfNum(num);
}