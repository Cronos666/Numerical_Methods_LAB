#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double false_pos(double (*f)(double), double left, double right, double tol, int &iteration){
  iteration = 0;

  double xn = left;
  double guess;

  do{
    guess = xn;
    xn = (left*f(right) - right*f(left))/(f(right) - f(left));
    iteration++;
  
    if (f(left)*f(xn) > 0.0){left=xn;}else{right=xn;}

  }while(abs((xn - guess) / xn) >= tol);
  
  return xn;
}

double secant(double (*f)(double), double x0, double x1, double tol, int &iteration) {
  iteration =  0;
  

  do{
    double xn = (x0*f(x1) - x1*f(x0))/(f(x1)-f(x0));
    iteration++;

    x0=x1;
    x1=xn;
  }while(abs((x1-x0)/x1) >= tol);

  return x1;
}

//func
double func(double x){
  return cos(x) - x;
}


int main(){
  int iter = 0;
  cout<<setprecision(8);

  double val_fp = false_pos(func, 0.0, 1.0, 1e-8, iter);
  cout << "Iterations: " << iter << "\nRoot: " << val_fp << "\n\n";
  
  double val_sec = secant(func, 0.0, 1.0, 1e-8, iter);
  cout << "Iterations: " << iter << "\nRoot: " << val_sec << "\n";

  return 0;
}
