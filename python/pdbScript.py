#!/bin/bash
# Parse out a pdb file after grep or can be used directly on pdb files if you specify an if
# statement for ATOM
import sys

# class to store in atom values
class atomExtract(object):
    def __init__(self,atomId,name,resName,chain,resID,x,y,z):
        self.atom_id = atomId
        self.atom_name = name
        self.res_name = resName
        self.chain_name = chain
        self.residue_seq = resID
        self.x = x
        self.y = y
        self.z = z
    
def main():
    pdbFile = open(sys.argv[1], 'rw')
    atomCoords = [] 

    for line in pdbFile:
        atom_id = line[6:11].strip()
        atom_name = line[12:16].strip()
        res_name = line[17:20].strip()
        chain_name = line[21:22].strip()
        residue_seq = line[22:26].strip()
        x = line[30:38].strip()
        y = line[38:46].strip()
        z = line[46:54].strip()
        atomLine = atomExtract(atom_id, atom_name, res_name, chain_name, residue_seq, x,y,z)
        atomCoords.append(atomLine)

# test for each object values
# will have to store each item in a comparsion array for distance calculation
    for item in atomCoords:
        # d = float(item.x)+ float(item.y) + float(item.z)
       # print d
       print item.residue_seq




if __name__ == '__main__':
  main()

