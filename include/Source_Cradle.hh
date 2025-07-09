#ifndef Source_Cradle_H
#define Source_Cradle_H 1

#include "G4Material.hh"
#include "Materials.hh"
#include "G4AssemblyVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4Polycone.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
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

class Source_Cradle
{
public:

  G4LogicalVolume *expHall_log;
  Materials* materials;
  
  Source_Cradle(G4LogicalVolume*, Materials*);
  ~Source_Cradle();

  void Construct();
  
  void setX(G4double x){Pos.setX(x);};
  void setY(G4double y){Pos.setY(y);};
  void setZ(G4double z){Pos.setZ(z);};

  void rotateX(G4double ax){Rot.rotateX(ax);};
  void rotateY(G4double ay){Rot.rotateY(ay);};
  void rotateZ(G4double az){Rot.rotateZ(az);};
  
  void PlaceCradle();

  private:

  G4AssemblyVolume* assembly;
  
  // Logical volume

  G4LogicalVolume* upper_leg_log;
  G4LogicalVolume* lower_leg_log;
  G4LogicalVolume* holder_log;
  G4LogicalVolume* base_log;
  
  // Materials
  G4Material* EpoxyResin;

  // position
  G4RotationMatrix Rot;
  G4ThreeVector Pos;

};

#endif

