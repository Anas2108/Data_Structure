
#include <iostream>
#include <cassert>
using namespace std;



class Vector
{
private:
   int*arr=nullptr;
   int size =0;
   int capacity;

public:
 
Vector(int size) :size(size)
{
if (size<0)
size=1;
capacity=size+10;
arr =new int [capacity];
}

~Vector() {
		delete[] arr;
		arr = nullptr;
	}

int get (int index){

assert(0<= index && index<=capacity); //if this condition true the program continue if not it terminate

    return arr[index];

 }

void set (int index, int value){

assert(0<= index && index<=capacity);

arr[index]=value;
}

///////////////// Some operations on the array////////////////

void print (){

for(int i=0;i<size;i++){

    cout<<arr[i]<<"\n";
}

}

int find (int value){

    for(int i=0;i<size;i++){

        if(arr[i]==value)
        return i;

      
    
    }
  return -1;

}

int get_back (){

    return arr[size-1];
}

int get_front (){

    return arr[0];
}

void expand_capacity(){

    capacity *=2;
int *arr2=new int [capacity];
for(int i=0;i<size;i++){

   arr2[i]=arr[i];

   }

   swap(arr,arr2);
   delete []arr2;
}


void push_back(int value){

if(size==capacity){
  
expand_capacity();

}
arr[size++]=value;

}

void insert (int index,int value){

if (size==capacity)
expand_capacity();

for(int i=size-1;i>=index;i--){

arr[i+1]=arr[i];

}

arr[index]=value;
size++;

}

void right_rotate(int times){



int last_element;
for(int counter=0;counter<times;counter++){
     last_element=arr[size-1];
for(int i=size-2;i>=0;i--){

arr[i+1]=arr[i];

  }

arr[0]=last_element;
}



}

void right_rotate(){

int last_element=arr[size-1];

for(int i=size-2;i>=0;i--){

arr[i+1]=arr[i];

}

arr[0]=last_element;



}


void left_rotate(){

int first_element=arr[0];



for (int i = 1; i < size; i++)
{
    arr[i-1]=arr[i];
}

arr[size-1]=first_element;

}


int pop(int index){

assert(index>=0&&index<size);
int deleted_item=arr[index];
int *arr2=new int[capacity];
int arr2_counter=0;
for (int i = 0; i < index; i++)
{
    arr2[arr2_counter]=arr[i];
    arr2_counter++;
}

for (int i = index+1; i < size; i++)
{
    arr2[arr2_counter]=arr[i];
    arr2_counter++;
}
swap(arr,arr2);
delete[]arr2;

size--; //because you delet an item so the size =size-1

return deleted_item;

}


int find_transposition(int value){

for (int i = 0; i < size; i++)
{
    if (arr[i]==value)
    {
        if(i==0)
        return 0;
        
        swap(arr[i],arr[i-1]);
        return i-1;
    }
    

}
return -1;

}


};


int main(){

/*Test the Vector Class*/

}
