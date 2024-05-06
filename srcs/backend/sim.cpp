#include "simulator.hpp"




std::vector<Molecule> parse(std::string filename)
{

}

void calculateInitialAtomicState(std::vector<Molecule> &molecules)
{

}

MECH_TYPE determineMechanismType(std::vector<Molecule> &reactants)
{

}

SubMolecule identifyLeavingGroup(std::vector<Molecule> &reactants)
{

}

SubMolecule identifyNucleophile(std::vector<Molecule> &reactants)
{

}

void constructProduct(std::vector<Molecule> &molecules)
{

}

std::vector<SubMolecule> seperateReactants(std::vector<Molecule> &molecules, SubMolecule &LG, SubMolecule &NU)
{

}

SubMolecule constructCarbocation(std::vector<Molecule> &intermediates)
{

}

SubMolecule identifyStableLGResonanceStructure(SubMolecule &LG)
{

}

Molecule attachCarboToLG(SubMolecule &carbocation, SubMolecule &LG)
{

}

void saveProduct()
{

}

/*
    Pipeline()
    read input from file
    parse()
    calculateInitialAtomicState()
    determineMechanismType()
    
    
    identifyLeavingGroup()
    identifyNucleophile()
    constructProduct()
    while(NOT_IN_PROXIMITY)
        ;
    seperateReactants();
    constructCarbocation();



    identifyStableLGResonanceStructure();
    attachCarboToLG();
    saveProduct();
*/


int main(int argc, char **argv) {

    if (argc != 2) {
        // error msg
        return 0;
    }

    //STEP 1: Parse user input:
    std::vector<Molecule> reactants = parse(std::string(argv[1]));
    
    //STEP 2: Calculate Initial Atomic State of all atoms:
    calculateInitialAtomicState(reactants);

    //STEP 3: Determine Reaction Mechanism Type based on IAS:
    MECH_TYPE rxnType = determineMechanismType(reactants);

    //STEP 4: Identify Leaving Group LG (a sub molecule from one of the moleules in <reactants>)
    SubMolecule LG = identifyLeavingGroup(reactants);

    //STEP 5: Identify Nuclepphile
    SubMolecule NU = identifyNucleophile(reactants);


    //*******************************************************************************

    //STEP 6: Seperate LG & NU from reactants
    std::vector<SubMolecule> intermediates = seperateReactants(reactants, LG, NU);

    //STEP 7: Retrieve CarboCation:
    SubMolecule carbocation = constructCarbocation(intermediates);

    //STEP 8: Identify most stable LG Resonance Structure IF ANY:
    SubMolecule stableLG = identifyStableLGResonanceStructure(LG);

    //STEP 9: Attach LG to Carbo:
    Molecule product = attachCarboToLG(carbocation, stableLG);

    //STEP 10: Save Product & render to GUI:
    saveProduct();

    
    return (0);
}