#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double bisec(double (*f)(double), double left, double right, double tol, int &iteration){
  
  double middle = (right + left)/2;
  do{
    iteration++;
    if (f(right)*f(middle) > 0.0){
      right = middle;
    }else{
      left = middle;
    }
    middle = (right + left)/2;

  }while(abs((right-left)/middle)>=tol);

  return middle;
}
//function
double func(double x){
  return cos(x)-x;
}

int main(){

  int iter=0;
  double val  = bisec(func, 0, 1, 1e-8, iter);
  cout<<setprecision(8);
  cout<<"Iterations: "<<iter<<"\nRoot: "<<val<<"\n";
  
  return 0;
}
