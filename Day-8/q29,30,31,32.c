//29.print half pyramid pattern//
#include<stdio.h>
int main(){
  int n=5,i,j;
  for(i=1;i<=n;i++){
    for(j=1;j<=i;j++){
      printf("* ");
    }
    printf("\n");
  }
  return 0;
}

//30.print number trinagle//
#include<stdio.h>
int main(){
  int n=5,i,j;
  for(i=1;i<=n;i++){
    for(j=1;j<=i;j++){
      printf("%d",j);
    }
    printf("\n");
  }
  return 0;
}

//31.print character triangle//
#include<stdio.h>
int main(){
    int i, j, n = 5;
    for(i = 0; i < n; i++){
        for(j = 0; j <= i; j++){
            printf("%c ", 'A' + j);
        }
        printf("\n");
    }
    return 0;
}


//32.print repeated-number trinagle//
#include<stdio.h>
int main(){
  int n=5,i,j;
  for(i=0;i<n;i++){
    for(j=0;j<i+1;j++){
      printf("%d",i+1);
    }
    printf("\n");
  }
  return 0;
}