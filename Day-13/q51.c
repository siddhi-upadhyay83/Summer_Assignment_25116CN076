//wap to find largest and smallest element//
#include<stdio.h>
int main (){
  int n;
  printf("enter the number of elements\n");
  scanf("%d", &n);
    int arr[n];
  printf("enter %d elemets\n",n);
  for(int i=0;i<n;i++){
    printf("element [%d]: ",i);
    scanf("%d",&arr[i]);
  }
  int largest=arr[0];
  int smallest=arr[0];
  for(int i=1;i<n;i++){
    if(arr[i]>largest)
    largest =arr[i];
    if(arr[i]<smallest)
    smallest =arr[i];
  }
  printf("\n Array elements: ");
  for(int i=0;i<n;i++)
  printf("%d ",arr[i]);
  printf("\nlargest element =%d",largest);
  printf("\nSmallest element = %d\n", smallest);
  return 0;
}