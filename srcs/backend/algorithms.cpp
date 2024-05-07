#include "simulator.hpp"
#include <set>


using namespace std;

struct ElectronConfig {
    std::vector<int> orbitals;
};

// Function to parse electron configurations from a file
std::unordered_map<int, ElectronConfig> parseElectronConfigurations(const std::string& filename) {
    std::unordered_map<int, ElectronConfig> electronConfigs;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return electronConfigs;
    }

    std::string line;
    int atomicNumber = 1;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string orbitalStr;

        // Parse each orbital
        std::vector<int> orbitals;
        while (std::getline(iss, orbitalStr, ',')) {
            orbitals.push_back(std::stoi(orbitalStr));
        }

        // Save electron configuration for the current atomic number
        electronConfigs[atomicNumber++] = {orbitals};
    }

    return electronConfigs;
}

// Function to get electron configuration for a specific atomic number
std::vector<int> getElecConfig(int atomicNumber, const std::unordered_map<int, ElectronConfig>& electronConfigs) {
    if (electronConfigs.find(atomicNumber) != electronConfigs.end()) {
        return electronConfigs.at(atomicNumber).orbitals;
    } else {
        std::cerr << "Electron configuration not found for atomic number " << atomicNumber << std::endl;
        return {};
    }
}

//TODO:
int size(Atom &atom) {
//


    return (0);
}

//TODO:
std::vector<int> getCovalentBondWeights(Atom &atom) {
    std::vector<int> weights;
    return (weights);
}


//TODO:
std::set<Atom> getNeighbours(Atom &atom) {
    std::set<Atom> N;
    return (N);
}


//TODO:
int getWeight(Atom &a1, Atom &a2) {
    // Bond bond =  std::vector
    return (0);
}


//DONE
void c_methyl_shift(Atom &a1, Atom &a2, Atom &a3) {
    SubMolecule CH3;                                               //TODO
    //A1 IS POSITIVELY CHARGED CARBON
    //A2 IS THE ONE THAT IS GOING TO TAKE THE POSTIIVE CHARGE
    //A1 CHARGE REDUCED BY 1
    a1.charge -= 1;

    //A2 CHARGE INC BY 1
    a2.charge += 1;

    //TAKE A CH3 FROM A2, BREAK IT, GIVE IT TO A1
    a2 = a2 - CH3.root;
    a1 = a1 + CH3.root;
}

//DONE
void c_hydride_shift(Atom &a1, Atom &a2) {
    //A1 IS POSITIVELY CHARGED CARBON
    //A2 IS THE ONE THAT IS GOING TO TAKE THE POSTIIVE CHARGE
    //A1 CHARGE REDUCED BY 1
    a1.charge -= 1;

    //A2 CHARGE INC BY 1
    a2.charge += 1;

    //TAKE A H FROM A2, BREAK IT, GIVE IT TO A1
    Atom _H;                                                             //TODO: create hydrogen atom here
    a2 = a2 - _H;
    a1 = a1 + _H;
}


bool isNonMetal(Atom &atom) {
    return false;
}


//DONE - Rn as sum of si
float computeResidue(int protons, int i) {
    // compute
    int R = 0; 
    std::string filename = "residue.txt";
    std::unordered_map<int, ElectronConfig> electronConfigs = parseElectronConfigurations(filename);
    std::vector<int> config = getElecConfig(protons, electronConfigs);

    for (int i = 0; i< config.size() - 1; i++) {
        R += config[i];
    }
    return (R);
}

//DONE
int maxShellNumber(int protons) {

    std::string filename = "residue.txt";
    std::unordered_map<int, ElectronConfig> electronConfigs = parseElectronConfigurations(filename);
    std::vector<int> config = getElecConfig(protons, electronConfigs);

    return (config.size());
}


int thresholdValency(const Atom &atom)
{
    int threshold = (computeResidue(atom.protons, 1) - computeResidue(atom.protons, 0))/2;
    return threshold;
}



//Algo 1:
BOND_TYPE determineBondType(const Atom &a1, const Atom &a2)
{
    if (fabs(ElectroNegativity::ID(a1) - ElectroNegativity::ID(a2)) > 1.8f)
    {
        if (a1.getValence() >= thresholdValency(a1) && a2.getValence() <= thresholdValency(a1))
            return IONIC;
    }

    if (fabs(ElectroNegativity::ID(a1) - ElectroNegativity::ID(a2)) > 0.4)
    {

        if (fabs(ElectroNegativity::ID(a1) - ElectroNegativity::ID(a2)) <= 1.8f)
        {
            if (a1.getValence() >= thresholdValency(a1) && a2.getValence() >= thresholdValency(a1))
                return (POLAR_COVALENT);
        }
    }

    if (fabs(ElectroNegativity::ID(a1) - ElectroNegativity::ID(a2)) <= 0.4f)
    {
        if (a1.getValence() >= thresholdValency(a1) && a2.getValence() >= thresholdValency(a1))
            return (COVALENT);
    }
    return (NEG_INF);
}

