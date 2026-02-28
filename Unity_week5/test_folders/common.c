#include "header.h"

int even(int n){
if(n%2==0){
    return 1;
}
return 0;
}
float arr_average(int arr[],int s){
    float sum=0;
    if(s==0) return 0;
    else{
        for(int i=0;i<s;i++)
        {
            sum+=arr[i];
        }
    }
    return (float)sum/s;
}
int num_swap(int *a,int *b)
{
  int temp=*a;
    *a=*b;
    *b=temp;
}

void arr_swap(int arr[], int s) {
    int *st = arr;
    int *ed = arr + s - 1;

    while (st < ed) {
        int temp = *st;
        *st = *ed;
        *ed = temp;

        st++;
        ed--;
    }
}

