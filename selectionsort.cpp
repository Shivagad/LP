#include<iostream>
#include<bits/stdc++.h>
using namespace std;



void sortarray( vector<int>&arr,int n)
{
  for(int i=0;i<n;i++)
  {
   int minindex=i;
   for(int j=i+1;j<n;j++)
   {
    if(arr[j]<arr[minindex])
    {
        minindex=j;
    }
   }
   swap(arr[i],arr[minindex]);
  }
}

int main()
{
  
    int n;
    cout<<"enter the array size:";
    cin>>n;
    vector<int>v(n);
    cout<<"enter the array element:";
    for(int i=0;i<n;i++)
    {
       cin>>v[i];
    }
    cout<<endl;
    cout<<"array before sorted:";
    for(int i=0;i<n;i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
    sortarray(v,n);
    cout<<endl;
    cout<<"array after sorted:";
    for(int i=0;i<n;i++)
    {
        cout<<v[i]<<" ";
    }

}