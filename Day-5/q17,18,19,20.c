//17.check perfect number or not//
#include<stdio.h>
int main(){
    int n,sum=0;
    printf("Enter a number:\n");
    scanf("%d",&n);
    for(int i=1;i<n;i++) {
        if(n%i==0) {
            sum=sum+i;
        }
      }
    if(sum==n){
        printf("%d is a perfect number",n);
    }else {
        printf("%d is not a perfect number",n);
    }
    return 0;
}

//18.check strong number or not//
#include<stdio.h>
int main(){
    int n,sum=0,temp,r,fact;
    printf("Enter a number:\n");
    scanf("%d",&n);
    temp=n;
    while(temp>0) {
        r=temp%10;
        fact=1;
        for(int i=1;i<=r;i++) {
            fact=fact*i;
        }
        sum=sum+fact;
        temp=temp/10;
    }
    if(sum==n){
        printf("%d is a strong number",n);
    }else {
        printf("%d is not a strong number",n);
    }
    return 0;
}

//19.print factors of a number//
#include<stdio.h>
int main(){
    int n;
    printf("Enter a number:\n");
    scanf("%d",&n);
    printf("Factors of %d are:\n",n);
    for(int i=1;i<=n;i++) {
        if(n%i==0) {
            printf("%d ",i);
        }
    }
    return 0;
}

//20.find largest prime factor of a number//
#include<stdio.h>
int main(){
    int n,largest=0;
    printf("Enter a number:\n");
    scanf("%d",&n);
    for(int i=2;i<=n;i++) {
        while(n%i==0) {
            largest=i;
            n=n/i;
        }
    }
    if(largest==0) {
        printf("No prime factor found");
    }else {
        printf("Largest prime factor is %d",largest);
    }
    return 0;
}