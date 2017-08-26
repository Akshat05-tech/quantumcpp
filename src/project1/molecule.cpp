#include "molecule.h"
#include <numeric>
#include <array>
#include <cmath>
#define ARMA_DONT_USE_WRAPPER
#include <armadillo>

using namespace arma;
using namespace std;

Molecule::Molecule(int n, double x_coord[], double y_coord[], double z_coord[], int z[])
{
    this->natom = n;
    mat geom(n, 3);
    this->geom = geom;
    this->zvals = z;
    for (int i = 0; i < n; i++) {
        this->geom(i, 0) = x_coord[i];
        this->geom(i, 1) = y_coord[i];
        this->geom(i, 2) = z_coord[i];
    }
}

rowvec Molecule::get_bond(int i, int j){
    rowvec atom1 = this->geom.row(i);
    rowvec atom2 = this->geom.row(j);
    rowvec bond = atom2-atom1;
    return bond;
}

double Molecule::bond_length(int ind_atom1, int ind_atom2)
{
    rowvec bond = this->get_bond(ind_atom2, ind_atom1);
    double distance = norm(bond);
    return distance;
}


double Molecule::angle(int atom1, int atom2, int atom3)
{
    rowvec bond1 = this->get_bond(atom2, atom1);
    rowvec bond2 = this->get_bond(atom2, atom3);
    double costheta = norm_dot(bond1, bond2);
    double theta = acos(costheta);

    return theta;
}

mat Molecule::get_bond_lengths()
{
    int n = this->natom;
    mat dists(n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dists(i, j) = norm(this->get_bond(i, j));
        }
    }
    return dists;
}
