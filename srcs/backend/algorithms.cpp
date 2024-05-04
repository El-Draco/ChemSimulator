#include "simulator.hpp"
#include <set>
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

//TODO
float getElectronegativity(const Atom &atom)
{

}

//TODO
float computeResidue(int protons, int i) {
    return (0);
}


int thresholdValency(const Atom &atom)
{
    int protons = atom.protons;
    int threshold = (computeResidue(protons, 1) - computeResidue(protons, 0))/2;
    return threshold;
}



//Algo 1:
BOND_TYPE determineBondType(const Atom &a1, const Atom &a2)
{
    if (fabs(getElectronegativity(a1) - getElectronegativity(a2)) > 1.8f)
    {
        if (a1.valency() >= thresholdValency(a1) && a2.valency() <= thresholdValency(a1))
            return IONIC;
    }

    if (fabs(getElectronegativity(a1) - getElectronegativity(a2)) > 0.4)
    {

        if (fabs(getElectronegativity(a1) - getElectronegativity(a2)) <= 1.8f)
        {
            if (a1.valency() >= thresholdValency(a1) && a2.valency() >= thresholdValency(a1))
                return (POLAR_COVALENT);
        }
    }

    if (fabs(getElectronegativity(a1) - getElectronegativity(a2)) <= 0.4f)
    {
        if (a1.valency() >= thresholdValency(a1) && a2.valency() >= thresholdValency(a1))
            return (COVALENT);
    }
    return (NEG_INF);
}

//TODO:
int maxShellNumber(int protons) {

}

//Algo 2:
int getNumElecInShell(int protons, int shell) {
    return (computeResidue(protons, -maxShellNumber(protons) + shell + 1) - computeResidue(protons, -maxShellNumber(protons) + shell));
}


//Algo 3:
float computeDeltaValue(const Atom &atom) {
    int protons = atom.protons;
    if (atom.valency() >= thresholdValency(atom))
        return (computeResidue(protons,1) - computeResidue(protons, 0) - atom.valency());
    
    return (atom.valency());
}


//TODO:
std::vector<int> getCovalentBondWeights(Atom &atom) {
    std::vector<int> weights;
    return (weights);
}


//Algo 4:
float computeFormalCharge(Atom &atom) {
    float sum = 0;
    Atom element(atom.protons);

    std::vector<int> weights = getCovalentBondWeights(atom);
    for (int i = 0; i < weights.size(); i++) {
        sum += weights[i];
    }
    return (element.valency() - atom.valency() + sum);
}


//Algo 5:
float computeFormalCharge(Molecule &molecule) {
    float sum = 0;

    for (Atom atom : molecule.atoms) {
        sum += computeFormalCharge(atom);
    }
    return (sum);
}

//Algo 6:
int nonBondingElectrons(Atom &atom) {
    float sum = 0;

    std::vector<int> weights = getCovalentBondWeights(atom);
    for (int i = 0; i < weights.size(); i++) {
        sum += weights[i];
    }
    return (atom.valency() - 2*sum);
}

//Algo 7:
bool canFormDative(Atom &a1, Atom &a2) {
    if (fabs(getElectronegativity(a1) - getElectronegativity(a2)) <= 1.8) {
        if (computeDeltaValue(a1) == 0 && computeDeltaValue(a2) >= 2) {
            if (nonBondingElectrons(a1) >= 2)
                return (true);
        }
    }
    return false;
}


//TODO:
std::set<Atom> getNeighbours(Atom &atom) {
    std::set<Atom> N;
    return (N);
}


//TODO:
int getWeight(Atom &a1, Atom &a2) {
    return (0);
}

//Algo 8:
int getNumOfResonanceStructures(Atom &a1) {
    if (nonBondingElectrons(a1) < 2)
        return (0);
    
    int sum = 0;
    std::set<Atom> N1 = getNeighbours(a1);
    std::set<Atom> visited;
    for (Atom a2 : N1) {
        if (visited.find(a2) != visited.end())
            continue ;
        std::set<Atom> N2 = getNeighbours(a2);

        for (Atom a3: N2){
            if (visited.find(a3) == visited.end() && getWeight(a2,a3)==2) {
                visited.insert(a3);
                sum += 1;
            }
        }
        visited.insert(a2);
    }
    return (sum);
}



//Algo 9:

SubMolecule getMostCommonResonanceStructure(Atom &a, SubMolecule &m) {
    if (getNumOfResonanceStructures(a) == 0)
        return SubMolecule();
}




//Algo 10:
int getCarbocationState(Atom &atom) {
    if (atom.protons != 6 || computeFormalCharge(atom) != 1)
        return (NEG_INF);
    int sum = 0;

    std::set<Atom> neighbours = getNeighbours(atom);
    for (Atom atom : neighbours) {
        if (atom.protons == 6)
            sum += 1;
    }
    return (sum);
}


//TODO:
void c_methyl_shift(Atom &a1, Atom &a2) {

}

//TODO:
void c_hydride_shift(Atom &a1, Atom &a2) {
    
}

