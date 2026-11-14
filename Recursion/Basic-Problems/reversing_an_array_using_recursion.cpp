#include<iostream>
using namespace std;

void reverse(int arr[],int start,int end){
	if(start>=end){
		return;
	}
	swap(arr[start],arr[end]);
	return reverse(arr,start+1,end-1);
	
}
int main(){
	int arr[5];
	int n;
	cout<<"enter the number of elements in the array";
	cin>>n;
	cout<<"enter the elements in the array:"<<endl;
	for(int i = 0;i<n;i++){
		cin>>arr[i];
	}
	
	reverse(arr,0,n-1);
	cout<<"the reversed array is;"<<endl;
	for(int i =0;i<n;i++){
		cout<<arr[i];
	}
	
}
