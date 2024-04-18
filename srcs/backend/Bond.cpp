#include "Bond.h"

bool Bond::isPureCovalent(const Atom &a, const Atom &b)
{
    if (static_cast<float>(Atom::desiredValence(a) - a.valency()) / (Atom::desiredValence(b) - b.valency()) ==
            (Atom::desiredValence(a) - a.valency()) / (Atom::desiredValence(b) - b.valency()) ||
        static_cast<float>(Atom::desiredValence(b) - b.valency()) / (Atom::desiredValence(a) - a.valency()) ==
                (Atom::desiredValence(b) - b.valency()) / (Atom::desiredValence(a) - a.valency()) &&
            std::abs(ElectroNegativity::ID(a) - ElectroNegativity::ID(b) < 0.4))
    {
        return true;
    }
    return false;
}

bool Bond::isIonic(const Atom &a, const Atom &b)
{
    if (
        ((a.valency() - Atom::desiredValence(a) > 0 && b.valency() - Atom::desiredValence(b) < 0) && std::abs(b.valency() - Atom::desiredValence(b)) <= std::abs(a.valency() - Atom::desiredValence(a)))

        || ((a.valency() - Atom::desiredValence(a) < 0 && b.valency() - Atom::desiredValence(b) > 0) && std::abs(b.valency() - Atom::desiredValence(b)) >= std::abs(a.valency() - Atom::desiredValence(a)))

               && std::abs(ElectroNegativity::ID(a) - ElectroNegativity::ID(b) > 1.8))
    {
        return true;
    }
    return false;
}