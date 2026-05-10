#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

//forward
double forward(double (*f)(double), double x, double h){
    return (f(x+h)-f(x))/h;
}
double forward2(double (*f)(double), double x, double h){
    return (f(x) - 2*f(x+h) + f(x+2*h))/(h*h);
}

//central
double central(double (*f)(double), double x, double h){
    return (f(x+h)-f(x-h))/(2*h);
}
double central2(double (*f)(double), double x, double h){
    return (f(x+h) - 2*f(x) + f(x-h))/(h*h);
}

//funcs
double func(double x){
  return x*exp(x);
}

//df/dx = e^x + x*e^x
double exact(double x){
  return exp(x) + x*exp(x);
}
double exact2(double x){
  return 2*exp(x) + x*exp(x);
}



int main(){

  double x = 2;
  
  //files
  ofstream Data_f("08forward.csv");
  Data_f<<"ln(h),ln(err)";

  ofstream Data_f2("08forward2.csv");
  Data_f2<<"ln(h),ln(err)";

  ofstream Data_c("08central.csv");
  Data_c<<"ln(h),ln(err)";

  ofstream Data_c2("08central2.csv");
  Data_c2<<"ln(h),ln(err)";
  
  //calc
  cout<<setprecision(8);
  double e=exact(x);
  double e2=exact2(x);
    
  for (int i=0; i<10; i++){
    
    double h = (i+1)*0.05;
    //forward
    double f = forward(func,x,h);
    double f2 = forward2(func,x,h);
    
    double f_err = abs(f-e);
    double f2_err = abs(f2-e2);
    
    //central
    double c = central(func,x,h);
    double c2 = central2(func,x,h);
      
    double c_err = abs(c-e);
    double c2_err = abs(c2-e2);
   
    cout<<"------\nh: "<<h<<"\n------\n";
    cout<<"First\n\n";

    cout<<"Exact: "<<e<<"\n";
    cout<<"Central: "<<c<<" Error: "<<c_err<<"\n";
    cout<<"Forward: "<<f<<" Error: "<<f_err<<"\n";
    
    cout<<"Second\n\n";

    cout<<"Exact: "<<e2<<"\n";
    cout<<"Central: "<<c2<<" Error: "<<c2_err<<"\n";
    cout<<"Forward: "<<f2<<" Error: "<<f2_err<<"\n";
    
    Data_f<<'\n'<<log(h)<<','<<log(f_err);
    Data_f2<<'\n'<<log(h)<<','<<log(f2_err);
    Data_c<<'\n'<<log(h)<<','<<log(c_err);
    Data_c2<<'\n'<<log(h)<<','<<log(c2_err);

  } 
  
  Data_f.close();
  Data_f2.close();
  Data_c.close();
  Data_c2.close();

  return 0;
}
