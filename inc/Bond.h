#pragma once
#include "Atom.h"
#include "ElectroNegativityTable.h"

#define _IONIC -2
#define _POLAR_COVALENT -1
#define _COVALENT 0
#define _NEG_INF -9999999


enum BOND_TYPE
{
    IONIC = _IONIC,
    POLAR_COVALENT = _POLAR_COVALENT,
    COVALENT = _COVALENT,
    NEG_INF  = _NEG_INF
};

class Bond
{
public:
    std::initializer_list<Atom> bonds;

    Bond(const std::initializer_list<Atom> &bond_input) : bonds(bond_input) {}
    Atom a1;
    Atom a2;
    bool pairwiseElectrons(int a, int b) {
        if (a1.protons == a and a2.protons == b)
            return (true);
        if (a1.protons == b and a2.protons == a)
            return (true);
        return (false);
    }
    bool static isPureCovalent(const Atom &a, const Atom &b);
    bool static isIonic(const Atom &a, const Atom &b);
    static BOND_TYPE getBondType(Atom &a1, Atom &a2) const ;
};