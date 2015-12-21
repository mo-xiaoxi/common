#include<iostream>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<stdio.h>
using namespace std;
#define N 256

void function1();
void function2();
void function3();

int main()
{
	cout<<"µ⁄“ª÷÷∑Ω∑®£∫"<<endl;
	function1();
	cout<<"µ⁄∂˛÷÷∑Ω∑®£∫"<<endl;
	function2();
	cout<<"”¶”√£∫"<<endl;
	function3(); 
	return 0; 
} 

void function1()	// π”√∑Ω∑®“ªΩ¯––ÀÊª˙≈≈¡–£¨∂¡»°Œƒº˛ 
{
	int a[256],b[256];
	int i,j,n,temp;
	FILE *fp;
	cout<<" ‰»Î≈≈–Ú ˝◊È¥Û–°: "<<endl;
	cin>>n;		// ‰»Î≈≈–Ú ˝◊È¥Û–° 
	for(i=0;i<=n;i++)		//≥ı ºªØ¥˝≈≈–Ú ˝◊È 
		a[i]=i;		 
	 
	fp=fopen("text.txt","r");	//¥”Œƒº˛∂¡»°b[] 
	for(i=0;i<=n;i++)
		b[i]=fgetc(fp);
	fclose(fp);
	
	for(i=n;i>0;i--)		//º∆À„≤¢÷√ªª 
	{
		j=(b[i-1]+b[i])%i;
		temp=a[i];
		a[i]=a[j];
		a[j]=temp;
	}
	
	for(i=0;i<n;i++)
		cout<<a[i]<<' ';
	cout<<a[n]<<endl;
}

void function2()
{
	int i,j,m,n;
	int a[256],b[256];
	
	memset(a,0,sizeof(a));		//Ω´a[],b[]÷√Œ™0 
	memset(b,0,sizeof(b));
	cout<<" ‰»Îm”În"<<endl; 
	cin>>m>>n;
	
	srand((unsigned int) time(0));	//“‘œµÕ≥¡˜ ≈ ±º‰◊˜Œ™ÀÊª˙ ˝∑¢…˙∆˜÷÷◊” 
	for(i=0;i<m;i++)
	{
		j=rand()%(n+1);	//≤˙…˙ÀÊª˙ ˝≤¢∂‘n+1»°”‡ 
		if(!a[j])
		{
			a[j]=j;
		}
	} 
	for(i=0;i<=n;i++)
	{
		if(b[a[i]]==0)			//»Áπ˚’‚∏ˆ ˝µ⁄“ª¥Œ≥ˆœ÷‘Ú ‰≥ˆ
			cout<<a[i]<<' ';	
		b[a[i]]=1;				//’‚∏ˆ ˝“—æ≠≥ˆœ÷π˝ 
	}
	for(i=0;i<=n;i++)
	{
		if(b[i]==0)				//Ω´Œ¥≥ˆœ÷µƒ ˝∞¥À≥–Ú ‰≥ˆ 
			cout<<i<<' ';
	}
	cout<<endl;
}

void swap(int* a, int *b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	return;
}

void function3() {
	srand((unsigned)time(NULL));
	int n, t;
	int a[N];
	int b[N];
	for (int i = 0;i < N;++i) {
		b[i] = i ;
	}
	printf("«Î ‰»Î—›Ω≤µƒ»À ˝\n");
	scanf("%d", &n);
	for (int i = 0;i < n;++i) {
		t = rand() % (n - i);//÷ª¥” £œ¬µƒ ˝æ›÷–ÀÊª˙≥È»°£¨÷Æ∫Ûµƒ ˝æ›∂º≤ª”Ëøº¬«
		a[i] = b[t];//ÃÓ»Îƒø±Í ˝◊È
		swap(&b[t], &b[n - i - 1]);//Ω´—°≥ˆµƒ ˝æ›”Î◊Ó∫Û“ª∏ˆ ˝æ›Ω¯––Ωªªª
	}
	printf("—›Ω≤À≥–Ú»Áœ¬£∫\n");
	for (int i = 0;i < n;++i) {
		printf(">>\t%d\t<<\n", a[i]);
	}
	system("pause");
}
