//wap to linear search//
#include <stdio.h>
int main(){
    int arr[50],n,val,pos,i;
    printf("enter size of array\n");
    scanf("%d",&n);
    printf("\n enter value to be search\n");
    scanf("%d",&val);
    printf("\n enter array elements\n");
    for(i=0;i<n;i++)
    scanf("%d",&arr[i]);
   
    printf("\n array elements\n");
    for(i=0;i<n;i++)
    printf("%d\t",arr[i]);
    
    pos=-1;
    for(i=0;i<n;i++){
        if(arr[i]==val){
            pos=i;
            break;
        }
    }
    if(pos==-1)
    printf("\n element not found\n");
    else
    printf("\n %d in format at position %d",val,pos+1);
    return 0;
}