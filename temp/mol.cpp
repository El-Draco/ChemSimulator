#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

// Define a class for 3D vectors
class Vector3 {
public:
    float x, y, z;
    Vector3(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z) {}
};

// Define Atom class
class Atom {
public:
    Vector3 position;
    const int protons;
    const int neutrons;
    int electrons;

public:
    Atom(const Vector3& pos = Vector3(0, 0, 0), const int& p = -1, const int& n = -1, const int& e = -1)
        : position(pos), protons(p), neutrons(n), electrons(e) {
        if (electrons == -1)
            electrons = p;
    }
};

// Define Molecule class
class Molecule {
public:
    std::vector<Atom> atoms;
    size_t size; //num of atoms
    uint8_t **Adjacency;

    Molecule() {
        size = 0;
        Adjacency = nullptr;
    }

    Molecule(int size_in) : size(size_in) {
        Adjacency = new uint8_t *[size];
        for (int i = 0; i < size; ++i) {
            Adjacency[i] = new uint8_t[size];
        }
    }

    ~Molecule() {
        if (Adjacency != nullptr) {
            for (int i = 0; i < size; ++i) {
                delete[] Adjacency[i];
            }
            delete[] Adjacency;
        }
    }

    // Function to print adjacency matrix (for testing)
    void printAdj() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << static_cast<int>(Adjacency[i][j]) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Function to compute dipole moment (for testing)
    Vector3 computeDipole() {
        Vector3 dipole;
        for (const Atom& atom : atoms) {
            dipole.x += atom.position.x * atom.electrons;
            dipole.y += atom.position.y * atom.electrons;
            dipole.z += atom.position.z * atom.electrons;
        }
        return dipole;
    }

    // Function to break a bond (for testing)
    void breakBond(int i, int j) {
        Adjacency[i][j] = 0;
        Adjacency[j][i] = 0;
    }
};

// Function to parse the file and populate atoms and adjacency matrix
Molecule parseMolecule(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return Molecule();
    }

    // Molecule molecule;
    std::string line;

    // Read the number of atoms
    std::getline(file, line);
    int numAtoms = std::stoi(line);
    Molecule molecule = Molecule(numAtoms);

    // Read atom information
    for (int i = 0; i < numAtoms; ++i) {
        std::getline(file, line);
        std::istringstream iss(line);
        std::string symbol;
        int protons, neutrons, electrons;
        float x, y, z;

        // Parse atom information
        iss >> symbol >> protons >> neutrons >> electrons >> x >> y >> z;

        // Create Atom object and add it to the molecule
        molecule.atoms.emplace_back(Vector3(x, y, z), protons, neutrons, electrons);
    }

    // Read adjacency matrix
    for (int i = 0; i < numAtoms; ++i) {
        std::getline(file, line);
        std::istringstream iss(line);
        for (int j = 0; j < numAtoms; ++j) {
            int val;
            iss >> val;
            molecule.Adjacency[i][j] = val;
        }
    }

    return molecule;
}

int main() {
    Molecule molecule = parseMolecule("molecule.txt");

    // Testing functions
    molecule.printAdj();
    // Vector3 dipole = molecule.computeDipole();
    // std::cout << "Dipole Moment: (" << dipole.x << ", " << dipole.y << ", " << dipole.z << ")" << std::endl;
    // molecule.breakBond(0, 1);
    // molecule.printAdj();

    return 0;
}
