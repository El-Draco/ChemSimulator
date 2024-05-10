# %% [markdown]
# #Implementation of Atom Class
# 

# %%
class Atom:
    def __init__(self, symbol, protons, electrons, neutrons, position, recently_broken=False):
      self.symbol = symbol
      self.protons = protons
      self.electrons = electrons
      self.neutrons = neutrons
      self.position = position
      self.recently_broken = recently_broken

    def electronegativity(self):
      e = {       
          1: 2.2,
          2: 2.2,
          3: 0.98,
          4: 1.57,
          5: 2.04,
          6: 2.55,
          7: 3.04,
          8: 3.44,
          9: 3.98,
          10: 3.98,
          11: 0.93,
          12: 1.31,
          13: 1.61,
          14: 1.90,
          15: 2.19,
          16: 2.58,
          17: 3.16,
          18: 3.16,
          19: 0.82,
          20: 1.00,
          21: 1.36,
          22: 1.54,
          23: 1.63,
          24: 1.66,
          25: 1.55,
          26: 1.83,
          27: 1.88,
          28: 1.91,
          29: 1.90,
          30: 1.65,
          31: 1.81,
          32: 2.01,
          33: 2.18,
          34: 2.55,
          35: 2.96,
          36: 3,
      }
      return e[self.protons]
    
    def __str__(self):
      return self.symbol

# %%
elements = {
        'H':{1,1,0},
        'He':{2,2,2},
        'Li':{3,3,4},
        'Be':{4,4,5},
        'B':{5,5,6},
        'C':{6,6,6},
        'N':{7,7,7},    
        'O':{8,8,8},
        'F':{9,9,10},
        'Ne':{10,10,10},
        'Na':{11,11,12},
        'Mg':{12,12,12},
        'Al':{13,13,14},
        'Si':{14,14,14},
        'P':{15,15,16},
        'S':{16,16,16},
        'Cl':{17,17,18},
        'Ar':{18,18,22},
        'K':{19,19,20},
        'Ca':{20,20,20},
        'Sc':{21,21,24},
        'Ti':{22,22,26},
        'V':{23,23,28},
        'Cr':{24,24,28},
        'Mn':{25,25,30},
        'Fe':{26,26,30},
        'Co':{27,27,32},
        'Ni':{28,28,31},
        'Cu':{29,29,35},
        'Zn':{30,30,35},
        'Ga':{31,31,39},
        'Ge':{32,32,41},
        'As':{33,33,42},
        'Se':{34,34,45},
        'Br':{35,35,45},
        'Kr':{36,36,48},
        'Rb':{37,37,48},
        'Sr':{38,38,50},
        'Y':{39,39,50},
        'Zr':{40,40,51},
        'Nb':{41,41,52},
        'Mo':{42,42,54},
        'Tc':{43,43,55},
        'Ru':{44,44,57},
        'Rh':{45,45,58},
        'Pd':{46,46,60},
        'Ag':{47,47,61},
        'Cd':{48,48,64},
        'In':{49,49,66},
        'Sn':{50,50,69},
        'Sb':{51,51,71},
        'Te':{52,52,76},
        'I':{53,53,74},
        'Xe':{54,54,77},
        'Cs':{55,55,78},
        'Ba':{56,56,81},
        'La':{57,57,82},
        'Ce':{58,58,82},
        'Pr':{59,59,82},
        'Nd':{60,60,84},
        'Pm':{61,61,84},
        'Sm':{62,62,88},
        'Eu':{63,63,89},
        'Gd':{64,64,93},
        'Tb':{65,65,94},
        'Dy':{66,66,97},
        'Ho':{67,67,98},
        'Er':{68,68,99},
        'Tm':{69,69,100},
        'Yb':{70,70,103},
        'Lu':{71,71,104},
        'Hf':{72,72,106},
        'Ta':{73,73,108},
        'W':{74,74,110},
        'Re':{75,75,111},
        'Os':{76,76,114},
        'Ir':{77,77,115},
        'Pt':{78,78,117},
        'Au':{79,79,118},
        'Hg':{80,80,121},
        'Tl':{81,81,123},
        'Pb':{82,82,125},
        'Bi':{83,83,126},
        'Po':{84,84,125},
        'At':{85,85,125},
        'Rn':{86,86,136},
        'Fr':{87,87,136},
        'Ra':{88,88,138},
        'Ac':{89,89,138},
        'Th':{90,90,142},
        'Pa':{91,91,148},
        'U':{92,92,146}
    }

# %% [markdown]
# # Implementation of Bond Class

