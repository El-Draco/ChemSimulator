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
std::vector<Molecule> parse(std::string filename);

void saveProduct();