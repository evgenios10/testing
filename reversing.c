#include<stdio.h>
#include <stdlib.h> 
#include<time.h> 

int main(){

int size;
printf("please give the size of the table\n");
scanf("%d",&size);

srand(time(NULL));
int arr[size];
int temp=0;
int element;
int check=0;

for(int i=0; i<size; i++){
    check =0;
    
    

    while(check == 0){
    element=rand();
    if(element<100)
        check++;
    }

    arr[i]=element;
    printf("%d  ",arr[i]);

}
printf("\n");
printf("goodbye\n");

int count=0;

while(count!=size/2 ){
    temp=arr[count];
    arr[count]=arr[size-count-1];
    arr[size-count-1]=temp;

    count++;

}

for(int i=0; i<size; i++){

    printf("%d  ",arr[i]);
    
}

return 0;

}