# %%
class Bond:
    def __init__(self, atom_list, weight):
      self.atom_list = atom_list # fixed length = 2
      self.weight = weight
    
    def getWeight(self):
      return self.weight

    def __str__(self):
      return f"{self.atom_list[0]}-{self.atom_list[1]}"

# %% [markdown]
# # Implementation of Molecule Class

# %%
import collections
class Molecule:
    def __init__(self):
      self.bonds = []

    def construct_molecule(self, bondset):
      self.bonds = bondset

    def add_bond(self, bond):
      self.bonds.append(bond)

    def getBonds(self):
      return self.bonds
    
    def bondWeight(self, pair):
      for b in self.bonds:
        if pair[0] == b.atom_list[0] and pair[1] == b.atom_list[1]:
          return b.getWeight()

    def getAdjacentListStr(self, a=0):
      # returns adjacent list with symbols

      adj_list = collections.defaultdict(list)

      for bond in self.bonds:
        adj_list[bond.atom_list[0].symbol].append(bond.atom_list[1].symbol)
        adj_list[bond.atom_list[1].symbol].append(bond.atom_list[0].symbol)

      if a:
        return adj_list[a]
      else:
        return adj_list

    def getAdjacentList(self, a=0):
      # returns adjacency list representation of the molecule

      adj_list = collections.defaultdict(list)

      for bond in self.bonds:
        adj_list[bond.atom_list[0]].append(bond.atom_list[1])
        adj_list[bond.atom_list[1]].append(bond.atom_list[0])

      if a:
        return adj_list[a]
      else:
        return adj_list

    def getAtoms(self):
      # returns atoms list without repetition

      atoms = set()
      for bond in self.bonds:
        atoms.add(bond.atom_list[0])
        atoms.add(bond.atom_list[1])
      return list(atoms)

    def bondExists(self, atom1, atom2):
      for bond in self.bonds:
        if((bond.atom_list[0].symbol == atom1.symbol and bond.atom_list[1].symbol == atom2.symbol) or (bond.atom_list[0].symbol == atom2.symbol and bond.atom_list[1].symbol == atom1.symbol)):
          return True
      return False


# %% [markdown]
# # Testing Molecule

# %%
import collections
import math
import copy

C2H5F = Molecule()
C1 = Atom("C", 6, 6, 6, [0.0745, -0.5534, 0.0000])
C2 = Atom("C", 6, 6, 6, [-1.2043, 0.2502, 0.0000])
F = Atom("F", 9, 9, 9, [1.1298, 0.3032, 0.0000])
H1 = Atom("H", 1, 1, 1, [0.1472, -1.1828, -0.8910])
H2 = Atom("H", 1, 1, 1, [0.1471, -1.1828, 0.8910])
H3 = Atom("H", 1, 1, 1, [-2.0791, -0.4057, -0.0001])
H4 = Atom("H", 1, 1, 1, [-1.2472, 0.8979, 0.8810])
H5 = Atom("H", 1, 1, 1, [-1.2471, 0.8980, -0.8809])
bond1 = Bond([C1, H1], 1)
bond2 = Bond([C1, H2], 1)
bond3 = Bond([C1, H3], 1)
bond4 = Bond([C2, H4], 1)
bond5 = Bond([C2, H5], 1)
bond6 = Bond([C1, C2], 1)
bond7 = Bond([C2, F], 1)
C2H5F.add_bond(bond1)
C2H5F.add_bond(bond2)
C2H5F.add_bond(bond3)
C2H5F.add_bond(bond4)
C2H5F.add_bond(bond5)
C2H5F.add_bond(bond6)
C2H5F.add_bond(bond7)
adj_list = C2H5F.getAdjacentList()
adj_list


NaOH = Molecule()
Na = Atom("Na", 11, 11, 12, [3.4030, 0.2500, 1.0000])
O = Atom("O", 8, 8, 8, [2.5369, -0.2500, 1.0000])
H = Atom("H", 1, 1, 1, [2.0000, 0.0600, 1.0000])
bond1 = Bond([Na, O], 1)
bond2 = Bond([O, H], 1)
NaOH.add_bond(bond1)
NaOH.add_bond(bond2)
adj_list = NaOH.getAdjacentList()
adj_list

