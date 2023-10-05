#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    cout << "POW: " << "Hello There!" << endl;
    double a1,a2,b1,b2;
        for (int x = -100; x < 100; x++)
    {
        for (int y = -100; y < 100; y++)
        {
            a1 = powl(x,x+y);
            a2 = powl(y,24);
            b1 = powl(y,x+y);
            b2 = powl(x,6);

            if (a1 == a2) if (b1 == b2) {
                cout << "TADA: x=" << x << " y=" << y << endl;
            }
            // disabled "0==1" to show only good results
            if (1==1 && x%10==0 && y%10==0) {
                cout << " x=" << x << " y=" << y << "\t\t";
                cout << a1 << " = " << a2 << " \t" << b1 << " = " << b2 << endl;
            }
        }
    }
    return 0;
}
