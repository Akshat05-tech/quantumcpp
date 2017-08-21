#include <cmath>
#include <iostream>
#include "molecule.h"
using namespace std;

int main()
{
    int n;

    cin >> n;
    double xc_arr[n];
    double yc_arr[n];
    double zc_arr[n];
    int z_arr[n];

    for (int i = 0; i < n; i++) {
        cin >> z_arr[i] >> xc_arr[i] >> yc_arr[i] >> zc_arr[i];
    }
    Molecule mol = Molecule(n, xc_arr, yc_arr, zc_arr, z_arr);
}
