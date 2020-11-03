//Copyright Grisha777
#include <iostream>
#include "cmake-build-debug/TextTable.h"
#include <algorithm>
#include <cmath>
#include <string>
#include <random>

using namespace std;
double Right_limit = 1.5;
double Left_limit = -2.5;

double Function(double x)
{
    return -0.5*cos(0.5*x)+1;
}
double Function_Multi(double x)
{
    return Function(x)*sin(5*x);
}

void Print_table(TextTable& table, int N, double T, double x, double f)
{
    table.add(std::to_string(N));
    table.add(std::to_string(T));
    table.add(std::to_string(x));
    table.add(std::to_string(f));
    table.endOfRow();
}
void SA(double Fuction(double x))
{
    TextTable textTable('-', '|', '+');
    textTable.add("N");
    textTable.add("T");
    textTable.add("x");
    textTable.add("f(x)");
    textTable.endOfRow();
    const double T_max = 10000;
    const double T_min = 0.1;
    double T_i = T_max;
    int N = 1;
    random_device rd;
    std::mt19937 gen(rd());
    uniform_real_distribution<double> length(Left_limit, Right_limit);
    uniform_real_distribution<double> difference(0, 1);
    double x = length(gen);
    double f_x = Fuction(x);
    Print_table(textTable, N, T_i, x, f_x);
    while(T_i > T_min)
    {
        N++;
        double x_i = length(gen);
        double f_i = Fuction(x_i);
        double Delta = f_i - f_x;
        if (Delta<= 0)
        {
            x = x_i;
            f_x = f_i;
        } else
            {
            double P = exp(-Delta / T_i);
            double Difference = difference(gen);
            if (Difference < P)
            {
                x = x_i;
                f_x = f_i;
            }
        }
        T_i = T_i * 0.95;
        Print_table(textTable, N, T_i, x, f_x);
    }
    cout << textTable << endl;
}

int main()
{
    cout<<"Variant 9 "<<endl<<"Function: -0.5*cos(0.5*x)+1, interval: [-2.5,1.5] "<<endl<<endl;
    SA(Function);
    cout <<endl<< "Function_Multi: Function(x)*sin(5x), interval: [-2.5,1.5] "<<endl;
    SA(Function_Multi);
}
