#ifndef CeBr3_2x2_Detector_H
#define CeBr3_2x2_Detector_H 1

#include "G4Material.hh"
#include "Materials.hh"
#include "G4Tubs.hh"
#include "G4Polycone.hh"
#include "G4AssemblyVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4PVDivision.hh"

#include "TrackerGammaSD.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SubtractionSolid.hh"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "Randomize.hh"
#include "globals.hh"
#include <iostream>
#include <iomanip>

using namespace std;

class CeBr3_2x2_Detector 
{
public:

  G4LogicalVolume *expHall_log;
  Materials* materials;
  
  CeBr3_2x2_Detector(G4LogicalVolume*, Materials*);
  ~CeBr3_2x2_Detector();

  void Construct();

  G4AssemblyVolume* GetAssembly(){return assembly;}
  
  void MakeSensitive(TrackerGammaSD*);

  private:

  // Logical volumes

  G4LogicalVolume* crystal_log;
  G4LogicalVolume* can_log;
  G4LogicalVolume* pmt_log;
  G4LogicalVolume* shield_log;
  G4LogicalVolume* window_log;

  // Materials
  G4Material* CeBr3;
  G4Material* Al;
  G4Material* MuMetal;
  G4Material* quartz;

  // dimensions
  G4double Length;
  G4double Radius;
  G4double canThickness;
  G4double canRadius;
  G4double canLength;
  G4double pmtLength;
  G4double pmtFrontRadius;
  G4double pmtBaseRadius;
  G4double pmtFrontLength;
  G4double pmtTransitionLength;
  G4double pmtBaseLength;
  G4double pmtThickness;
  G4double shieldThickness;
  G4double shieldLength;
  G4double windowRadius;
  G4double windowLength;
  G4double crystalRadius;
  G4double crystalLength;

  G4double startAngle;
  G4double spanningAngle;

  // position
  G4RotationMatrix DetRot;
  G4ThreeVector crystalPos;
  G4ThreeVector crystalShift;
  G4ThreeVector DetPos;
  G4ThreeVector pmtShift;
  G4ThreeVector pmtPos;
  G4ThreeVector canPos;
  G4ThreeVector windowShift;
  G4ThreeVector windowPos;
  G4double thetad;
  G4double phid;

  G4Polycone* can;
  G4Polycone* pmt;
  G4Polycone* shield;
  G4Tubs* window;
  G4Tubs* crystal;
  G4AssemblyVolume * assembly;

};

#endif

