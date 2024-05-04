# pragma once

#include <iostream>
#include <string>
#include "Atom.h"
#include "ElectroNegativityTable.h"
#include "Molecule.h"
#include "ErrorHandler.h"
#include "Bond.h"
#include <list>
#include <fstream>


#define SN_1 101
#define SN_2 102

#define IN_PROXIMITY 0

enum MECH_TYPE {
    SN1 = SN_1,
    SN2 = SN_2
};
std::vector<Molecule> parse(std::string filename);
void calculateInitialAtomicState(std::vector<Molecule> &molecules);
MECH_TYPE determineMechanismType(std::vector<Molecule> &molecules);
SubMolecule identifyLeavingGroup(std::vector<Molecule> &molecules);
SubMolecule identifyNucleophile(std::vector<Molecule> &molecules);
void constructProduct();
std::vector<SubMolecule> seperateReactants();
SubMolecule constructCarbocation(std::vector<Molecule> &reactants);
SubMolecule identifyStableLGResonanceStructure(SubMolecule &LG);
Molecule attachCarboToLG(SubMolecule &carbocation, SubMolecule &LG);
void saveProduct();