#include "Atom.h"
#include "ElectroNegativityTable.h"
#include "Molecule.h"
#include "ErrorHandler.h"
#include "Bond.h"
#include <list>
#include <fstream>

template <class VectorType = Vector3>
std::ofstream& printV(std::ofstream& outputfile, const VectorType& vectordata) {
    if (!outputfile) { std::cerr << "error while outputting to file\n"; }
    static int num_calls = 0;
    num_calls++;
    if (std::is_same<VectorType, Vector3>::value){
        outputfile << vectordata.x << ", " << vectordata.y << ", " << vectordata.z << '\n';
    }
    return outputfile;
}

std::ofstream& printM(std::ofstream& outputfile, Molecule& m) {
    if (!outputfile) { std::cerr << "error while outputting to file\n"; }
    static int num_calls = 0;
    num_calls++;
    for (int i = 0; i < m.size; ++i) {
        for (int k = 0; k < i; ++k) {
            outputfile << "  ";
        }
        for (int j = i; j < m.size; ++j) {
            outputfile << static_cast<int>(m.Adjacency[i][j]) << ' ';
        }
        outputfile << '\n';
    }
    outputfile << "END" << '\n';
    return outputfile;
}

int main()
{
    Atom Atoms[5] = {
        Atom(Vector3(0, 0, 0), 6, 6, 6),
        Atom(Vector3(0, 0, 1), 1, 0, 1),
        Atom(Vector3(0, 0, 1).rodrigues_rotate(Vector3(1,1,0), 109.47*PI/180), 1, 0, 1),
        Atom(Vector3(0, 0, 1).rodrigues_rotate(Vector3(1,1,0), 109.47*PI/180).rodrigues_rotate(Vector3(0,0,1), 120*PI/180), 1, 0, 1),
        Atom(Vector3(0, 0, 1).rodrigues_rotate(Vector3(1,1,0), 109.47*PI/180).rodrigues_rotate(Vector3(0,0,1), -120*PI/180), 1, 0, 1)
    };

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            std::cout << Atoms[i].position.angle(Atoms[j].position) << '\n';
        }
    }

    const uint16_t AtomSet_cardinality = sizeof(Atoms)/sizeof(*Atoms);

    std::vector<std::vector<Atom>> B = std::vector<std::vector<Atom>>
            {
                {Atoms[1], Atoms[2], Atoms[3], Atoms[4]},
                {Atoms[0]},
                {Atoms[0]},
                {Atoms[0]},
                {Atoms[0]}
            };

    Molecule methane = Molecule::Create<5>(Atoms, B);

    Molecule::printAdj(methane);

    Atom BrAtoms[5] = {
        Atom(Vector3(0, 0, 0), 6, 6, 6),
        Atom(Vector3(0, 0, 1), 1, 0, 1),
        Atom(Vector3(0, 0, 1).rodrigues_rotate(Vector3(1,1,0), 109.47*PI/180), 1, 0, 1),
        Atom(Vector3(0, 0, 1).rodrigues_rotate(Vector3(1,1,0), 109.47*PI/180).rodrigues_rotate(Vector3(0,0,1), 120*PI/180), 1, 0, 1),
        Atom(Vector3(0, 0, 1).rodrigues_rotate(Vector3(1,1,0), 109.47*PI/180).rodrigues_rotate(Vector3(0,0,1), -120*PI/180), 35, 44.904, 35)
    };

    std::vector<std::vector<Atom>> C = std::vector<std::vector<Atom>>(
            {
                {BrAtoms[1], BrAtoms[2], BrAtoms[3], BrAtoms[4]},
                {BrAtoms[0]},
                {BrAtoms[0]},
                {BrAtoms[0]},
                {BrAtoms[0]}
            });

    Molecule CH3Br = Molecule::Create<5>(BrAtoms, C);

    Molecule::printAdj(CH3Br);

    
    Atom nAtoms[12] = {
        Atom(Vector3(0,0,1), 6, 6, 6),                                                     // a0
        Atom(Vector3(0,0,1).rodrigues_rotate(Vector3(0,1,0),   60*PI/180), 6,6,6),         // a1
        Atom(Vector3(0,0,1).rodrigues_rotate(Vector3(0,1,0), 2*60*PI/180), 6,6,6),         // a2
        Atom(Vector3(0,0,1).rodrigues_rotate(Vector3(0,1,0), 3*60*PI/180), 6,6,6),         // a3
        Atom(Vector3(0,0,1).rodrigues_rotate(Vector3(0,1,0), 4*60*PI/180), 6,6,6),         // a4
        Atom(Vector3(0,0,1).rodrigues_rotate(Vector3(0,1,0), 5*60*PI/180), 6,6,6),         // a5

        Atom(Vector3(0,0,1).scale(1.5), 1, 0, 1),                                            // a6
        Atom(Vector3(0,0,1).rodrigues_rotate(Vector3(0,1,0),   60*PI/180).scale(1.5), 1,0,1),// a7
        Atom(Vector3(0,0,1).rodrigues_rotate(Vector3(0,1,0), 2*60*PI/180).scale(1.5), 1,0,1),// a8
        Atom(Vector3(0,0,1).rodrigues_rotate(Vector3(0,1,0), 3*60*PI/180).scale(1.5), 1,0,1),// a9
        Atom(Vector3(0,0,1).rodrigues_rotate(Vector3(0,1,0), 4*60*PI/180).scale(1.5), 1,0,1),// a10
        Atom(Vector3(0,0,1).rodrigues_rotate(Vector3(0,1,0), 5*60*PI/180).scale(1.5), 1,0,1),// a11
    };


    std::vector<std::vector<Atom>> D = 
    {
        {nAtoms[5], nAtoms[5], nAtoms[1], nAtoms[6]},
        {nAtoms[0], nAtoms[2], nAtoms[2], nAtoms[7]},
        {nAtoms[1], nAtoms[1], nAtoms[3], nAtoms[8]},
        {nAtoms[2], nAtoms[4], nAtoms[4], nAtoms[9]},
        {nAtoms[3], nAtoms[3], nAtoms[5], nAtoms[10]},
        {nAtoms[4], nAtoms[0], nAtoms[0], nAtoms[11]},

        {nAtoms[0]},
        {nAtoms[1]},
        {nAtoms[2]},
        {nAtoms[3]},
        {nAtoms[4]},
        {nAtoms[5]},
    };

    Molecule benzene = Molecule::Create<12>(nAtoms, D);

    Molecule::printAdj(methane);
    Molecule::printAdj(benzene);

    std::ofstream file = std::ofstream("positions.txt");

    Molecule pmol = CH3Br;
    for (int i = 0; i < pmol.size; ++i) {
        printV(file, pmol.AtomSet[i].position);
        //std::cout<<pmol.AtomSet[i].position;
    }
    
    std::cout<<Molecule::computeDipole(methane);
    std::cout<<Molecule::computeDipole(benzene);
    std::cout<<Molecule::computeDipole(CH3Br);
    std::cout << Molecule::computeDipole(CH3Br).magnitude() << '\n';

    //std::cout << Atom::desiredValence(Atom(Vector3(0,0,0),1,0,1)) << '\n';
    for (int i = 1; i < 119; ++i) {
        std::cout << i << ':' << Atom::desiredValence(Atom(Vector3(0,0,0),1,0,i)) << '\n'; // TODO: FIX VALENCY CALCULATION
    }

    std::cout << Atom::desiredValence(Atom(Vector3(0,0,0),1,0,8)) << '\n';
    std::cout << Atom(Vector3(0,0,0),1,0,8).valency() << '\n';

    std::cout << "delta EN: " << ElectroNegativity::ID(Atom(Vector3(0,0,0),6,6,6)) << ' ' << ElectroNegativity::ID(Atom(Vector3(0,0,0),7,7,7)) << '\n';

    std::cout << Bond::isPureCovalent(Atom(Vector3(0,0,0),1,0,8), Atom(Vector3(0,0,0),1,0,6)) << '\n';

    file.close();

    file = std::ofstream("./conf/bonds.txt");

    printM(file, pmol);

    file.close();
};
