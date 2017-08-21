#include "molecule.h"
#include <numeric>
#include <array>
#include <cmath>
#include <armadillo>

using namespace arma;
using namespace std;

Molecule::Molecule(int n, double x_coord[], double y_coord[], double z_coord[], int z[])
{
    this->natom = n;
    this->geom = new mat(n,3);
    this->zvals = z;
    for (int i = 0; i < n; i++) {
        this->geom(i)(0) = x_coord[i];
        this->geom(i)(1) = y_coord[i];
        this->geom(i)(2) = z_coord[i];
    }
    this->init_bond_lengths();
    this->b_angles = 0;
}


double Molecule::bond_length(int ind_atom1, int ind_atom2)
{
    rowvec atom1 = this->geom.row(ind_atom1);
    rowvec atom2 = this->geom.row(ind_atom2);
    double distance = norm(atom2-atom1);

    return distance;
}


double Molecule::angle(int atom1, int atom2, int atom3)
{
    rowvec bond1 = this->bond_vec_norm(atom2, atom1);
    double* bond2 = this->bond_vec_norm(atom2, atom3);
    double costheta = norm_dot(bond1, bond2)
    double theta = acos(costheta);

    return theta;
}


double dot_product(double vec1[], double vec2[])
{
    double prod = 0;

    prod += vec1[0] * vec2[0];
    prod += vec1[1] * vec2[1];
    prod += vec1[2] * vec2[2];
}


void Molecule::init_bond_lengths()
{
    int n = this->natom;
    double** dists = new double*[n];

    for (int i = 0; i < n; i++) {
        dists[i] = new double[n];
        for (int j = 0; j < n; j++) {
            dists[i][j] = this->bond(i, j);
        }
    }
    this->b_lengths = dists;
}

void Molecule::init_bond_angles(){

}
