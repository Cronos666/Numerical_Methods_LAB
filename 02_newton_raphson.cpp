#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double deriv(double (*f)(double), double x, double h){
  return (f(x+h)-f(x-h))/(2*h);
}


double newton(double (*f)(double), double guess, double tol, int &iteration){
  
  double xn = guess;
  do{
    iteration++;
    guess=xn;
    xn = guess - (f(guess)/deriv(f,guess,1e-8));

  }while(abs((xn-guess)/xn)>=tol);

  return xn;
}

//function
double func(double x){
  return cos(x)-x;
}

int main(){

  int iter=0;
  double x0[4]={0.1, 0.6, 0.8, 0.9};

  cout<<setprecision(8);
  for (int i=0; i<(sizeof(x0)/sizeof(x0[0])); i++){

    double val  = newton(func, x0[i], 1e-8, iter);
    cout<<"Initial guess: "<<x0[i]<<"\nIterations: "<<iter<<"\nRoot: "<<val<<"\n---------\n";
  } 
  return 0;
}
