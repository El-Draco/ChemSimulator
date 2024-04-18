#pragma once
#include "Atom.h"
#include "ElectroNegativityTable.h"

class Bond
{
public:
    std::initializer_list<Atom> bonds;
    Bond(const std::initializer_list<Atom> &bond_input) : bonds(bond_input) {}

    bool static isPureCovalent(const Atom &a, const Atom &b);
    bool static isIonic(const Atom &a, const Atom &b);
};