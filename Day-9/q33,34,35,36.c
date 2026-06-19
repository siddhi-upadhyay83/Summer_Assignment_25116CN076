//33.print reverse star print//
#include<stdio.h>
int main(){
  int n=5;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n+1-i;j++){
      printf("*");
    }
    printf("\n");
  }
  return 0;
}

//34.print reverse number//
#include<stdio.h>
int main(){
    int n=5;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n+1-i;j++){
      printf("%d",j);
    }
    printf("\n");
  }
  return 0;
}

//35.print repeated character//
#include<stdio.h>
int main(){
    int i, j, n = 5;
    for(i = 0; i < n; i++){
        for(j = 0; j <= i; j++){
            printf("%c", 'A' + i);
        }
        printf("\n");
    }
    return 0;
}

//36.print hollow square pattern//
#include<stdio.h>
int main(){
    int i, j, n = 5;
    for(i = 1; i <= n; i++){
        for(j = 1; j <= n; j++){
            if(i == 1 || i == n || j == 1 || j == n)
                printf("* ");
            else
                printf("  ");
        }
        printf("\n");
    }
    return 0;
}