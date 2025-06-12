#ifndef Cradle_H
#define Cradle_H 1

#include "G4Material.hh"
#include "Materials.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
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

class Cradle
{
public:

  G4LogicalVolume *expHall_log;
  Materials* materials;
  
  Cradle(G4LogicalVolume*, Materials*);
  ~Cradle();

  void Construct();

  void setX(G4double x){Pos.setX(x);};
  void setY(G4double y){Pos.setY(y - Depth/2);};
  void setZ(G4double z){Pos.setZ(z + Length/2);};

  void PlaceCradle();

  private:

  // Logical volume

  G4LogicalVolume* fCradle_log;

  // Materials
  G4Material* EpoxyResin;
  
  // dimensions
  G4double Length;
  G4double Width;
  G4double Depth;
  G4double Radius;

  // position
  G4RotationMatrix Rot;
  G4ThreeVector Pos;
  G4ThreeVector cradleShift;
  G4ThreeVector Offset;

  G4SubtractionSolid* fCradle;
};

#endif

