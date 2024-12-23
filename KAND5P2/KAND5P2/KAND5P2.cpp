#include <iostream>
#include <fstream>
using namespace std;
int main()
{
    ofstream out("rez.txt");
    float x[4] = {}, y[4] = {}, z[4] = {};
    float ctrl[4] = {};
    for (int i = 1; i < 997; i++)
    {
        x[0] = i;
        x[1] = i;
        x[2] = i;
        x[3] = i;
        for (int j = i + 1; j < 998; j += 4)
        {
            y[0] = j;
            y[1] = j + 1;
            y[2] = j + 2;
            y[3] = j + 3;
            __asm
            {
                movups xmm0, x
                movups xmm1, y
                mulps xmm0, xmm0
                mulps xmm1, xmm1
                addps xmm0, xmm1
                sqrtps xmm2, xmm0
                movups z, xmm2
                roundps xmm2, xmm2, 1
                mulps xmm2, xmm2
                subps xmm2, xmm0
                movups ctrl, xmm2
            }
            for (int g = 0; g < 4; g++)
            {
                if (ctrl[g] == 0)
                {
                    out << x[g] << " " << y[g] << " " << z[g] << endl;
                }
            }
        }
    }
}