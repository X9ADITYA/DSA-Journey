
#include <iostream>
using namespace std;

int main()
{
    int poly[10], degree;

    cout << "Enter degree: ";
    cin >> degree;

    cout << "Enter coefficients from x^0 to x^degree:\n";

    for (int i = 0; i <= degree; i++)
    {
        cin >> poly[i];
    }

    cout << "Polynomial: ";

    for (int i = degree; i >= 0; i--)
    {
        if (poly[i] != 0)
        {
            cout << poly[i];

            if (i > 0)
                cout << "x";

            if (i > 1)
                cout << "^" << i;

            if (i > 0)
                cout << " + ";
        }
    }

    return 0;
}

