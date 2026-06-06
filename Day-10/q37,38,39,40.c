//37.print star pyramid//
#include<stdio.h>
int main(){
  int i,j,k,n=5;
  for(i = 1; i <= n; i++){
    for(j = i;j < n; j++){
      printf(" ");
    }
    for(k = 1; k <= (2*i-1); k++){
      printf("*");
    }
    printf("\n");
  }
  return 0;
}

//38.print reverse pyramid//
#include<stdio.h>
int main(){
  int i,j,k,n=5;
  for(i = n; i >= 1; i--){
    for(j = i;j < n; j++){
      printf(" ");
    }
    for(k = 1; k <= (2*i-1); k++){
      printf("*");
    }
    printf("\n");
  }
  return 0;
}

//39.print number pyramid//
#include<stdio.h>
int main(){
    int i, j, n = 4;
    for(i = 1; i <= n; i++){
        for(j = i; j < n; j++){
            printf(" ");
        }
        for(j = 1; j <= i; j++){
            printf("%d ", j);
        }
        for(j = i-1; j >= 1; j--){
            printf("%d ", j);
        }
        printf("\n");
    }
    return 0;
}

//40.print character pyramid//
#include<stdio.h>
int main(){
    int i, j, n = 4;
    for(i = 1; i <= n; i++){
        for(j = i; j < n; j++){
            printf(" ");
        }
        for(j = 0; j < i; j++){
            printf("%c ", 'A' + j);
        }
        for(j = i-2; j >= 0; j--){
            printf("%c ", 'A' + j);
        }
        printf("\n");
    }
    return 0;
}