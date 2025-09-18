#include <iostream>
using namespace std;

double power(double x, int n)
{
    if (n == 2){
        return x * x;
    }
    if (n < 0){
        return 1 / power(x, -n);
    }
    if (n == 0){
        return 1;
    }
    if (n % 2 == 0){
        return power(x*x, n/2);
    }
    else{
        return x * power(x*x, (n-1)/2);
    }

}

int main()
{
    cout << power(2, -3) << endl;    
}