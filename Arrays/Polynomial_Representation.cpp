#include<iostream>
using namespace std;

int main(){
	int poly[10],degree;
	
	cout<<"enter the degreee";
	
	cin>>degree;
	cout<<"enter the coefficient";
	for(int i =0;i<=degree;i++){
		cin>>poly[i];
	}
	cout<<"polynomial";
	
	for(int i = degree;i>=0;i--){
		if(poly[i]!=0){
			cout<<poly[i];
			if(i>0){
				cout<<"x";
			}
			if(i>1){
				cout<<"^"<<i;
			}
			if(i>0){
				cout<<"+";
			}
		}
	
	}
	return 0;
	
}
