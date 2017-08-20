#include "molecule.h"
#include <numeric>
#include <array>
#include <cmath>

using namespace std;

Molecule::Molecule(int n, double x_coord[], double y_coord[], double z_coord[], int z[])
{
    this->natom = n;
    this->geom = new double*[natom];
    this->zvals = z;
    for (int i = 0; i < n; i++) {
        this->geom[i] = new double[3];
        this->geom[i][0] = x_coord[i];
        this->geom[i][1] = y_coord[i];
        this->geom[i][2] = z_coord[i];
    }
}


double Molecule::bond(int atom1, int atom2)
{
    double** g = this->geom;
    double dx = g[atom1][0] - g[atom2][0];
    double dy = g[atom1][1] - g[atom2][1];
    double dz = g[atom1][2] - g[atom2][2];
    double distance = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));

    return distance;
}


double* Molecule::bond_vec_norm(int atom1, int atom2)
{
    double** g = this->geom;
    double bond_length = this->bond(atom1, atom2);
    double vec[3] = {
        g[atom2][0] - g[atom1][0],
        g[atom2][1] - g[atom1][1],
        g[atom2][2] - g[atom1][2]
    };
    double* vec_norm = new double[3];

    for (int i = 0; i < 3; i++) {
        vec_norm[i] = vec[i] / bond_length;
    }
    return vec_norm;
}


double Molecule::angle(int atom1, int atom2, int atom3)
{
    double* bond2 = this->bond_vec_norm(atom2, atom3);
    double* bond1 = this->bond_vec_norm(atom1, atom2);
    double costheta = dot_product(bond1, bond2);
    double theta = acos(costheta);
    return theta;
}

double dot_product(double vec1[], double vec2[]){
    double prod = 0;
    prod += vec1[0]*vec2[0];
    prod += vec1[1]*vec2[1];
    prod += vec1[2]*vec2[2];
}

double** Molecule::dist_matrix()
{
    int n = this->natom;
    double** dists;

    dists = new double*[n];
    for (int i = 0; i < n; i++) {
        dists[i] = new double[n];
        for (int j = 0; j < n; j++) {
            dists[i][j] = this->bond(i, j);
        }
    }
    return dists;
}
