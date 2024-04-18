#pragma once
#include <limits.h>

class Molecule;

struct ERROR
{
public:
    const static int INACCESSIBLE_ELEM = INT_MIN;
    const static int NO_DATA = INT_MIN + 1;
    const static Molecule MOLECULE_CREATE_ERR; // double dependency requires definition in ErrorHandler.cpp
};

