#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main()
{
    double m, n, k, res = 0;
    fstream F("INPUT.TXT");
    ofstream O("OUTPUT.TXT");
    F >> n >> m >> k;
    if (n <= 0 || m <= 1 || k <= 2)
    {
        O << 0;
    }
    else
    {
        while (m >= 2 && n > 0)
        {
            n -= (k - 2);
            m -= 2;
            ++res;
        }
        if (n < 0)
            m += n;
        res += ceil(m / k);
        if (n > 0)
        {
            O << 0;
        }
        else
        {
            O << res;
        }
    }
}