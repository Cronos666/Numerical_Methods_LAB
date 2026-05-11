#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

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



int main(){

  const int n=5;
  
  //A*x = r
  double A[n][n] = {
    { 2, -1,  0,  0,  0},
    {-1,  2, -1,  0,  0},
    { 0, -1,  2, -1,  0},
    { 0,  0, -1,  2, -1},
    { 0,  0,  0, -1,  2}
  };
  double x[n] = {0, 0, 0, 0, 0}; 
  double r[n] = {0, 1, 2, 3,4};
  

  //diagonal extracion
  double a[n-1], b[n],c[n-1];
  for (int i=0; i<(n-1); i++){
    a[i]=A[i+1][i];
    b[i]=A[i][i];
    c[i]=A[i][i+1];
  }
  b[n-1]=A[n-1][n-1];


  tridiag(a, b, c, r, n, x);

  cout<<fixed<<setprecision(8);
  for (int i=0; i<n; i++){
    cout<<"x_"<<i+1<<": "<<x[i]<<"\n";
  }

  cout<<"\nVerification\n";
  for (int i=0; i<n; i++){
    double calc_r = 0.0;

    for (int j=0; j<n; j++){
      calc_r += A[i][j]*x[j];
    }
    double error = abs(calc_r - r[i]);

    cout<<"Row "<<i+1<<"\n  calculated r: "<<calc_r<<"\n  expected r:   "<<r[i]<<"\n  error:        "<<error<<"\n";
  }

  return 0;
}
