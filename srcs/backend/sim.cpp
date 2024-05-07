#include "simulator.hpp"
#include "algorithms.cpp"
using namespace std;
#include <set>
std::vector<Molecule> parse(std::string filename)
{

}

void saveProduct()
{

}

//-------------------------------TODO FOR OMAR
Atom &identifyLeavingGroup(Molecule &m)
{
    //find all possible LGs
    //take every neighbor of every carbon (other than carbons) and put in a vector
    std::vector<Atom> possibleLGs = getPossibleLGs(m);
    std::vector<Atom> carbons_for_LGs;
    for (Atom carbon : m.atoms){
        if (carbon.protons != 6 || carbon.degree() != 4){
            continue;
        }
        for (Atom neighbor : getNeighbours(carbon)){
            if (neighbor.protons != 6){
                possibleLGs.push_back(neighbor);
                carbons_for_LGs.push_back(carbon);
            }
        }
    }
    int max = 0;
    //find the ones with max resonance
    std::vector<Atom> newPossibleLGs;
    for (Atom atom : possibleLGs){
        if (getNumOfResonanceStructures(atom) > max){
            max = getNumOfResonanceStructures(atom);
        }
    }
    for (Atom atom : possibleLGs){
        if (getNumOfResonanceStructures(atom) == max){
            newPossibleLGs.push_back(atom);
        }
    }
    //find the ones with max size
    possibleLGs = newPossibleLGs; //MAKE SURE ITS BY COPY HERE
    newPossibleLGs.clear();//MAKE SURE TO EMPTY newPossibleLGs HERE
    max = 0;
    for (Atom atom : possibleLGs){
        if (size(atom) > max){
            max = size(atom);
        }
    }
    for (Atom &atom : possibleLGs){
        if (size(atom) == max){
            newPossibleLGs.push_back(atom);
        }
    }
    possibleLGs = newPossibleLGs; // MAKE SURE ITS BY COPY HERE
    newPossibleLGs.clear();// MAKE SURE TO EMPTY newPossibleLGs HERE
    //find the ones with max electronegativity                     
    max = 0;
    for (Atom atom : possibleLGs){
        if (ElectroNegativity::ID(atom.protons) > max){
            max = ElectroNegativity::ID(atom.protons);
        }
    }
    for (Atom atom : possibleLGs){
        if (ElectroNegativity::ID(atom.protons) == max){
            newPossibleLGs.push_back(atom);
        }
    }
    possibleLGs = newPossibleLGs;
    newPossibleLGs.clear();
                          //find groups by BFS
    
    //find max electronegativity (approx of inductive effect) of entire group
    //randomize 1 item from the final list.
}

//-------------------------------TODO FOR RADI
Atom &getAdjacentAtom(Molecule &parent, Atom &to_remove) {

}

//DONE
SubMolecule &constructCarbocation(Molecule &m)
{
    //YOU'RE GONNA HAVE A WHILE LOOP UNTIL YOU HAVE NO CHANGE
    //MAKE A FLAG TO CHECK FOR CHANGE
    //THIS ONE IS IN ANOTHER FUNCTION FROM ONE OF THE ALGORTIHMS IN PAPER
    Atom &carbon = m.root;
    SubMolecule &carbocation = *(carbocationShift(carbon).parent);
    return (carbocation);
}
//DONE
std::vector<Atom> getPotentialNUs(Molecule &mol) {
    return (mol.atoms);
}

//DONE
SubMolecule identifyStableLGResonanceStructure(SubMolecule &LG)
{
    //ALGO9
    return getMostCommonResonanceStructure(LG.root, LG);
}

//DONE
void calculateInitialAtomicState(Molecule &M)
{
    for (Atom &m : M.atoms) {
        int Rn0 = computeResidue(m.protons, 0);
        m.valence = m.electrons - Rn0;
        m.delta = computeDeltaValue(m);
    }
}

//DONE
MECH_TYPE determineMechanismType(SubMolecule &carbocation, MECH_TYPE user_input)
{
    //AFTER YOU KNOW LG AND NU, IF CARBOCATION STATE IS 3, THEN IT HAS TO BE SN1
    // IF CARBOCATION STATE IS 2, THEN WE DONT KNOW, USE USER INPUT
    // IF CARBOCATION STATE IS 1 OR 0, IT HAS TO BE SN2
    if (carbocation.root.degree() == 3)
        return (SN1);
    if (carbocation.root.degree() == 2)
        return (user_input);
    return (SN2);

}

