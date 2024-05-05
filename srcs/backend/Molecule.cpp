#include "Molecule.h"

const Molecule ERROR::MOLECULE_CREATE_ERR = Molecule();

Molecule::Molecule(int size_in=0)
{
    this->size = size_in;
    Adjacency = new uint8_t *[size];
    for (uint16_t i = 0; i < size; i++)
        Adjacency[i] = new uint8_t[size];
}

void Molecule::printAdj(Molecule &m)
{
    for (int i = 0; i < m.size; ++i)
    {
        for (int j = 0; j < m.size; ++j)
            std::cout << static_cast<int>(m.Adjacency[i][j]) << ' ';
        std::cout << '\n';
    }
    std::cout << '\n';
}

Vector3 Molecule::computeDipole(Molecule &m)
{
    Vector3 e = Vector3(0, 0, 0);
    for (int i = 0; i < m.size; ++i)
    {
        for (int j = i + 1; j < m.size; ++j)
            e += (m.atoms[i].position - m.atoms[j].position).unitvector() * (ElectroNegativity::ID(m.atoms[i]) - ElectroNegativity::ID(m.atoms[j]));
    }
    return e;
}

Molecule::~Molecule()
{
    const uint16_t atoms_cardinality = atoms.size();
    if (atoms_cardinality > 0)
    {
        for (uint16_t i = 0; i < atoms_cardinality; i++)
        {
            if (Adjacency[i] != nullptr)
                delete[] Adjacency[i];
        }
        if (Adjacency != nullptr)
            delete[] Adjacency;
    }
}
