#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;
double lagrange(double x[], double y[], double x1, int n){
  double result = 0;
  for (int i = 0; i < n; i++){
    double term = y[i];
    for (int j = 0; j < n; j++){
      if (j != i) {
        term *= (x1 - x[j]) / (x[i] - x[j]);
      }
    }
    result += term;
  }
  return result;
}

double deriv(double (*f)(double), double x, double h){
  return (f(x+h)-f(x-h))/(2*h);
}
double func(double x){
  return exp(x);
}


double hermite(double x[], double y[], double x_eval, int n){
  double result = 0.0;
  
  for (int i = 0; i < n; i++){
    double L_i = 1.0;
    double sum_term = 0.0;
    
    for (int j = 0; j < n; j++){
      if (i != j){
        L_i *= (x_eval - x[j]) / (x[i] - x[j]);
        sum_term += 1.0 / (x[i] - x[j]);
      }
    }
    
    double h_i = (1.0 - 2.0 * sum_term * (x_eval - x[i])) * L_i * L_i;
    double h_hat_i = (x_eval - x[i]) * L_i * L_i;
   
    result += y[i] * h_i + deriv(func,x[i],1e-8) * h_hat_i;
  }
  
  return result;
}

int main(){
  
  double x[4] = {-1.0,0.5,1.5,2.0};
  double y[4];
  for (int i=0; i<sizeof(x)/sizeof(x[0]); i++){
    y[i] = exp(x[i]);
  }

  ofstream Datal("05_lagrange.csv");
  ofstream Datah("05_hermite.csv");
  Datal<<"x,y";
  Datah<<"x,y";
  for (int i=-50; i<=50; i++){
      Datal<<"\n"<<i/10.0<<','<<lagrange(x,y,i/10.0,sizeof(x)/sizeof(x[0]));
      Datah<<"\n"<<i/10.0<<','<<hermite(x,y,i/10.0,sizeof(x)/sizeof(x[0]));
  }


  Datal.close();
  Datah.close();
  return 0;
}