sizes = { 1: 1, 2: 1, 3: 2, 4: 2, 5: 2, 6: 2, 7: 2, 8: 2, 9: 2, 10: 2, 11: 3, 12: 3, 13: 3, 14: 3, 15: 3, 16: 3, 17: 3, 18: 3, 19: 4, 20: 4, 21: 4, 22: 4, 23: 4, 24: 4, 25: 4, 26: 4, 27: 4, 28: 4, 29: 4, 30: 4, 31: 4, 32: 4, 33: 4, 34: 4, 35: 4, 36: 4, }
def findLeavingGroup(molecule):
    adj_list = molecule.getAdjacentList()
    potential_leaving_atoms = []

    for atom in adj_list:
        if atom.symbol == "C" and len(adj_list[atom]) == 4:
            for adj_atom in adj_list[atom]:
                if adj_atom.symbol != "C":
                    potential_leaving_atoms.append(adj_atom)

    # STORE RESONANCE NUMBERS
    LGResNum = [0] * len(potential_leaving_atoms)
    max_resonance = 0
    for i in range(len(potential_leaving_atoms)):
        LGneighbors = adj_list[potential_leaving_atoms[i]]
        num = 0
        for j in range(len(LGneighbors)):
            # check if the bond between LGi and LGj is a double bond
            if molecule.bondWeight([potential_leaving_atoms[i], LGneighbors[j]]) == 2:
                num += 1
        LGResNum[i] = num
        max_resonance = max(max_resonance, num)

    # tuple of leaving group to resonance number
    potential_leaving_atoms = [
        (potential_leaving_atoms[i], LGResNum[i])
        for i in range(len(potential_leaving_atoms))
    ]

    # compare pairwise leavingroups and remove elements with less resonance
    newpotential_leaving_atoms = []
    for i in range(len(potential_leaving_atoms)):
        if potential_leaving_atoms[i][1] == max_resonance:
            newpotential_leaving_atoms.append(potential_leaving_atoms[i])

    potential_leaving_atoms = newpotential_leaving_atoms

    max_size = 0
    for i in range(len(potential_leaving_atoms)):
        max_size = max(max_size, sizes[potential_leaving_atoms[i][0].protons])

    new_potential_leaving_atoms = []
    for i in range(len(potential_leaving_atoms)):
        if sizes[potential_leaving_atoms[i][0].protons] == max_size:
            new_potential_leaving_atoms.append(potential_leaving_atoms[i])

    potential_leaving_atoms = new_potential_leaving_atoms

    for i in range(len(potential_leaving_atoms)):
        potential_leaving_atoms[i][0].recently_broken = True


    leaving_atom_carbons = []
    for i in range(len(potential_leaving_atoms)):
        neighbors = molecule.getAdjacentList(potential_leaving_atoms[i][0])
        for j in range(len(neighbors)):
            if neighbors[j].symbol == "C":
                leaving_atom_carbons.append(neighbors[j])
    
    for i in range(len(leaving_atom_carbons)):
        leaving_atom_carbons[i].recently_broken = True

    # REMOVE THOSE WITH LESS ELECTRONEGATIVITY
    def group(adj_list, atom, i):
        visited = set()
        queue = []
        queue.append(atom)
        visited.add(atom)

        adj_list[atom].remove(leaving_atom_carbons[i])

        while queue:
            s = queue.pop(0)
            for neighbour in adj_list[s]:
                if neighbour not in visited:
                    queue.append(neighbour)
                    visited.add(neighbour)
        return list(visited)

    potential_leaving_groups = [
        group(adj_list, potential_leaving_atoms[i][0], i)
        for i in range(len(potential_leaving_atoms))
    ]
    print("Leaving Groups:")
    print(
        [
            potential_leaving_groups[i][0].symbol
            for i in range(len(potential_leaving_groups))
        ]
    )

    def dipolevectormag(atomset):
        sum = 0
        for i in range(len(atomset)):
            vector = [
                atomset[i].position[0] - leaving_atom_carbons[i].position[0],
                atomset[i].position[1] - leaving_atom_carbons[i].position[1],
                atomset[i].position[2] - leaving_atom_carbons[i].position[2],
            ]
            sum += atomset[i].electronegativity() / (
                vector[0] ** 2 + vector[1] ** 2 + vector[2] ** 2
            )
        return sum

    max_vector_magnitude = 0
    for i in range(len(potential_leaving_groups)):
        max_vector_magnitude = max(
            max_vector_magnitude, dipolevectormag(potential_leaving_groups[i])
        )

    new_potential_leaving_groups = []
    for i in range(len(potential_leaving_groups)):
        if dipolevectormag(potential_leaving_groups[i]) == max_vector_magnitude:
            new_potential_leaving_groups.append(potential_leaving_groups[i])

    return [
        potential_leaving_groups[i][0] for i in range(len(potential_leaving_groups))
    ]


metals = {1, 3, 4, 11, 12, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}


