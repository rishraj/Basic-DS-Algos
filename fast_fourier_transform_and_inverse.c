#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float ** fft(float **a , int n);
float ** ffti(float **a , int n);

int main()
{
	int t;
	scanf("%d", &t);
	int n;
	scanf("%d" , &n);
	float **a;
	a = malloc(n*sizeof(float*));
	for(int i=0 ; i<n ; i++)
		a[i] = malloc(2 * sizeof(float));
	for(int i=0 ; i<n ; i++)
		scanf("%f %f" , &a[i][0], &a[i][1]);
	if(t == 0)
	{
		float **y = fft(a , n);
		printf("%d ", n);
		for(int i=0 ; i<n ; i++)
		{
			if((y[i][0] >= -0.005 && y[i][0] <= 0.005) && (y[i][1] >= -0.005 && y[i][1] <= 0.005))
				printf("0 0 ");
			else if(y[i][0] >= -0.005 && y[i][0] <= 0.005)
				printf("0 %0.1f ", y[i][1]);
			else if(y[i][1] >= -0.005 && y[i][1] <= 0.005)
				printf("%0.1f 0 ", y[i][0]);
			else
				printf("%0.1f %0.1f ", y[i][0] , y[i][1]);

		}
		printf("\n");
	}
	else if(t == 1)
	{
		float **y = ffti(a , n);
		printf("%d ", n);
		for (int i = 0; i < n; ++i)
		{
			if((y[i][0] >= -0.005 && y[i][0] <= 0.005) && (y[i][1] >= -0.005 && y[i][1] <= 0.005))
				printf("0 0 ");
			else if(y[i][0] >= -0.005 && y[i][0] <= 0.005)
				printf("0 %0.1f ", y[i][1]/n);
			else if(y[i][1] >= -0.005 && y[i][1] <= 0.005)
				printf("%0.1f 0 ", y[i][0]/n);
			else
				printf("%0.1f %0.1f ", y[i][0]/n , y[i][1]/n);
		}
		printf("\n");	
	}
	return 0;
}

float ** fft(float **a, int n)
{
	if(n == 1)
		return a;
	float **a0;
	a0 = malloc(n/2*sizeof(float*));
	for(int i=0 ; i<n/2 ; i++)
		a0[i] = malloc(2 * sizeof(float));
	float **a1;
	a1 = malloc(n/2*sizeof(float*));
	for(int i=0 ; i<n ; i++)
		a1[i] = malloc(2 * sizeof(float));
	for(int i=0 ; i<n ; i++)
	{
		if(i%2 == 0)
		{
			a0[i/2][0] = a[i][0];
			a0[i/2][1] = a[i][1];
		}
		else
		{
			a1[(i-1)/2][0] = a[i][0];
			a1[(i-1)/2][1] = a[i][1];
		}
	}
	float **y0 = fft(a0 , n/2);
	float **y1 = fft(a1 , n/2);
	float **y;
	y = malloc(n * sizeof(float *));
	for(int i=0 ; i<n ; i++)
		y[i] = malloc(2 * sizeof(float));
	float w[1][2];
	w[0][0] = 1;
	w[0][1] = 0;
	float wn[1][2];
	wn[0][0] = cos((2*3.141592)/n);
	wn[0][1] = sin((2*3.141592)/n);
	for(int i=0 ; i<n/2 ; i++)
	{
		y[i][0] = y0[i][0] + ((w[0][0]*y1[i][0])-(w[0][1]*y1[i][1]));
		y[i][1] = y0[i][1] + ((w[0][0]*y1[i][1])+(w[0][1]*y1[i][0]));
		y[i+(n/2)][0] = y0[i][0] - ((w[0][0]*y1[i][0])-(w[0][1]*y1[i][1]));
		y[i+(n/2)][1] = y0[i][1] - ((w[0][0]*y1[i][1])+(w[0][1]*y1[i][0]));
		float q = w[0][0];
		float r = w[0][1];
		w[0][0] = (q*wn[0][0]) - (r*wn[0][1]);
		w[0][1] = (q*wn[0][1]) + (r*wn[0][0]);
	}
	return y;
}

float ** ffti(float **a , int n)
{
	if(n == 1)
		return a;
	float **a0;
	a0 = malloc(n/2*sizeof(float*));
	for(int i=0 ; i<n/2 ; i++)
		a0[i] = malloc(2 * sizeof(float));
	float **a1;
	a1 = malloc(n/2*sizeof(float*));
	for(int i=0 ; i<n ; i++)
		a1[i] = malloc(2 * sizeof(float));
	for(int i=0 ; i<n ; i++)
	{
		if(i%2 == 0)
		{
			a0[i/2][0] = a[i][0];
			a0[i/2][1] = a[i][1];
		}
		else
		{
			a1[(i-1)/2][0] = a[i][0];
			a1[(i-1)/2][1] = a[i][1];
		}
	}
	float **y0 = ffti(a0 , n/2);
	float **y1 = ffti(a1 , n/2);
	float **y;
	y = malloc(n * sizeof(float *));
	for(int i=0 ; i<n ; i++)
		y[i] = malloc(2 * sizeof(float));
	float w[1][2];
	w[0][0] = 1;
	w[0][1] = 0;
	float wn[1][2];
	wn[0][0] = cos((2*3.141592)/n);
	wn[0][1] = -sin((2*3.141592)/n);
	for(int i=0 ; i<n/2 ; i++)
	{
		y[i][0] = (y0[i][0] + ((w[0][0]*y1[i][0])-(w[0][1]*y1[i][1])));
		y[i][1] = (y0[i][1] + ((w[0][0]*y1[i][1])+(w[0][1]*y1[i][0])));
		y[i+(n/2)][0] = y0[i][0] - ((w[0][0]*y1[i][0])-(w[0][1]*y1[i][1]));
		y[i+(n/2)][1] = y0[i][1] - ((w[0][0]*y1[i][1])+(w[0][1]*y1[i][0]));
		float q = w[0][0];
		float r = w[0][1];
		w[0][0] = (q*wn[0][0]) - (r*wn[0][1]);
		w[0][1] = (q*wn[0][1]) + (r*wn[0][0]);
	}
	return y;
}










