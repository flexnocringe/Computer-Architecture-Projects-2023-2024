#include <iostream>
using namespace std;
bool NAND(bool x, bool y);
bool AND(bool x, bool y);
bool NOR(bool x, bool y);
bool OR(bool x, bool y);
bool XOR(bool x, bool y);
bool NOT(bool x);
void HAdder(bool x, bool y, bool sum[2]);
void FAdder(bool a, bool b, bool sum[2], bool& cOut);
void Shifter(bool a[8], bool shift);
void DEC24(bool x[2], bool y[4]);
void DEC38(bool x[3], bool y[8]);
void ALU1bit(bool a, bool b, bool salyga[2], bool& out, bool& carry);
void ALU8bit(bool a[8], bool b[8], bool salyga[3], bool& bEkv, bool output[8], bool& f, bool &cFlag, bool &shift);
void ExcIO(bool a[8]);
int main()
{
    bool A8[8] = { 0,0,0,0,1,1,0,1 }; // 8bit ALU A
    bool B8[8] = { 0,0,0,0,1,0,1,1 }; // 8bit ALU B
    bool salyga38[3] = { 1,0,0 }; // 8bit ALU salyga
    bool shift = 0; //shifto puses pasirinkimas
    bool bEkv=0, f=0, cFlag=0; // Carry flagas pranesa vartuotojui kai ivyko perpildymas po gautu rezultatu bus skaicius: 1
    bool output[8] = {};
    ALU8bit(A8, B8, salyga38, bEkv, output, f, cFlag, shift);
    if (f)
    {
        cout << bEkv;
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            cout << output[i];
        }
        if (cFlag)
        {
            cout << endl;
            cout << cFlag;
        }
    }
    return 0;
}
bool NAND(bool x, bool y)
{
    if ((!x && !y) || (x && !y) || (!x && y))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
bool AND(bool x, bool y)
{
    if (NAND(NAND(x, y), NAND(x, y)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
bool NOR(bool x, bool y)
{
    if (NAND(NAND(NAND(x, x), NAND(y, y)), NAND(NAND(x, x), NAND(y, y))))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
bool OR(bool x, bool y)
{
    if (NAND(NAND(x, x), NAND(y, y)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
bool XOR(bool x, bool y)
{
    if (NAND(NAND(x, NAND(x, y)), NAND(y, NAND(x, y))))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
bool NOT(bool x)
{
    if (NAND(x, x))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void HAdder(bool x, bool y, bool& sum, bool& carry)
{
    carry = AND(x, y);
    sum = XOR(x, y);
}
void FAdder(bool a, bool b, bool& sum, bool& cOut)
{
    bool cr1, cr2;
    HAdder(a, b, sum, cr1);
    bool sum1 = sum;
    HAdder(sum1, cOut, sum, cr2);
    cOut = OR(cr1, cr2);
}
void Shifter(bool a[8], bool shift)
{
    bool b[8];
    b[0] = AND(NOT(shift), a[1]);
    b[1] = OR(AND(a[0], shift), AND(a[2], NOT(shift)));
    b[2] = OR(AND(a[1], shift), AND(a[3], NOT(shift)));
    b[3] = OR(AND(a[2], shift), AND(a[4], NOT(shift)));
    b[4] = OR(AND(a[3], shift), AND(a[5], NOT(shift)));
    b[5] = OR(AND(a[4], shift), AND(a[6], NOT(shift)));
    b[6] = OR(AND(a[5], shift), AND(a[7], NOT(shift)));
    b[7] = AND(shift, a[6]);
    for (int i = 0; i < 8; i++)
    {
        a[i] = b[i];
    }
}
void DEC24(bool x[2], bool y[4])
{
    y[0] = AND(NOT(x[0]), NOT(x[1]));
    y[1] = AND(NOT(x[0]), x[1]);
    y[2] = AND(x[0], NOT(x[1]));
    y[3] = AND(x[0], x[1]);
}
void DEC38(bool x[3], bool y[8])
{
    y[0] = AND(AND(NOT(x[2]), NOT(x[1])), NOT(x[0]));
    y[1] = AND(AND(x[2], NOT(x[1])), NOT(x[0]));
    y[2] = AND(AND(NOT(x[2]), x[1]), NOT(x[0]));
    y[3] = AND(AND(x[2], x[1]), NOT(x[0]));
    y[4] = AND(AND(NOT(x[2]), NOT(x[1])), x[0]);
    y[5] = AND(AND(x[2], NOT(x[1])), x[0]);
    y[6] = AND(AND(NOT(x[2]), x[1]), x[0]);
    y[7] = AND(AND(x[2], x[1]), x[0]);
}
void ExcIO(bool a[8])
{
    try
    {
        if (a[0] || a[6] || a[7])
        {
            throw 0;
        }
    }
    catch (int numException)
    {
        cout << "Error. No Operation Assigned to Adress.";
    }
}
void ALU1bit(bool a, bool b, bool salyga[2], bool& out1, bool& carry1)
{
    bool dekod[4] = {};
    DEC24(salyga, dekod);
    if (dekod[0])
    {
        out1 = NOT(a);
        return;
    }
    else if (dekod[1])
    {
        out1 = NOT(b);
        return;
    }
    else if (dekod[2])
    {
        out1 = XOR(a, b);
        return;
    }
    else if (dekod[3])
    {
        FAdder(a, b, out1, carry1);
        return;
    }
}
void ALU8bit(bool a[8], bool b[8], bool salyga[3], bool& bEkv, bool output[8], bool& f, bool& cFlag, bool& shift)
{
    bool out1, carry1;
    bool ena, enb;
    bool dekod[8] = {};
    DEC38(salyga, dekod);
    ExcIO(dekod);
    if (dekod[1])
    {
        f = 0;
        ena = 0;
        enb = 1;
        for (int i = 0; i < 8; i++)
        {
            a[i] = AND(a[i], ena);
            b[i] = AND(b[i], enb);
        }

        bool salyga1[2] = { 0,1 };
        for (int i = 0; i < 8; i++)
        {
            ALU1bit(a[i], b[i], salyga1, out1, carry1);
            output[i] = out1;
        }
        for (int i = 7; i >=0; i--)
        {
            ALU1bit(a[i], output[i], salyga1, out1, carry1);
            output[i] = out1;
            if (output[i]==1)
            {
                break;
            }
        }
        return;
    }
    else if (dekod[2])
    {
        f = 1;
        ena = 1;
        enb = 1;
        for (int i = 0; i < 8; i++)
        {
            a[i] = AND(a[i], ena);
            b[i] = AND(b[i], enb);
        }
        bool xor1, xor2;
        bool salyga1[2] = { 1,0 };
        for (int i = 0; i < 8; i = i + 2)
        {
            ALU1bit(a[i], b[i], salyga1, out1, carry1);
            xor1 = out1;
            ALU1bit(a[i + 1], b[i + 1], salyga1, out1, carry1);
            xor2 = out1;
            bEkv = NOR(xor1, xor2);
        }
        return;
    }
    else if (dekod[3])
    {
        f = 0;
        ena = 1;
        enb = 1;
        for (int i = 0; i < 8; i++)
        {
            a[i] = AND(a[i], ena);
            b[i] = AND(b[i], enb);
        }
        bool salyga1[2] = { 1,1 };
        bool cOut=0;
        for (int i = 7; i >= 0; i--)
        {
            ALU1bit(a[i], b[i], salyga1, out1, cOut);
            output[i] = out1;
            if (i == 0 && cOut)
            {
                cFlag = 1;
            }
        }
    }
    else if (dekod[4])
    {
        f = 0;
        ena = 1;
        enb = 1;
        for (int i = 0; i < 8; i++)
        {
            a[i] = AND(a[i], ena);
            b[i] = AND(b[i], enb);
        }
        bool salyga1[2] = { 1,1 };
        bool cOut = 0;
        for (int i = 7; i>=0; i--)
        {
            if (b[7] == 1)
            {
                for (int j = 7; j >= 0; j--)
                {
                    ALU1bit(output[j], a[j], salyga1, out1, cOut);
                    output[j] = out1;
                    if (j == 0 && cOut)
                    {
                        cFlag = 1;
                    }

                }
                Shifter(b, 1);
                Shifter(a, 0);
            }
            else if (b[7] == 0)
            {
                Shifter(b, 1);
                Shifter(a, 0);
            }
        }
        return;
    }
    else if (dekod[5])
    {
        f = 0;
        ena = 1;
        enb = 0;
        for (int i = 0; i < 8; i++)
        {
            a[i] = AND(a[i], ena);
            b[i] = AND(b[i], enb);
        }
        Shifter(a, shift);
        for (int i = 0; i < 8; i++)
        {
            output[i] = a[i];
        }
        return;
    }
}