def findNucleophile(molecule: Molecule):
    adj_list = molecule.getAdjacentList()
    potential_leaving_atoms = []

    for atom in adj_list:
        if atom.protons in metals:
            for adj_atom in adj_list[atom]:
                if molecule.bondWeight([atom, adj_atom]) == 1:
                    potential_leaving_atoms.append(adj_atom)

    # REMOVE THOSE WITH LESS SIZE
    min_size = math.inf
    for i in range(len(potential_leaving_atoms)):
        min_size = min(min_size, sizes[potential_leaving_atoms[i].protons])

    new_potential_leaving_atoms = []
    for i in range(len(potential_leaving_atoms)):
        if sizes[potential_leaving_atoms[i].protons] == min_size:
            new_potential_leaving_atoms.append(potential_leaving_atoms[i])

    potential_leaving_atoms = new_potential_leaving_atoms

    for i in range(len(potential_leaving_atoms)):
        potential_leaving_atoms[i].recently_broken = True

    leaving_atom_metals = []
    for i in range(len(potential_leaving_atoms)):
        neighbors = molecule.getAdjacentList(potential_leaving_atoms[i])
        for j in range(len(neighbors)):
            if neighbors[j].protons in metals:
                leaving_atom_metals.append(neighbors[j])
    
    for i in range(len(leaving_atom_metals)):
        leaving_atom_metals[i].recently_broken = True

    # REMOVE THOSE WITH LESS ELECTRONEGATIVITY
    def group(adj_list, atom, i):
        visited = set()
        queue = []
        queue.append(atom)
        visited.add(atom)

        adj_list[atom].remove(leaving_atom_metals[i])

        while queue:
            s = queue.pop(0)
            for neighbour in adj_list[s]:
                if neighbour not in visited:
                    queue.append(neighbour)
                    visited.add(neighbour)
        return list(visited)

    potential_nucleophiles = [
        group(adj_list, potential_leaving_atoms[i], i)
        for i in range(len(potential_leaving_atoms))
    ]

    return potential_nucleophiles
LeavingGroup = findLeavingGroup(C2H5F)
Nucleophile = findNucleophile(NaOH)[0]

newadjlist1 = C2H5F.getAdjacentList()
for atom in newadjlist1:
    for oldatom in LeavingGroup:
        if oldatom in newadjlist1[atom]:
            newadjlist1[atom].remove(oldatom)

for oldatom in LeavingGroup:
    newadjlist1.pop(oldatom)

newadjlist2 = NaOH.getAdjacentList()
for atom in newadjlist2:
    for oldatom in Nucleophile:
        if oldatom in newadjlist2[atom]:
            newadjlist2[atom].remove(oldatom)

for oldatom in Nucleophile:
    newadjlist2.pop(oldatom)
print("Atoms of intermediate 1:")
print([a.symbol for a in newadjlist1])
print("Atoms of intermediate 2:")
print([a.symbol for a in newadjlist2])

newbondset1 = []
for atom in newadjlist1:
    for adjatom in newadjlist1[atom]:
        for bond in C2H5F.getBonds():
            if atom in bond.atom_list and adjatom in bond.atom_list and bond not in newbondset1:
                newbondset1.append(bond)
for atom in Nucleophile:
    for adjatom in NaOH.getAdjacentList()[atom]:
        for bond in NaOH.getBonds():
            if atom in bond.atom_list and adjatom in bond.atom_list and adjatom not in newadjlist2 and bond not in newbondset1:
                newbondset1.append(bond)
for atom in Nucleophile:
    for newatom in newadjlist1:
        if atom.recently_broken and newatom.recently_broken:
            newbondset1.append(Bond([atom, newatom], 1))

newbondset2 = []
for atom in newadjlist2:
    for adjatom in newadjlist2[atom]:
        for bond in NaOH.getBonds():
            if atom in bond.atom_list and adjatom in bond.atom_list and bond not in newbondset2:
                newbondset2.append(bond)
for atom in LeavingGroup:
    for adjatom in C2H5F.getAdjacentList()[atom]:
        for bond in C2H5F.getBonds():
            if atom in bond.atom_list and adjatom in bond.atom_list and adjatom not in newadjlist1 and bond not in newbondset2:
                newbondset2.append(bond)
for atom in LeavingGroup:
    for newatom in newadjlist2:
        if atom.recently_broken and newatom.recently_broken:
            newbondset2.append(Bond([atom, newatom], 1))
print("Bonds of product 1:")
print([b.__str__() for b in newbondset1])
print("Bonds of product 2:")
print([b.__str__() for b in newbondset2])



Product1 = Molecule().construct_molecule(newbondset1)
Product2 = Molecule().construct_molecule(newbondset2)

# %%


# %%


# %%


# %%



