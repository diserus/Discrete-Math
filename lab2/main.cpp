#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<char> CreateSetA()
{
    vector<char> setA;
    string line;

    cout << "Enter the elements of set A: ";
    getline(cin, line);
    for (char elem : line)
        if (elem != ' ')
            setA.push_back(elem);

    sort(setA.begin(), setA.end());
    setA.erase(unique(setA.begin(), setA.end()), setA.end());
    return setA;
}

int main()
{
    vector<char> setA = CreateSetA();
    return 0;
}