//Algo 11: UPDATE VISITED
int carbocationShift(Atom &a1) {
    if (a1.protons != 6 || computeFormalCharge(a1) != 1)
        return (NEG_INF);
    std::set<Atom> N1 = getNeighbours(a1);
    std::set<Atom> visited;
    
    for (Atom a2 : N1) {
        if (visited.find(a2) != visited.end())
            continue ;
        if (a2.protons == 6 && computeFormalCharge(a2) == 0){
            if (getCarbocationState(a2) == 4 && getCarbocationState(a1) < 3) {
                std::set<Atom> N2 = getNeighbours(a2);
                for (Atom a3 : N2) {
                    if (a3.protons == 6 and getCarbocationState(a3) == 3) {
                        c_methyl_shift(a1, a3);
                    }
                }
                
            }
        }

        if (getCarbocationState(a2) > 0 && getCarbocationState(a2) < 4) {
            if (getCarbocationState(a1) < getCarbocationState(a2))
                c_hydride_shift(a1, a2);
        }
    }
}

bool isNonMetal(Atom &atom) {
    return false;
}


//Algo 12:
float computeAtomicCharge(Atom &atom) {
    
    if (isNonMetal(atom))
        return (computeFormalCharge(atom));
    Atom element(atom.protons);
    float sum = 0;

    std::vector<int> weights = getCovalentBondWeights(atom);
    for (int i = 0; i < weights.size(); i++) {
        sum += weights[i];
    }

    return (element.valency() - atom.valency() - sum);
}


//TODO:
int size(Atom &atom) {



    return (0);
}
//Algo 13:
Atom &PairwiseLGPreference(Atom &u, Atom &a1, Atom &a2) {
    if (getNumOfResonanceStructures(a1) > getNumOfResonanceStructures(a2))
        return (a1);
    if (getNumOfResonanceStructures(a1) < getNumOfResonanceStructures(a2))
        return (a2);
    if (size(a1) > size(a2))
        return (a1);
    if (size(a1) < size(a2))
        return (a2);   
    if (getElectronegativity(a1) > getElectronegativity(a2))
        return (a1);
    if (getElectronegativity(a1) < getElectronegativity(a2))
        return (a2); 
    float sum1 = 0;
    float sum2 = 0;
    
    std::set<Atom> N1 = getNeighbours(a1);
    N1.erase(u);
    std::set<Atom> N2 = getNeighbours(a2);
    N2.erase(u);

    for (Atom v: N1) {
        sum1 += getElectronegativity(v) / (u.position - v.position).magnitude();
    }
    for (Atom v: N2) {
        sum2 += getElectronegativity(v) / (u.position - v.position).magnitude();
    }
    if (sum1 >= sum2)
        return (a1);
    return (a2);
}





//Algo 14:

Atom &NUPreference(Atom &a1, Atom &a2, Molecule &m) {
    if (size(a1) != size(a2)) {
        std::vector<Bond> bonds = m.bonds;
        for (Bond bond : bonds) {
            if (bond.pairwiseElectrons(1,7) || bond.pairwiseElectrons(1,8)
             || bond.pairwiseElectrons(1,9)) {
                if (size(a1) > size(a2))
                    return (a1);
                if (size(a1) < size(a2))
                    return (a2);    
            }
        }
        if (size(a1) < size(a2))
            return (a1);
        if (size(a1) > size(a2))
            return (a2);
    }

    if (getElectronegativity(a1) < getElectronegativity(a2))
        return (a1);
    return (a2);
}


std::vector<SubMolecule> findPotentialLGs(Molecule &m) {

}

std::vector<SubMolecule> findPotentialNUs(Molecule &m) {

}

std::vector<SubMolecule> findPotentialNUs(Molecule &m, Molecule &ms) {

}

SubMolecule findMax(std::vector<SubMolecule> potentialSubMols) {

}


SubMolecule performOptimalCarbocationRearrangement(Molecule &m) {

}

SubMolecule performOptimalResonanceStructure(Molecule &m) {

}

void attach(SubMolecule &m1, SubMolecule &m2) {

}

//Algo 15:
void SN1_Mechanism(Molecule &m1, Molecule &m2) {
    std::vector<SubMolecule> potentialLGs = findPotentialLGs(m1);
    std::vector<SubMolecule> potentialNUs = findPotentialNUs(m2);
    SubMolecule LG = findMax(potentialLGs);
    SubMolecule NU = findMax(potentialNUs);
    m1.breakBond(LG);
    m2.breakBond(NU);

    m1 = performOptimalCarbocationRearrangement(m1);
    LG = performOptimalResonanceStructure(LG);

    attach(m1, NU);
    attach(m2, LG);
}


//Algo 16:
void SN2_Mechanism(Molecule &m1, Molecule &m2, Molecule &ms) {
    std::vector<SubMolecule> potentialLGs = findPotentialLGs(m1);
    std::vector<SubMolecule> potentialNUs = findPotentialNUs(m2, ms);
    SubMolecule LG = findMax(potentialLGs);
    SubMolecule NU = findMax(potentialNUs);
    m1.breakBond(LG);
    m2.breakBond(NU);

    LG = performOptimalResonanceStructure(LG);

    attach(m1, NU);
    attach(m2, LG);
}