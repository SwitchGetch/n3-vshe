#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <random>
using namespace std;
using namespace chrono;

string Time(high_resolution_clock::time_point start, high_resolution_clock::time_point end)
{
    string result = "";


    int h = duration_cast<hours>(end - start).count();
    int m = duration_cast<minutes>(end - start).count();
    int s = duration_cast<seconds>(end - start).count();
    int ms = duration_cast<milliseconds>(end - start).count();


    int min = m - h * 60;
    int sec = s - m * 60;
    int milsec = ms - s * 1000;

    result += to_string(h) + ":";

    if (to_string(min).size() == 2) result += to_string(min) + ":";
    else result += "0" + to_string(min) + ":";

    if (to_string(sec).size() == 2) result += to_string(sec) + ":";
    else result += "0" + to_string(sec) + ":";

    if (to_string(milsec).size() == 3) result += to_string(milsec);
    else if (to_string(milsec).size() == 2) result += "0" + to_string(milsec);
    else result += "00" + to_string(milsec);


    return result;
}

long CurrentD(vector<int>& a, vector<int>& index_combo, int k)
{
    long D = 0;

    for (int i = 0, j = k - 1; i < j; i++, j--)
    {
        D += a[index_combo[i]] - a[index_combo[j]];
    }

    return D;
}

long MaxD(vector<int>& a, int n, int k)
{
    vector<int> index_combo;
    long maxD, curD;
    int i;
    bool b = false;

    for (int i = 0; i < k; i++) index_combo.push_back(i);
    index_combo.push_back(n);
    index_combo.push_back(0);


    while (true)
    {
        curD = CurrentD(a, index_combo, k);

        if (b)
        {
            if (curD > maxD) maxD = curD;
        }
        else
        {
            maxD = curD;
            b = true;
        }

        for (i = 0; index_combo[i] + 1 == index_combo[i + 1]; i++) index_combo[i] = i;

        if (i < k) index_combo[i]++;
        else break;
    }

    return maxD;
}

int main()
{
    srand(time(NULL));

    int t;
    high_resolution_clock::time_point start, end;

    cout << "t = ";
    cin >> t;

    cout << endl;

    for (int i = 0; i < t; i++)
    {
        int n, k;
        vector<int> a;

        cout << "n = ";
        cin >> n;

        cout << "k = ";
        cin >> k;

        cout << "a = " << n << " random numbers" << endl;

        for (int i = 0; i < n; i++) a.push_back(rand());


        start = high_resolution_clock::now();

        cout << "D = " << MaxD(a, n, n - k) << endl;

        end = high_resolution_clock::now();

        cout << "solve time: " << Time(start, end) << '\n' << endl;
    }
}