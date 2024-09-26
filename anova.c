#include <iostream>
#include <math.h>
#include <vector>

#include <math.h>
#include "cal.h"

double mean(double t[],int n){
	double sum=0;
	int i;
	for(i=0;i<n;i++)sum+=t[i];
	return sum/n;
}
int sd1var(double tx[],int n,STAT *result){
	int i;
	result->sumx=0;
	result->sumx2=0;
	for(i=0;i<n;i++){
		result->sumx+=tx[i];
		result->sumx2+=tx[i]*tx[i];
	}
	result->xbar=result->sumx/n;
	result->ssx=0;
    for(i=0;i<n;i++){
		result->ssx+=(tx[i]-result->xbar)*(tx[i]-result->xbar);
    }
    result->sigmax=sqrt(result->ssx/n);
    return 1;
}
int sd2var(double tx[],double ty[],int n,STAT *result){
	int i;
	result->sumx=0;
	result->sumy=0;
	result->sumx2=0;
	result->sumy2=0;
	result->sumxy=0;
	for(i=0;i<n;i++){
		result->sumx+=tx[i];
		result->sumy+=ty[i];
		result->sumx2+=tx[i]*tx[i];
		result->sumy2+=ty[i]*ty[i];
		result->sumxy+=tx[i]*ty[i];
	}
	result->xbar=result->sumx/n;
	result->ybar=result->sumy/n;
	result->ssx=0;
	result->ssy=0;
    for(i=0;i<n;i++){
		result->ssx+=(tx[i]-result->xbar)*(tx[i]-result->xbar);
		result->ssy+=(ty[i]-result->ybar)*(ty[i]-result->ybar);
    }
    result->sigmax=sqrt(result->ssx/n);
    result->sigmay=sqrt(result->ssy/n);
    return 1;
}

int example()
{
	STAT stat;
	int i,j,n[10],r;
	double *data[10];
	double tmp[10][4];
	double result[3][4];
	char *colname[]={"variance","SS","DoF","MSE","Fvalue"};
	char *rowname[]={"Factor A","Error","sum Total"};
	//Data input
	printf("r=");
	scanf("%d",&r);
	for(i=0;i<r;i++){
		printf("n[%d]=",i+1);
		scanf("%d",n+i);
		puts("Please input data:");
		data[i]=(double*)malloc(n[i]*sizeof(double));
		for(j=0;j<n[i];j++){
			scanf("%lf",data[i]+j);
		}
	}
	//Start calc
	tmp[r][0]=0;
	tmp[r][1]=0;
	tmp[r][2]=0;
	tmp[r][3]=0;
	result[1][0]=0;
	for(i=0;i<r;i++){
		sd1var(data[i],n[i],&stat);
		tmp[i][0]=n[i];
		tmp[i][1]=stat.sumx;
		tmp[i][2]=stat.xbar;
		tmp[i][3]=stat.sumx2;
		tmp[r][0]+=n[i];
		tmp[r][1]+=stat.sumx;
		tmp[r][3]+=stat.sumx2;
		result[0][0]+=tmp[i][0]*tmp[i][2]*tmp[i][2];
	}
	tmp[r][2]=tmp[r][0]/tmp[r][1];
	for(i=0;i<=r;i++){
		for(j=0;j<4;j++){
			printf("%10.4lf ",tmp[i][j]);
		}
		putchar('\n');
	}
	result[2][0]=tmp[r][3]-tmp[r][1]*tmp[r][1]/tmp[r][0];
	result[0][0]=result[0][0]-tmp[r][1]*tmp[r][1]/tmp[r][0];
	result[1][0]=result[2][0]-result[0][0];
	result[0][1]=r-1;
	result[1][1]=tmp[r][0]-r;
	result[2][1]=tmp[r][0]-1;
	result[0][2]=result[0][0]/result[0][1];
	result[1][2]=result[1][0]/result[1][1];
	result[0][3]=result[0][2]/result[1][2];
	puts("analysis of variance table：");
	for(j=0;j<5;j++){
		printf("%10s ",colname[j]);
	}
	putchar('\n');
	for(i=0;i<3;i++){
		printf("%10s ",rowname[i]);
		for(j=0;j<4;j++){
			if(i+j<4)printf("%10.4f ",result[i][j]);
		}
		putchar('\n');
	}
    return 0;
}





