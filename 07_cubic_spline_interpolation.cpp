#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;
//solves tridiagonal matrix
int tridiag(double a[], double b[], double c[], double r[], int n, double* x){
  double* beta = new double[n];
  double* rho = new double[n];

  beta[0]=b[0];
  rho[0]=r[0];
  for (int i=1; i<n; i++){
    double ratio = a[i-1]/beta[i-1];
    beta[i]=b[i]-ratio*c[i-1];
    rho[i]=r[i]-ratio*rho[i-1];
  }
  
  x[n-1]=rho[n-1]/beta[n-1];

  for (int i=n-2; i>=0; i--){
    x[i]=(rho[i] - c[i]*x[i+1])/beta[i];
  }

  delete[] beta;
  delete[] rho;

  return 0;
}
//creates matrix problem from n points of x and y
int cspline( double x[], double y[], int n, double step, double* px, double* x1){
  if (n<2){
    return -1;
  }
  
  double h = x[1]-x[0];
  
  double *a = new double[n-1];
  double *b = new double[n];
  double *r = new double[n];
  
  double *pp = new double[n];
  
  for (int i=1; i<(n-1); i++){
    a[i-1] = h;
    b[i] = 4*h;
    r[i] = 6*(y[i+1] - 2*y[i] + y[i-1])/h;
  }
  a[0]=0;
  b[0]=1;
  r[0]=0;
  
  a[n-2]=0;
  b[n-1]=1;
  r[n-1]=0;

  tridiag(a,b,a,r,n,pp);

  int points= round((x[n-1] - x[0]) / step) + 1;
  for (int i=0; i<points; i++){
    double x_target = x[0] + i * step;
  
    int j = 0;
    for (int k = 0; k < n - 1; k++) {
      if (x_target >= x[k] && x_target <= x[k+1]) {
        j = k;
        break;
      }
    }
    if (j >= n - 1) { j = n - 2; }
    double dx = x_target - x[j];  

    double term1 = y[j];
    double term2 = ((y[j+1] - y[j])/h - (h * pp[j+1])/6.0 - (h * pp[j])/3.0) * dx;
    double term3 = (pp[j] / 2.0) * (dx * dx);
    double term4 = ((pp[j+1] - pp[j]) / (6.0 * h)) * (dx * dx * dx);

    x1[i]=x_target;
    px[i]= term1 + term2 + term3 + term4;
  }

  delete[] a;
  delete[] b;
  delete[] r;
  delete[] pp;
  return 0;
}



double func(double x){
  return 1/(1+x*x);
}

int main(){

  const int n = 11;
  double x[n],y[n];
  for (int i=0; i<n; i++){
    x[i]= i-5;
    y[i]= func(i-5);
  }
  
  const int j= round((x[n-1] - x[0]) / 0.1) + 1; 
  double* x1 = new double[j];
  double* px = new double[j];

  cspline(x,y,n,0.1,px,x1);

  ofstream Data("07_plot.csv"); 
  Data<<"x,px";
  for (int i=0; i<j; i++){
    Data<<"\n"<<x1[i]<<","<<px[i];
  }


  Data.close():
  delete[] x1;
  delete[] px;
  return 0;
}
