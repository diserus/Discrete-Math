#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
using namespace std;
typedef struct List
{
    vector<char> pair;
    List *next;
};
void PrintRelation(List *head)
{
    List *temp = head;
    cout << "{ ";
    while (temp != nullptr)
    {
        cout << "(" << temp->pair[0] << ", " << temp->pair[1] << ") ";
        temp = temp->next;
    }
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
    cout << "}";
}

void PrintSet(const vector<char> &set)
{
    cout << "{ ";
    for (auto i : set)
        cout << i << " ";
    cout << "}\n";
}
vector<vector<char>> GetRelationMatrix(const vector<char> &set, List *head)
{
    cout << "Binary relation matrix:\n";
    int n = set.size();
    vector<vector<char>> matrix(n, vector<char>(n, '0'));

    List *temp = head;
    while (temp != nullptr)
    {
        char first = temp->pair[0];
        char second = temp->pair[1];
        int index1 = find(set.begin(), set.end(), first) - set.begin();
        int index2 = find(set.begin(), set.end(), second) - set.begin();

        matrix[index1][index2] = '1';
        temp = temp->next;
    }
    return matrix;
}
void PrintRelationMatrix(const vector<vector<char>> &matrix, const vector<char> &setA)
{
    int n = matrix.size();
    cout << "  ";
    for (int i = 0; i < n; i++)
        cout << setA[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; i++)
    {
        cout << setA[i] << " ";
        for (int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
void PrintRelationProperties(const vector<vector<char>> &matrix)
{
    bool reflexive = true;
    bool symmetric = true;
    bool antisymmetric = true;
    bool transitive = true;

    int n = matrix.size();

    for (int i = 0; i < n; i++)
        if (matrix[i][i] == '0')
        {
            reflexive = false;
            break;
        }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] == '1')
            {
                if (matrix[j][i] == '0')
                    symmetric = false;
                if (i != j && matrix[j][i] == '1')
                    antisymmetric = false;
            }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] == '1')
                for (int k = 0; k < n; k++)
                    if (matrix[j][k] == '1' && matrix[i][k] == '0')
                        transitive = false;

    cout << "Properties of the binary relation:\n";
    cout << "Reflexive: " << (reflexive ? "Yes" : "No") << endl;
    cout << "Symmetric: " << (symmetric ? "Yes" : "No") << endl;
    cout << "Antisymmetric: " << (antisymmetric ? "Yes" : "No") << endl;
    cout << "Transitive: " << (transitive ? "Yes" : "No") << endl;
}
vector<char> CreateSet()
{
    std::string str;
    int n;

    while (true)
    {
        std::cout << "Enter the number of elements in the set: ";
        std::cin >> str;

        bool isNumber = true;
        for (auto c : str)
        {
            if (!std::isdigit(c))
            {
                isNumber = false;
                std::cout << "Expected int\n";
                break;
            }
        }

        if (isNumber)
        {
            n = std::stoi(str);
            break;
        }
    }
    vector<char> setA;
    cout << "Enter the elements of the set: ";
    for (int i = 0; i < n; i++)
    {
        char element;
        cin >> element;
        if (isalpha(element))
            setA.push_back(element);
        else
        {
            cout << "Set must contains only latin letters\n";
            i--;
        }
    }
    sort(setA.begin(), setA.end());
    setA.erase(unique(setA.begin(), setA.end()), setA.end());
    return setA;
}
List *CreateRelation(List *(&R), vector<char> &setA)
{
    List *current = nullptr;

    cout << "Enter the pairs of relation R:\n";
    char choice;
    do
    {
        cout << "Do you want to enter a pair?\n";
        cout << "1. Yes\n";
        cout << "2. No\n";
        cin >> choice;
        if (choice == '1')
        {
            List *newPair = new List;
            char first, second;
            cout << "Enter a pair: ";
            cin >> first >> second;
            if (find(setA.begin(), setA.end(), first) == setA.end() ||
                find(setA.begin(), setA.end(), second) == setA.end())
            {
                cout << "Invalid pair. Elements not in the set.\n";
                delete newPair;
                continue;
            }

            newPair->pair.push_back(first);
            newPair->pair.push_back(second);
            newPair->next = nullptr;

            if (R == nullptr)
            {
                R = newPair;
                current = R;
            }
            else
            {
                current->next = newPair;
                current = newPair;
            }
        }
        else if (!(choice == '2'))
        {
            cout << "Incorrect choice\n";
        }
    } while (choice != '2');
    return R;
}
void ChangeMatrix(vector<vector<char>> &matrix, vector<char> set)
{
    char row, column;
    cout << "Enter the element to change (row column): ";
    cin >> row >> column;

    int rowIndex = find(set.begin(), set.end(), row) - set.begin();
    int colIndex = find(set.begin(), set.end(), column) - set.begin();

    if (rowIndex < set.size() && colIndex < set.size())
    {
        matrix[rowIndex][colIndex] = (matrix[rowIndex][colIndex] == '0') ? '1' : '0';
    }
    else
    {
        cout << "Invalid element\n";
    }
}
int main()
{
    vector<char> setA = CreateSet();
    List *R = NULL;
    R = CreateRelation(R, setA);
    char choice;
    vector<vector<char>> matrix = GetRelationMatrix(setA, R);
    do
    {
        PrintRelationMatrix(matrix, setA);
        PrintRelationProperties(matrix);
        cout << "1. Change relation matrix\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case '1':
            ChangeMatrix(matrix, setA);
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
    } while (choice != '0');
    return 0;
}
