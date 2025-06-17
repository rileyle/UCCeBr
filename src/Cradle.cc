#include "Cradle.hh"

Cradle::Cradle(G4LogicalVolume* experimentalHall_log,
		     Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;

  EpoxyResin = materials->FindMaterial("EpoxyResin");

  // Detector cradle designed and printed by Brock Dyer (UC'25)
  Length =  40*mm;    // along z
  Width  = 110*mm;
  Depth  =  54*mm;    // height
  Radius = 83.2/2*mm;

  cradleShift.setX(0);
  cradleShift.setY(Depth/2);
  cradleShift.setZ(0);
    
  Pos.setX(0);
  Pos.setY(-Depth/2);
  Pos.setZ(Length/2);

  Offset = 104*mm; // 3x4 can length
  
  Rot = G4RotationMatrix::IDENTITY;

  assemblyRot = Rot;
  assemblyPos.setX(0);
  assemblyPos.setY(0);
  assemblyPos.setZ(0);
    
  assembly    = new G4AssemblyVolume();

  constructed = false;
}


Cradle::~Cradle()
{
}

void Cradle::Construct()
{

  G4Box* box = new G4Box("box", Width/2.0, Depth/2.0, Length/2.0);
  G4Tubs* cylinder = new G4Tubs("cylinder", 0, Radius, 2*Length, 0, 360*deg);

  fCradle = new G4SubtractionSolid("fCradle", box, cylinder,
				       G4Transform3D(Rot, cradleShift));
  
  fCradle_log = new G4LogicalVolume(fCradle, EpoxyResin,
				    "fCradle_log", 0, 0, 0);

  assembly->AddPlacedVolume(fCradle_log, Pos, &Rot);

  G4ThreeVector Pos2;
  Pos2.setX(Pos.getX());
  Pos2.setY(Pos.getY());
  Pos2.setZ(Pos.getZ() + Offset);
  
  assembly->AddPlacedVolume(fCradle_log, Pos2, &Rot);

  G4Colour dGrey (0.8, 0.8, 0.8, 1.0);
  G4VisAttributes* Vis = new G4VisAttributes(dGrey);
  Vis->SetVisibility(true);
  Vis->SetForceSolid(true);

  fCradle_log->SetVisAttributes(Vis);

  constructed = true;
  
  return;
}
//---------------------------------------------------------------------
void Cradle::PlaceCradle()
{
  assembly->MakeImprint(expHall_log,
			assemblyPos, &assemblyRot,
			10000);
  // Use the current Pos, Offset, and Rot to place the cradle.
  //  new G4PVPlacement(G4Transform3D(Rot, Pos),
  //		    fCradle_log, "frontCradle", expHall_log, false, 0); 
  //  new G4PVPlacement(G4Transform3D(Rot, Pos+Offset),
  //		    fCradle_log, "backCradle", expHall_log, false, 0); 
}
//---------------------------------------------------------------------
