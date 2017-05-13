#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

void print_matrix(vector<vector<int> >a, int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
}

vector<vector<int> > matrix_add(vector<vector<int> > a, vector<vector<int> > b, int n)
{
	vector<vector<int> > c (n, vector<int> (n));
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			c[i][j]=a[i][j]+b[i][j];
		}
	}
	return c;
}

vector<vector<int> > matrix_sub(vector<vector<int> > a, vector<vector<int> > b, int n)
{
	vector<vector<int> > c (n, vector<int> (n));
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			c[i][j]=a[i][j]-b[i][j];
		}
	}
	return c;
}

vector<vector<int> > brute_mul(vector<vector<int> > a, vector<vector<int> > b, int n)
{
	vector<vector<int> > c (n, vector<int> (n));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			c[i][j]=0;
			for(int k=0;k<n;k++)
			{
				c[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
	return c;
}

vector<vector<int> > dc_mul(vector<vector<int> > a, vector<vector<int> > b, int n)
{
	if(n<=2)
	{
		vector<vector<int> > c=brute_mul(a,b,n);
		return c;
	}

	vector<vector<int> > a11(n/2, vector<int>(n/2,0));
	vector<vector<int> > a12(n/2, vector<int>(n/2,0));
	vector<vector<int> > a21(n/2, vector<int>(n/2,0));
	vector<vector<int> > a22(n/2, vector<int>(n/2,0));
	vector<vector<int> > b11(n/2, vector<int>(n/2,0));
	vector<vector<int> > b12(n/2, vector<int>(n/2,0));
	vector<vector<int> > b21(n/2, vector<int>(n/2,0));
	vector<vector<int> > b22(n/2, vector<int>(n/2,0));

	for(int i=0;i<n/2;i++)
	{
		for (int j=0;j<n/2;j++)
		{
			a11[i][j]=a[i][j];
			a12[i][j]=a[i][j+n/2];
			a21[i][j]=a[i+n/2][j];
			a22[i][j]=a[i+n/2][j+n/2];
			b11[i][j]=b[i][j];
			b12[i][j]=b[i][j+n/2];
			b21[i][j]=b[i+n/2][j];
			b22[i][j]=b[i+n/2][j+n/2];
		}
	}
	vector<vector<int> > p=dc_mul(matrix_add(a11, a22, n/2), matrix_add(b11,b22, n/2), n/2);
	vector<vector<int> > q=dc_mul(matrix_add(a21, a22, n/2), b11, n/2);
	vector<vector<int> > r=dc_mul(a11, matrix_sub(b12, b22, n/2), n/2);
	vector<vector<int> > s=dc_mul(a22, matrix_sub(b21, b11, n/2), n/2);
	vector<vector<int> > t=dc_mul(matrix_add(a11, a12, n/2), b22, n/2);
	vector<vector<int> > u=dc_mul(matrix_sub(a21, a11, n/2), matrix_add(b11, b12, n/2), n/2);
	vector<vector<int> > v=dc_mul(matrix_sub(a12, a22, n/2), matrix_add(b21, b22, n/2), n/2);
    //cout<<p<<q<<r<<s<<t<<u<<v;
	vector<vector<int> > c11=matrix_add(matrix_add(p, v, n/2), matrix_sub(s, t, n/2), n/2);
	vector<vector<int> > c12=matrix_add(r, t, n/2);
	vector<vector<int> > c21=matrix_add(q, s, n/2);
	vector<vector<int> > c22=matrix_add(matrix_add(p, u, n/2), matrix_sub(r, q, n/2), n/2);
	vector<vector<int> > c(n, vector<int>(n,0));
	for(int i=0;i<n/2;i++)
	{
		for(int j=0;j<n/2;j++)
		{
			c[i][j]=c11[i][j];
			c[i][j+n/2]=c12[i][j];
			c[i+n/2][j]=c21[i][j];
			c[i+n/2][j+n/2]=c22[i][j];
		}
	}
	return c;
}

int main()
{

	int dim;
	cout<<"Enter dimension of the square matrix (positive natural number):\t";
	cin>>dim;
	if(dim<=0)
	{
		cout<<"\nInvalid Input!\n";
		main();
	}
	int N=pow(2, ceil(log2(dim)));
	vector<vector<int> >a(N, vector<int>(N,0));
	vector<vector<int> >b(N, vector<int>(N,0));
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{
			cout<<"Enter element A["<<i<<"]["<<j<<"]\t";
			cin>>a[i][j];
		}
	}
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{
			cout<<"Enter element B["<<i<<"]["<<j<<"]\t";
			cin>>b[i][j];
		}
	}
	vector<vector<int> >c1=brute_mul(a,b,dim);
	cout<<"Matrix A*B (Brute Force Method):"<<endl;
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{
			cout<<c1[i][j]<<" ";
		}

		cout<<endl;
	}

	vector<vector<int> >c2=dc_mul(a,b,N);
	cout<<"Matrix A*B (Divide and Conquer Method):"<<endl;
	for(int i=0;i<dim;i++)
	{
		for(int j=0;j<dim;j++)
		{
			cout<<c2[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
