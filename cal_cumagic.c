#include "cal_cumagic.h"


int cal_cumagic(int n,int p)
{
int i,j,k;
if (n<=2 || n>MAX || n%2==0) return -1;
cureset(n);
j=n/2;i=j-1;
k=1;
cA.cu[i][j].num=k;
i--;j++;k++;
while (k<=p){
	if (i<0) i=n-1;
	if (j<0) j=n-1;
	if (j>=n) j=0;
	if (cA.cu[i][j].num==0){
		cA.cu[i][j].num=k;
		i--;j++;k++;
	}
	else{
		i--;j--;
	}
} 
cal_suma(n);
}

int cal_emplenar_cB(int n)
{
int i,j,k=1;
for (i=0;i<n;i++)
	for(j=0;j<n;j++)
		cB.cu[i][j].num=k++;
}

int cureset(int n)
{
int i,j;
for(i=0;i<n;i++)
	for(j=0;j<n;j++) cA.cu[i][j].num=0;
}

int SumaX(int n)
{
int i,j;
	for(i=0;i<n;i++){
		cA.sumX[i].num=0;
		for(j=0;j<n;j++)
			cA.sumX[i].num+=cA.cu[i][j].num;
	}
}

int SumaY(int n)
{
int i,j;
	for(j=0;j<n;j++){
		cA.sumY[j].num=0;
		for(i=0;i<n;i++)
			cA.sumY[j].num+=cA.cu[i][j].num;
	}
}

int SumaDiaA(int n)
{
int i;
cA.DiaA.num=0;
for(i=0;i<n;i++) cA.DiaA.num+=cA.cu[i][i].num;
}

int SumaDiaB(int n)
{
int i;
cA.DiaB.num=0;
for(i=0;i<n;i++) cA.DiaB.num+=cA.cu[i][n-i-1].num;
}

int cal_suma(int n)
{
SumaX(n);
SumaY(n);
SumaDiaA(n);
SumaDiaB(n);
}

