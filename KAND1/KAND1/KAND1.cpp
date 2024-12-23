#include <iostream>
#include <iomanip>
#include <cmath>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <chrono>
#include <thread>
#include <atomic>
#include <typeinfo>
#include <conio.h>
using namespace std;
atomic<bool> Quit(false);
void ForceQ();
bool IsBusTrue(set<string> bus, string nbusena);
struct tiuring
{
    string busena, nbusena;
    char pirs, pirs2, ants, ants2, kryp, kryp2;
};
tiuring temp;
vector<tiuring>t;
int main(int argc, char* argv[])
{
    set<string> bus;
    string seka, seka2, b, strel, strel2;
    int a, c, p, p2, f;
    bool IsLoopTrue = true;
    bool IsPirsTrue = false;
    string file;
    cout << "To Force Stop the Program Press q"<<endl;
    cout << "File name: ";
    cin >> file;
    for (int i = 1; i < 16; i++)
    {
        if (argv[i] == file)
        {
            f = i;
            break;
        }
    }
    ifstream F(argv[f]);
    thread inputThread(ForceQ);
    F >> a;
    if (a == 1)
    {
        F >> seka;
        c = seka.length();
        strel.resize(c);
        fill(strel.begin(), strel.end(), ' ');
        F >> p;
        p--;
        string line;
        while (getline(F, line))
        {
            if (!line.empty())
            {
                string bus1, nbus;
                string pr, ar, kp;
                stringstream iString(line);
                getline(iString, bus1, ',');
                getline(iString, pr, ',');
                getline(iString, ar, ',');
                getline(iString, kp, ',');
                getline(iString, nbus, ',');
                temp.busena = bus1;
                temp.pirs = pr[0];
                temp.ants = ar[0];
                temp.kryp = kp[0];
                temp.nbusena = nbus;
                t.push_back(temp);
                bus.insert(temp.busena);
            }
        }
        b = *bus.begin();
        while (IsLoopTrue == true)
        {
            system("CLS");
            strel[p] = '^';
            cout << seka << endl;
            cout << strel << endl;
            strel[p] = ' ';
            for (auto i : t)
            {
                if (b == i.busena)
                {
                    if (seka[p] == i.pirs)
                    {
                        IsPirsTrue = true;
                        seka[p] = i.ants;
                        if (i.kryp == 'L')
                        {
                            p--;
                        }
                        else if (i.kryp == 'R')
                        {
                            p++;
                        }
                        b = i.nbusena;
                        if (IsBusTrue(bus, i.nbusena) == false)
                        {
                            IsLoopTrue = false;
                            cout << "Halted. State " << i.nbusena;
                        }
                        break;
                    }
                }
            }
            if (IsPirsTrue == false)
            {
                IsLoopTrue = false;
                cout << "Halted. No rule for state: " << b << " and symbol: " << seka[p];
            }
            if (IsLoopTrue == false)
            {
                inputThread.detach();
            }
            if (Quit == true)
            {
                cout << "Forced Stop.";
                break;
            }
            IsPirsTrue = false;
            this_thread::sleep_for(chrono::milliseconds(25));
        }
    }
    else if (a == 2)
    {
        F >> seka >> seka2;
        string pos, ps, ps2;
        getline(F, pos);
        getline(F, pos);
        getline(F, pos);
        stringstream poss(pos);
        getline(poss, ps, ',');
        getline(poss, ps2, ',');
        p = stoi(ps);
        p2 = stoi(ps2);
        p--;
        p2--;
        cout << p << p2;
        c = seka.length();
        strel.resize(c);
        fill(strel.begin(), strel.end(), ' ');
        strel2.resize(c);
        fill(strel2.begin(), strel2.end(), ' ');
        string line;
        while (getline(F, line))
        {
            if (!line.empty())
            {
                string bus1, nbus;
                string pr, pr2, ar, ar2, kp, kp2;
                stringstream iString(line);
                getline(iString, bus1, ',');
                getline(iString, pr, ',');
                getline(iString, pr2, ',');
                getline(iString, ar, ',');
                getline(iString, ar2, ',');
                getline(iString, kp, ',');
                getline(iString, kp2, ',');
                getline(iString, nbus, ',');
                temp.busena = bus1;
                temp.pirs = pr[0];
                temp.pirs2 = pr2[0];
                temp.ants = ar[0];
                temp.ants2 = ar2[0];
                temp.kryp = kp[0];
                temp.kryp2 = kp2[0];
                temp.nbusena = nbus;
                t.push_back(temp);
                bus.insert(temp.busena);
            }
        }
        b = *bus.begin();
        while (IsLoopTrue == true)
        {
            system("CLS");
            strel[p] = '^';
            cout << seka << endl;
            cout << strel << endl;
            strel[p] = ' ';
            strel2[p2] = '^';
            cout << seka2 << endl;
            cout << strel2 << endl;
            strel2[p2] = ' ';
            for (auto i : t)
            {
                if (b == i.busena)
                {
                    if (seka[p] == i.pirs && seka2[p2] == i.pirs2)
                    {
                        IsPirsTrue = true;
                        seka[p] = i.ants;
                        seka2[p2] = i.ants2;
                        if (i.kryp == 'L')
                        {
                            p--;
                            if (p < 0)
                            {
                                IsLoopTrue = false;
                                cout << "Halted. Reached tape border.";
                            }
                        }
                        else if (i.kryp == 'R')
                        {
                            p++;
                            if (p > seka.length() - 1)
                            {
                                IsLoopTrue = false;
                                cout << "Halted. Reached 1st tape border.";
                            }
                        }
                        if (i.kryp2 == 'L')
                        {
                            p2--;
                            if (p2 < 0)
                            {
                                IsLoopTrue = false;
                                cout << "Halted.Reached 2nd tape border.";
                            }
                        }
                        else if (i.kryp2 == 'R')
                        {
                            p2++;
                            if (p2 > seka2.length() - 1)
                            {
                                IsLoopTrue = false;
                                cout << "Halted.Reached 2nd tape border.";
                            }
                        }
                        b = i.nbusena;
                        if (IsBusTrue(bus, i.nbusena) == false)
                        {
                            IsLoopTrue = false;
                            cout << "Halted. State: " << i.nbusena;
                        }
                        break;
                    }
                    else if (seka[p] != i.pirs || seka2[p2] != i.pirs2)
                    {
                        IsPirsTrue = false;
                    }
                }
            }
            if (IsPirsTrue == false)
            {
                IsLoopTrue = false;
                cout << "Halted. No rule for state: " << b << " and symbols: " << seka[p] << " and " << seka2[p2];
            }
            if (IsLoopTrue == false)
            {
                inputThread.detach();
            }
            if (Quit == true)
            {
                cout << "Forced Stop.";
                break;
            }
            this_thread::sleep_for(chrono::milliseconds(25));
        }
    }
    if (inputThread.joinable())
    {
        inputThread.join();
    }
}
void ForceQ()
{
    char q;
    while (Quit == false)
    {
        q = _getch();
        if (q == 'q')
        {
            Quit = true;
        }
    }
}
bool IsBusTrue(set<string> bus, string nbusena)
{
    bool s = false;
    for (auto i : bus)
    {
        if (nbusena == i)
        {
            s = true;
            break;
        }
    }
    return s;
}