//DONE
bool isSolventProtic(Molecule &m){
    //loop through all bonds, and see if it has H-N, H-O, or H-F, if yes, true
    //otherwise, false (1-7)(1-8)(1-9)
    for (Bond &bond : m.bonds) {
        if (bond.pairwiseElectrons(1,7) || bond.pairwiseElectrons(1,8) || bond.pairwiseElectrons(1,9))
            return (true);
    }
    return (false);
}

//DONE
std::vector<Atom> largest_size(std::vector<Atom> potentialNUs) {
    std::vector<Atom> NUs;
    int largest = potentialNUs[0].size;

    for (Atom &atom: potentialNUs) {
        if (atom.size > largest)
            largest = atom.size;
    }
    for (Atom &atom: potentialNUs) {
        if (atom.size == largest)
            NUs.push_back(atom);
    }
    return NUs;
}

//DONE
std::vector<Atom> smallest_size(std::vector<Atom> potentialNUs) {
    std::vector<Atom> NUs;
    int smallest = potentialNUs[0].size;

    for (Atom &atom: potentialNUs) {
        if (atom.size < smallest)
            smallest = atom.size;
    }
    for (Atom &atom: potentialNUs) {
        if (atom.size == smallest)
            NUs.push_back(atom);
    }
    return NUs;
}

//DONE
std::vector<Atom> max_electroneg(std::vector<Atom> potentialNUs) {
    std::vector<Atom> NUs;
    int largest = ElectroNegativity::ID(potentialNUs[0]);

    for (Atom &atom: potentialNUs) {
        if (atom.size > largest)
            largest = atom.size;
    }
    for (Atom &atom: potentialNUs) {
        if (atom.size == largest)
            NUs.push_back(atom);
    }
    return NUs;
}

//DONE
Atom &identifyNucleophile(Molecule &mol, Molecule &solvent)
{
    //find neighbors of every single atom (all are potential nucleophiles)
    std::vector<Atom> potentialNUs = getPotentialNUs(mol);                                       //convert Atom to SubMolecule
    
    //if solvent is protic, take Nus by largest size
    if (isSolventProtic(solvent))
        potentialNUs = largest_size(potentialNUs);
    //else if solvent is not protic, take Nus by smallest size
    else 
        potentialNUs = smallest_size(potentialNUs);
    //take all the ones with maximum electrongativity
    potentialNUs = max_electroneg(potentialNUs);
    //ADD BFS TO GET Nu GROUP WITHOUT PREVIOUSLY ATTACHED PART

    //return a random one in the resulting list.
    return potentialNUs[rand()%potentialNUs.size()];
}

//DONE
Molecule attachCarboToNu(SubMolecule &carbocation, Atom &Nu)
{
    //ATTACH Nu AND CARBOCATION BY DATIVE COVALENT BOND
    //LOOK AT ROOT OF Nu (THE ONE THAT JUST LEFT MOL2)
    //THAT ONE IS GONNA HAVE 2 LONE PAIRS
    //MAKE IT BOND WITH CARBON
    //MAKE A BOND FROM C WITH + CHARGE AND ROOT OF Nu
    Atom &carbocationRoot = carbocation.root;
    Atom &product = carbocation.root + Nu;

    carbocationRoot.valence +=2;
    carbocationRoot.delta -=2;

    //CARBON VALENCE INC BY 2 (AND DELTA DECREASES BY 2)
    // ROOT OF Nu STAYS THE SAME
    return (*product.parent);
}

//DONE
Molecule &ionicSeparation(Atom &atom, Atom &to_separate){
    atom = atom - to_separate;

    //charges change by 1 (the donating atom becomes positive, the receiving atom becomes negative)
    atom.charge +=1;
    to_separate.charge -=1;

    //valence and deltas stay the same because no electrons moved
    return (*atom.parent);
}

