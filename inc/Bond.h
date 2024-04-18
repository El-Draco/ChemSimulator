#pragma once
#include "Atom.h"
#include "ElectroNegativityTable.h"

class A_Bonds {
public:
    std::initializer_list<Atom> bonds;
    A_Bonds(const std::initializer_list<Atom>& bond_input) : bonds(bond_input) {}

    bool static CheckPureCovalent(Atom a, Atom b) {
        if (static_cast<float>(Atom::ValenceDesired(a) - a.valency())
            / (Atom::ValenceDesired(b) - b.valency()) == 
            (Atom::ValenceDesired(a) - a.valency()) / (Atom::ValenceDesired(b) - b.valency())
         || static_cast<float>(Atom::ValenceDesired(b) - b.valency())
            / (Atom::ValenceDesired(a) - a.valency()) == 
            (Atom::ValenceDesired(b) - b.valency()) / (Atom::ValenceDesired(a) - a.valency())
         && std::abs(ElectroNegativity::ID(a) - ElectroNegativity::ID(b) < 0.4)) {
            return true;
        }
        return false;
    }

    bool static CheckIonic(Atom a, Atom b) {
        if (
          ((a.valency() - Atom::ValenceDesired(a) > 0 && b.valency() - Atom::ValenceDesired(b) < 0)
        &&  std::abs(b.valency() - Atom::ValenceDesired(b)) <= std::abs(a.valency() - Atom::ValenceDesired(a)))
        
        || ((a.valency() - Atom::ValenceDesired(a) < 0 && b.valency() - Atom::ValenceDesired(b) > 0)
        &&  std::abs(b.valency() - Atom::ValenceDesired(b)) >= std::abs(a.valency() - Atom::ValenceDesired(a)))

        &&  std::abs(ElectroNegativity::ID(a) - ElectroNegativity::ID(b) > 1.8)) {
            return true;
        }
        return false;
    }
};
