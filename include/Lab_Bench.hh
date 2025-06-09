#ifndef Lab_Bench_H
#define Lab_Bench_H 1

#include "G4Material.hh"
#include "Materials.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "Randomize.hh"
#include "globals.hh"
#include <iostream>
#include <iomanip>

using namespace std;

class Lab_Bench
{
public:

  G4LogicalVolume *expHall_log;
  Materials* materials;
  
  Lab_Bench(G4LogicalVolume*, Materials*);
  ~Lab_Bench();

  void Construct();

  void setX(G4double);
  void setY(G4double);
  void setZ(G4double);

  void PlaceBench();

  private:

  // Logical volume

  G4LogicalVolume* bench_log;

  // Materials
  G4Material* EpoxyResin;

  // dimensions
  G4double Length;
  G4double Width;
  G4double Depth;

  // position
  G4RotationMatrix Rot;
  G4ThreeVector Pos;

  G4Box* bench;
};

#endif

