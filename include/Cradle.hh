#ifndef Cradle_H
#define Cradle_H 1

#include "G4Material.hh"
#include "Materials.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4AssemblyVolume.hh"
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

  G4AssemblyVolume* GetAssembly(){return assembly;}
  
  void setX(G4double x){assemblyPos.setX(x);};
  void setY(G4double y){assemblyPos.setY(y);};
  void setZ(G4double z){assemblyPos.setZ(z);};
  void rotateX(G4double ax){assemblyRot.rotateX(ax);};
  void rotateY(G4double ay){assemblyRot.rotateY(ay);};
  void rotateZ(G4double az){assemblyRot.rotateZ(az);};
  void setOffset(G4double o){Offset = o;};
  G4double getOffset(){return Offset;};
  G4bool isConstructed(){return constructed;};
  
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
  G4ThreeVector Pos;
  G4RotationMatrix Rot;
  G4ThreeVector cradleShift;
  G4double Offset;
  G4ThreeVector assemblyPos;
  G4RotationMatrix assemblyRot;
  
  G4SubtractionSolid* fCradle;

  G4AssemblyVolume* assembly;

  G4bool constructed;
};

#endif