//DONE
Molecule &heterolyticCleavage(Molecule &parent, Atom &to_remove) {

    Atom &parent_c = getAdjacentAtom(parent, to_remove);

    Atom &more_en = parent_c;
    Atom &less_en = to_remove;
    Atom &temp = more_en;

    if (ElectroNegativity::ID(more_en) < ElectroNegativity::ID(less_en))
    {
        //std::swap(more_en, less_en)
        more_en = less_en;
        less_en = temp;
    }

    parent_c = parent_c - to_remove;
    //THE ONE THAT IS MORE ELECTRONEGATIVE WILL STEAL AN ELECTRON FROM THE ONE THAT IS LESS ELECTRONEGATIVE
    //MORE(EN) IS GONNA HAVE NEGATIVE CHARGE BY 1
    more_en.charge -=1;

    //LESS(EN) IS GONNA HAVE POSITIVE CHARGE BY 1
    less_en.charge +=1;

    //LESS(EN) DELTA VALUE INCREASES BY 2 (VALENCE DECREASES BY 2)
    less_en.charge +=2;
    less_en.valence -=2;

    //MORE(EN) DELTA VALUE STAYS THE SAME (VALENCE STAYS THE SAME)
    return (parent);
}

//DONE
Molecule NubondSeparation(Molecule &NucleophilicMol, Atom &Nu) {

    Molecule &Mol_withoutNu = NucleophilicMol;
    //CHECK IF BOND IS IONIC (EN(DIFF) >= 1.8) OTHERWISE ITS COVALENT
    BOND_TYPE btype = Bond::getBondType(NucleophilicMol.root, Nu);
    //IF IONIC, THEN IONICSEPRATION(INPUTS)
    if (btype == IONIC)
        Mol_withoutNu = ionicSeparation(NucleophilicMol.root, Nu);
    //ELSE IF COVALENT, THEN HETEROLYTICCLEAVAGE(INPUTS)
    else if (btype == COVALENT)
        Mol_withoutNu = heterolyticCleavage(NucleophilicMol, Nu);                                 //SEEMS WRONG ??????
    //RETURN
    return (Mol_withoutNu);
}

//DONE
Molecule attachMol2toLG(SubMolecule &Mol_withoutNu, SubMolecule &stableLG) {
    //VALENCE DOESNT CHANGE, DELTAS DONT CHANGE, CHARGES BECOME 0 FOR ROOTS, 
    //BUT YOU JUST MAKE A BOND WITH THE ROOTS
    Mol_withoutNu.root.charge = 0;
    stableLG.root.charge = 0;
    Molecule product = Mol_withoutNu + stableLG;
    return product;
}

int main(int argc, char **argv) {

    if (argc != 2) {
        // error msg
        return 0;
    }

    //STEP 1: Parse user input:
    MECH_TYPE user_rxn_choice = SN1;
    if (std::string(argv[1]).compare("SN2"))
        user_rxn_choice = SN2;
    std::vector<Molecule> reactants = parse(std::string(argv[2]));

    Molecule Substrate = reactants[0];
    Molecule NucleophilicMol = reactants[1];
    Molecule Solvent = reactants[2];
    
    //STEP 2: Calculate Initial Atomic State of all atoms:
    calculateInitialAtomicState(Substrate);         // update deltas, valencies, (if we had quantum it would also update bond lengths)
    calculateInitialAtomicState(NucleophilicMol);
    calculateInitialAtomicState(Solvent);

    //STEP 3: Identify Leaving Group LG (a sub molecule from one of the moleules in <reactants>)
    Atom &LG = identifyLeavingGroup(Substrate); //UPDATE INPUT TYPE TO BE MOLECULE NOT VECTOR OF MOLECULES

    //STEP 4: Identify Nucleophile
    Atom &NU = identifyNucleophile(NucleophilicMol, Solvent);

    //STEP 5: Seperate LG & NU from reactants
    SubMolecule Substrate_withoutLG = heterolyticCleavage(Substrate, LG);
    SubMolecule Mol_withoutNu = NubondSeparation(NucleophilicMol, NU);


    //STEP 6: Retrieve CarboCation:
    SubMolecule carbocation = constructCarbocation(Substrate_withoutLG);
    

    //************************************LOCATION OF THIS IS WEIRD**********CHECK WITH OMAR
    MECH_TYPE rxnType = determineMechanismType(carbocation, user_rxn_choice);// USER INPUT FROM FRONTEND AND IF YOU HAVE FILE INPUTS NOT FROM GUI, SET VARIABLE IN COMMAND LINE

    //STEP 7: Identify most stable LG Resonance Structure IF ANY:
    SubMolecule stableLG = identifyStableLGResonanceStructure(*LG.parent);

    //STEP 8: Attach LG to Carbo:
    Molecule product1 = attachCarboToNu(carbocation, NU);
    
    Molecule product2 = attachMol2toLG(Mol_withoutNu, stableLG);


    //STEP 10: Save Product & render to GUI:
    saveProduct();

    
    return (0);
}