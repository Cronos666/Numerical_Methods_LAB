#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double deriv(double (*f)(double), double x, double h){
  return (f(x+h)-f(x-h))/(2*h);
}


double newton(double (*f)(double), double guess, double tol, int &iteration){
  iteration=0;
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
double func2(double x){
  return (6435*pow(x,8) - 12012*pow(x,6) + 6930*pow(x,4) - 1260*x*x + 35)/128;
}
double func3(double x){
  return x*x*x - 13*13;
}

int main(){

  int iter=0;
  double x0[5]={0.1,0.4, 0.6, 0.8, 0.9};

  cout<<setprecision(8);
  
  cout<<"\ncos(x) - x\n";
  double val  = newton(func, 0, 1e-8, iter);
  cout<<"Initial guess: "<<0<<"\nIterations: "<<iter<<"\nRoot: "<<val<<"\n---------\n";
  
  cout<<"\nP(x)\n";
  for (int i=0; i<(sizeof(x0)/sizeof(x0[0])); i++){

    double val  = newton(func2, x0[i], 1e-8, iter);
    cout<<"Initial guess: "<<x0[i]<<"\nIterations: "<<iter<<"\nRoot: "<<val<<"\n---------\n";
  }

  cout<<"\nx=13^2/3\n";
  val  = newton(func3, 13, 1e-8, iter);
  cout<<"Initial guess: "<<13<<"\nIterations: "<<iter<<"\nRoot: "<<val<<"\n---------\n";
  
    return 0;
}
