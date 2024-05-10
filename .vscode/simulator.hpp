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
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>


#define SN_1 101
#define SN_2 102

#define IN_PROXIMITY 0

enum MECH_TYPE {
    SN1 = SN_1,
    SN2 = SN_2
};




std::unordered_map<int, ElectronConfig> parseElectronConfigurations(const std::string& filename);

//Computational Chemistry API 

Atom                &identifyLeavingGroup(Molecule &m);
std::vector<Atom>   getPotentialNUs(Molecule &mol);
SubMolecule         constructCarbocation(Molecule &m);
SubMolecule         identifyStableLGResonanceStructure(SubMolecule &LG);
void                calculateInitialAtomicState(Molecule &M);

MECH_TYPE           determineMechanismType(SubMolecule &carbocation, MECH_TYPE user_input);
bool                isSolventProtic(Molecule &m);

std::vector<Atom>   largest_size(std::vector<Atom> potentialNUs);
std::vector<Atom>   smallest_size(std::vector<Atom> potentialNUs);
std::vector<Atom>   max_electroneg(std::vector<Atom> potentialNUs);

Atom                &identifyNucleophile(Molecule &mol, Molecule &solvent);
Molecule            attachCarboToNu(SubMolecule &carbocation, Atom &Nu);
Molecule            &ionicSeparation(Atom &atom, Atom &to_separate);
Atom                &getAdjacentAtom(Molecule &parent, Atom &to_remove);
Molecule            &heterolyticCleavage(Molecule &parent, Atom &to_remove);
Molecule            NubondSeparation(Molecule &NucleophilicMol, Atom &Nu);
Molecule            attachMol2toLG(SubMolecule &Mol_withoutNu, SubMolecule &stableLG);



//Algorithms.cpp


void                c_methyl_shift(Atom &a1, Atom &a2, Atom &a3);
void                c_hydride_shift(Atom &a1, Atom &a2);
float               computeResidue(int protons, int i);
int                 maxShellNumber(int protons);
int                 thresholdValency(const Atom &atom);
BOND_TYPE           determineBondType(const Atom &a1, const Atom &a2);
int                 getNumElecInShell(int protons, int shell);
float               computeDeltaValue(const Atom &atom);
float               computeFormalCharge(Atom &atom);
float               computeFormalCharge(Molecule &molecule);
int                 nonBondingElectrons(Atom &atom);
bool                canFormDative(Atom &a1, Atom &a2);
int                 getNumOfResonanceStructures(Atom &a1);
SubMolecule         getMostCommonResonanceStructure(Atom &a, SubMolecule &m);
int                 getCarbocationState(Atom &atom);
bool                carbocationShift(Atom &a1);
float               computeAtomicCharge(Atom &atom);
Atom                &PairwiseLGPreference(Atom &u, Atom &a1, Atom &a2);
Atom                &NUPreference(Atom &a1, Atom &a2, Molecule &m) ;
void                SN1_Mechanism(Molecule &m1, Molecule &m2);
void                SN2_Mechanism(Molecule &m1, Molecule &m2, Molecule &ms);

