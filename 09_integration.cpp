#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>

using namespace std;

//taking right f(x) of interval (overshooting for positive slope)
double riemann_right(double a, double b, double x[], double y[], int n){
  double sum=0;
  for (int i=1; i<n; i++){
    sum+= (x[i]-x[i-1])*y[i];
  }
  return sum;
}

//taking left f(x) of interval (undershooting for positive slope)
double riemann_left(double a, double b, double x[], double y[], int n){
  double sum=0;
  for (int i=1; i<n; i++){
    sum+= (x[i]-x[i-1])*y[i-1];
  }
  return sum;
}

//avg of left and right (exact to first derivative)
double trapezoid(double a, double b, double x[], double y[], int n){
  double sum=0;
  for (int i=1; i<n; i++){
    double dx=x[i]-x[i-1];
    sum+= dx*(y[i-1]+y[i])/2;
  }
  return sum;
}
//time measurment
int measure(double (*f)(double, double, double[], double[], int),
    double a, double b, double x[], double y[], int n){
  
  auto start = std::chrono::high_resolution_clock::now();
  double s=f(a,b,x,y,n);
  auto stop = std::chrono::high_resolution_clock::now();
  
  std::chrono::duration<double, std::milli> time_ms = stop - start;
  cout<<setprecision(12)<<fixed;
  cout<<"\n time: "<<time_ms.count()<<" |  value: "<<s<<'\n';

  return 0;
}

//const step simpson integration
//Simpson 1/3 (interavlas%2==0)  | dx/3 * ( f0 + 4 f1 + 2 f2 + 4 f3 +..+ 2 f(n-2) + 4 f(n-1) + fn)
double simpson13(double a, double b, double x[], double y[], int n){
  if ((n-1)%2!=0){
    return NAN;
  }
  double sum=y[0];
  for (int i=1; i<(n-1); i+=2){
    sum+=4*y[i];
  }
  for (int i=2; i<(n-1); i+=2){
    sum+=2*y[i];
  }
  sum += y[n-1];
  sum *= (x[1]-x[0])/3.0;
  return sum;
}

//Simpson 3/8 (interavlas%3==0)  | 3dx/8 * ( f0 + 3 f1 + 3 f2 + 2 f3 +..+ 3 f(n-2) + 3 f(n-1) + fn)
double simpson38(double a, double b, double x[], double y[], int n){
  if ((n-1)%3!=0){
    return NAN;
  }
  double sum=y[0];
  for (int i=1; i<(n-1); i++){
    if(i%3==0){ sum+=2*y[i];
    }else{ sum +=3*y[i]; }
  }
  sum += y[n-1];
  sum *= 3.0*(x[1]-x[0])/8.0;
  return sum;
}

//Boole 2/45 (interavlas%4==0)  | 2dx/45 * (7 f0 + 32 f1 + 12 f2 + 32 f3 + 7 f4 +..)
double boole245(double a, double b, double x[], double y[], int n){
  if ((n-1)%4!=0){
    return NAN;
  }
  double sum=0;
  for (int i=0; i<(n-1); i+=4){
    sum+= 7*y[i] + 32*y[i+1] + 12*y[i+2] + 32*y[i+3]+ 7*y[i+4];
  }
  sum *= 2.0*(x[1]-x[0])/45.0;
  return sum;
}






int main(int argc, char* argv[]){
  if (argc <2){ 
    cout<<"\nprovide number of points\n";
    return -1;
  }
  const int n = stoi(argv[1]);
  const double a = 0, b=0.5;
  double x[n],y[n];
  for (int i=0; i<n; i++){
    double xn=a+i*(b-a)/(n-1);
    x[i]=xn;
    y[i]=cos(xn);
  }
  
  cout<<"Right:";
  measure(riemann_right,a,b,x,y,n);
  cout<<"Left:";
  measure(riemann_left,a,b,x,y,n);
  cout<<"Trap:";
  measure(trapezoid,a,b,x,y,n);
  
  cout<<"\nconstant step fucntions\n";
  cout<<setprecision(12)<<fixed;
  cout<<"Simpson 1/3:";
  measure(simpson13,a,b,x,y,n);
  cout<<"Simpson 3/8:";
  measure(simpson38,a,b,x,y,n);
  cout<<"Boole 2/45:";
  measure(boole245,a,b,x,y,n);
  return 0;
}