//Algo 2:
int getNumElecInShell(int protons, int shell) {
    return (computeResidue(protons, -maxShellNumber(protons) + shell + 1) - computeResidue(protons, -maxShellNumber(protons) + shell));
}

//Algo 3:
float computeDeltaValue(const Atom &atom) {
    int protons = atom.protons;
    if (atom.getValence() >= thresholdValency(atom))
        return (computeResidue(protons,1) - computeResidue(protons, 0) - atom.getValence());
    
    return (atom.getValence());
}

//Algo 4:
float computeFormalCharge(Atom &atom) {
    float sum = 0;
    Atom element(atom.protons, atom.neutrons);

    std::vector<int> weights = getCovalentBondWeights(atom);
    for (int i = 0; i < weights.size(); i++) {
        sum += weights[i];
    }
    return (element.valence_in_isolation() - atom.getValence() + sum);
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
    return (atom.getValence() - 2*sum);
}

//Algo 7:
bool canFormDative(Atom &a1, Atom &a2) {
    if (fabs(ElectroNegativity::ID(a1) - ElectroNegativity::ID(a2)) <= 1.8) {
        if (computeDeltaValue(a1) == 0 && computeDeltaValue(a2) >= 2) {
            if (nonBondingElectrons(a1) >= 2)
                return (true);
        }
    }
    return false;
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
        return SubMolecule(); //YOU HAVE ALGO 9
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


//Algo 11: UPDATE VISITED
//TODO ADD WHILE LOOP WITH FLAG TO CHECK IF THERE WAS A CHANGE AND REPEAT
bool carbocationShift(Atom &a1) {
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
                        c_methyl_shift(a1, a2, a3); // IF THIS CALLED THEN CHANGED
                    }
                }
            }
        }

        if (getCarbocationState(a2) > 0 && getCarbocationState(a2) < 4) {
            if (getCarbocationState(a1) < getCarbocationState(a2))
                c_hydride_shift(a1, a2); //IF THIS CALLED THEN CHANGED
        }
    }
}


//Algo 12:
float computeAtomicCharge(Atom &atom) {
    
    if (isNonMetal(atom))
        return (computeFormalCharge(atom));
    Atom element(atom.protons, atom.neutrons);
    float sum = 0;

    std::vector<int> weights = getCovalentBondWeights(atom);
    for (int i = 0; i < weights.size(); i++) {
        sum += weights[i];
    }

    return (element.valence_in_isolation() - atom.getValence() - sum);
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
    if (ElectroNegativity::ID(a1) > ElectroNegativity::ID(a2))
        return (a1);
    if (ElectroNegativity::ID(a1) < ElectroNegativity::ID(a2))
        return (a2); 
    float sum1 = 0;
    float sum2 = 0;
    
    std::set<Atom> N1 = getNeighbours(a1);
    N1.erase(u);
    std::set<Atom> N2 = getNeighbours(a2);
    N2.erase(u);

    for (Atom v: N1) {
        sum1 += ElectroNegativity::ID(v) / (u.position - v.position).magnitude();
    }
    for (Atom v: N2) {
        sum2 += ElectroNegativity::ID(v) / (u.position - v.position).magnitude();
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

    if (ElectroNegativity::ID(a1) < ElectroNegativity::ID(a2))
        return (a1);
    return (a2);
}

//Algo 15:
// void SN1_Mechanism(Molecule &m1, Molecule &m2) {
//     std::vector<SubMolecule> potentialLGs = findPotentialLGs(m1);
//     std::vector<SubMolecule> potentialNUs = findPotentialNUs(m2);
//     SubMolecule LG = findMax(potentialLGs);
//     SubMolecule NU = findMax(potentialNUs);
//     m1.breakBond(LG);
//     m2.breakBond(NU);
//     m1 = performOptimalCarbocationRearrangement(m1);
//     LG = performOptimalResonanceStructure(LG);
//     attach(m1, NU);
//     attach(m2, LG);
// }


//Algo 16:
// void SN2_Mechanism(Molecule &m1, Molecule &m2, Molecule &ms) {
//     std::vector<SubMolecule> potentialLGs = findPotentialLGs(m1);
//     std::vector<SubMolecule> potentialNUs = findPotentialNUs(m2, ms);  
//     SubMolecule LG = findMax(potentialLGs);
//     SubMolecule NU = findMax(potentialNUs);
//     m1.breakBond(LG);
//     m2.breakBond(NU);
//     LG = performOptimalResonanceStructure(LG);
//     attach(m1, NU);
//     attach(m2, LG);
// }