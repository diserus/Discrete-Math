#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
using namespace std;

void PrintSet(const vector<char> &set)
{
    cout << "{ ";
    for (auto i : set)
        cout << i << " ";
    cout << "}\n";
}

bool Subset(vector<char> &set1, vector<char> &set2)
{
    for (auto elem : set1)
    {
        if (find(set2.begin(), set2.end(), elem) == set2.end())
        {
            return false;
        }
    }
    return true;
}

vector<char> Union(vector<char> &set1, vector<char> &set2)
{
    vector<char> result;
    size_t i = 0;
    size_t j = 0;
    while (i < set1.size() && j < set2.size())
    {
        if (set1[i] < set2[j])
            result.push_back(set1[i++]);
        else if (set2[j] < set1[i])
            result.push_back(set2[j++]);

        else
        {
            result.push_back(set2[j++]);
            i++;
        }
    }

    while (i < set1.size())
    {
        result.push_back(set1[i++]);
    }

    while (j < set2.size())
    {
        result.push_back(set2[j++]);
    }
    return result;
}

vector<char> Intersection(vector<char> &set1, vector<char> &set2)
{
    vector<char> result;
    size_t i = 0;
    size_t j = 0;

    while (i < set1.size() && j < set2.size())
    {
        if (set1[i] < set2[j])
        {
            i++;
        }
        else if (set1[i] > set2[j])
        {
            j++;
        }
        else
        {
            result.push_back(set2[j]);
            i++;
            j++;
        }
    }

    return result;
}

vector<char> Difference(vector<char> &set1, vector<char> &set2)
{
    vector<char> result;

    size_t i = 0;
    size_t j = 0;

    while (i < set1.size() && j < set2.size())
    {
        if (set1[i] < set2[j])
        {
            result.push_back(set1[i]);
            i++;
        }
        else if (set1[i] > set2[j])
        {
            j++;
        }
        else
        {
            i++;
            j++;
        }
    }

    while (i < set1.size())
    {
        result.push_back(set1[i]);
        i++;
    }

    return result;
}

vector<char> SymmetricDifference(vector<char> &set1, vector<char> &set2)
{
    vector<char> result;

    size_t i = 0;
    size_t j = 0;

    while (i < set1.size() && j < set2.size())
    {
        if (set1[i] < set2[j])
        {
            result.push_back(set1[i]);
            i++;
        }
        else if (set1[i] > set2[j])
        {
            result.push_back(set2[j]);
            j++;
        }
        else
        {
            i++;
            j++;
        }
    }

    while (i < set1.size())
    {
        result.push_back(set1[i]);
        i++;
    }

    while (j < set2.size())
    {
        result.push_back(set2[j]);
        j++;
    }

    return result;
}

vector<char> CreateSet()
{
    vector<char> set;
    string line;
    getline(cin, line);
    for (char elem : line)
        if (elem != ' ' && isalpha(elem))
            set.push_back(elem);
        else
        {
            cout << "Set must contains only latin letters\n";
        }
    sort(set.begin(), set.end());
    set.erase(unique(set.begin(), set.end()), set.end());
    return set;
}
int main()
{
    cout << "Enter the elements of set A: ";
    vector<char> setA = CreateSet();
    cout << "Enter the elements of set B: ";
    vector<char> setB = CreateSet();
    system("cls");
    char choice;
    do
    {
        cout << "\n\n1. Check whether A is a subset of the set B\n";
        cout << "2. Check whether B is a subset of the set A\n";
        cout << "3. Union of sets A and B\n";
        cout << "4. Intersects of sets A and B\n";
        cout << "5. Difference of sets A and B\n";
        cout << "6. Difference of sets B and A\n";
        cout << "7. Symmetric difference of sets A and B\n";
        cout << "8. Change sets\n";
        cout << "0. Exit\n";
        cout << "Enter a number of operation: ";

        cin >> choice;
        cin.ignore();
        system("cls");

        switch (choice)
        {
        case '1':
            if (Subset(setA, setB))
                cout << "Set A is a subset of set B\n";
            else
                cout << "Set A is not a subset of set B\n";
            break;
        case '2':
            if (Subset(setB, setA))
                cout << "Set B is a subset of set A\n";
            else
                cout << "Set B is not a subset of set A\n";
            break;
        case '3':
            cout << "Union of sets A and B: ";
            PrintSet(Union(setA, setB));
            break;
        case '4':
            cout << "Intersect of sets A and B: ";
            PrintSet(Intersection(setA, setB));
            break;
        case '5':
            cout << "Difference of sets A and B: ";
            PrintSet(Difference(setA, setB));
            break;
        case '6':
            cout << "Difference of sets B and A: ";
            PrintSet(Difference(setB, setA));
            break;
        case '7':
            cout << "Symmetric difference of sets B and A: ";
            PrintSet(SymmetricDifference(setB, setA));
            break;
        case '8':
            system("cls");
            cout << "Enter the elements of set A: ";
            setA = CreateSet();
            cout << "Enter the elements of set B: ";
            setB = CreateSet();

            break;
        default:
            if (choice != '0')
            {
                system("cls");
                cout << "Incorrect option\n";
                Sleep(1200);
                break;
            }
        }
        cout << "A set: ";
        PrintSet(setA);

        cout << "B set: ";
        PrintSet(setB);
    } while (choice != '0');
    system("cls");
    return 0;
}
