#include<iostream>
#include<string>
using namespace std;
int main()
{
	int n;
	while(cin>>n)
	{
		string *ptr=new string [n];
		string waste;
		getline(cin,waste);
		for(int i=0;i<n;i++) getline(cin,ptr[i]);
		for(int i=0;i<n;i++)
		{
			int num=0;
			for(int j=0;j<ptr[i].length();)
			{
				if(ptr[i][j]<0&&ptr[i][j+1]<0)   //ÿ���������ֽ� ÿ���ֽ�ʮ������С���㣨������ 
				{
					num++;
					j=j+2;
				}
				else j++;
			}
			cout<<num<<endl;
	    }
	}
}
