#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double deriv(double (*f)(double), double x, double h){
  return (f(x+h)-f(x-h))/(2*h);
}


double hybrid(double (*f)(double), double left, double right, double tol, int &newton_iter, int &bisec_iter){
  newton_iter=0;

  double xn = (left+right)/2;
  bisec_iter=1;
  
  double guess;
  
  do{
    guess=xn;
    double temp = guess - (f(guess)/deriv(f,guess,1e-8));

    if (temp>left && temp<right){
      xn =temp;
      newton_iter++;

      if (f(right)*f(xn)>0.0){right=xn;}else{left=xn;};

    }else{
      if (f(right)*f(xn)>0.0){right=xn;}else{left=xn;};

      xn=(left+right)/2;
      bisec_iter++;
    }


  }while(abs((xn-guess)/xn)>=tol && abs((right-left)/xn)>=tol);

  return xn;
}

//function
double func(double x){
  return (6435*pow(x,8) - 12012*pow(x,6) + 6930*pow(x,4) - 1260*x*x + 35)/128;
}
double func2(double x){
  return x*x - 2*x -2;
}

int main(){

  int itern=0;
  int iterb=0;

  cout<<setprecision(8);
   
  cout<<"\nP(x)\n";

  double val  = hybrid(func, 0.4, 0.7, 1e-8, itern, iterb);
  cout<<"\nNewton iterations: "<<itern<<"\nBisection iterations: "<<iterb<<"\nRoot: "<<val<<"\n---------\n";

  cout<<"\nx^2 - 2x -2\n";
  val  = hybrid(func2, 0, 3, 1e-8, itern, iterb);
  cout<<"\nNewton iterations: "<<itern<<"\nBisection iterations: "<<iterb<<"\nRoot: "<<val<<"\n---------\n";
  
  return 0;
}
