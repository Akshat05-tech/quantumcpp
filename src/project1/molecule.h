#ifndef MOLECULEH
#define MOLECULEH

#include <string>
#define ARMA_DONT_USE_WRAPPER

#include <armadillo>

using namespace std;
using namespace arma;


class Molecule {
public:
    int natom;
    int charge;
    int* zvals;
    mat geom;

    string point_group;

    void print_geom();
    void rotate(double phi);
    void translate(double x, double y, double z);
    double bond_length(int atom1, int atom2);
    double angle(int atom1, int atom2, int atom3);
    double torsion(int atom1, int atom2, int atom3, int atom4);

    rowvec get_bond(int i, int j);
    mat get_bond_lengths();

    Molecule(int n, double x_coord[], double y_coord[], double z_coord[], int z[]);
};

#endif
