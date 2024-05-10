#pragma once

#include "Atom.h"
#include "ErrorHandler.h"
#include "ElectroNegativityTable.h"
#include <iostream>
#include <vector>
#include "Bond.h"

typedef Molecule SubMolecule;

class Molecule
{
public:
    std::vector <Atom> atoms;
    size_t size;
    // std::vector<std::vector<int>> Adjacency;
    std::vector<Bond> bonds;
    Atom root;
    Molecule (std::vector<Bond> &bonds) {

    }
    Molecule() {

    }
    Molecule(int size_in);

    template <std::size_t cardinality>
    static Molecule Create(Atom *Atoms_input, std::vector<std::vector<Atom>> Bonds)
    {
        Molecule new_molecule(Bonds.size());
        new_molecule.atoms = Atoms_input;
        new_molecule.size = Bonds.size();

        if (cardinality != Bonds.size())
        {
            std::cout << "Atom set and Bond initializer list size mismatch <" << cardinality << "> " << Bonds.size() << '\n';
            return ERROR::MOLECULE_CREATE_ERR;
        }
        // TODO: FIX THIS BAD HACK
        for (size_t i = 0; i < Bonds.size(); i++)
        {
            for (size_t j = 0; j < Bonds[i].size(); j++)
            {
                for (size_t k = 0; k < new_molecule.size; k++)
                {
                    if (*((Bonds.begin() + i)->begin() + j) == Atoms_input[k])
                        new_molecule.Adjacency[i][k] += 1;
                }
            }
        }
        return new_molecule;
    }
    ~Molecule();
    void static printAdj(Molecule &m);
    Vector3 static computeDipole(Molecule &m);
    void breakBond(SubMolecule &m);


    Molecule (const Molecule &rhs) {
        *this = rhs;
    }
    Molecule &operator=(const Molecule &rhs) {
        return (*this);
    }
    Molecule &operator+(Molecule &m) {
        this->root = this->root + m.root;
        return (*this);
    }
    
    Molecule &operator-(Molecule &m) {
        this->root = this->root - m.root;
        return (*this);
    }

};
