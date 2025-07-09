#include "Source_Cradle.hh"

Source_Cradle::Source_Cradle(G4LogicalVolume* experimentalHall_log,
			     Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;

  EpoxyResin = materials->FindMaterial("EpoxyResin");

  Pos.setX(0);
  Pos.setY(0);
  Pos.setZ(0);

  Rot = G4RotationMatrix::IDENTITY;
  
}

Source_Cradle::~Source_Cradle()
{
}

void Source_Cradle::Construct()
{

  assembly = new G4AssemblyVolume();

  // Legs (box atop a trapezoid)

  G4Box* upper_leg = new G4Box("UpperLeg",
			       4./2*mm,   // x half-width (left/right)
			       25./2*mm,  // y half-width (up/down)
			       15./2*mm); // z half-width (toward detector)

  upper_leg_log = new G4LogicalVolume(upper_leg, EpoxyResin,
				      "UpperLeg_log", 0, 0, 0);
  
  G4RotationMatrix noRot = G4RotationMatrix::IDENTITY;
  
  G4ThreeVector upperPos;
  upperPos.setX(+34./2*mm - 4./2*mm);
  upperPos.setY(-54.*mm + 25.*mm + 25./2*mm);
  upperPos.setZ(0);

  assembly->AddPlacedVolume(upper_leg_log, upperPos, &noRot);
  
  upperPos.setX(-34./2*mm + 4./2*mm);

  assembly->AddPlacedVolume(upper_leg_log, upperPos, &noRot);
  
  // Starts oriented along z (needs a -90 deg rotation about x).
  G4Trd* lower_leg = new G4Trd("LowerLeg",
			       4./2*mm, 4./2*mm,   // x half-widths
			       39./2*mm, 15./2*mm, // y half-widths
			       25./2*mm);         // z half-height

  lower_leg_log = new G4LogicalVolume(lower_leg, EpoxyResin,
				      "LowerLeg_log", 0, 0, 0);

  G4RotationMatrix lowerRot = G4RotationMatrix::IDENTITY;
  lowerRot.rotateX(-90*deg);

  G4ThreeVector lowerPos;
  lowerPos.setX(34./2*mm - 4./2*mm);
  lowerPos.setY(-54.*mm + 25./2*mm);
  lowerPos.setZ(0);

  assembly->AddPlacedVolume(lower_leg_log, lowerPos, &lowerRot);

  lowerPos.setX(-34./2*mm + 4./2*mm);

  assembly->AddPlacedVolume(lower_leg_log, lowerPos, &lowerRot);

  // Base
  
  G4Trd* base = new G4Trd("Base",
			  26./2*mm, 26./2*mm,   // x half-widths
			  39./2*mm, 35.2/2*mm, // y half-widths
			  4./2*mm);             // z half-height

  base_log = new G4LogicalVolume(base, EpoxyResin,
				 "Base_log", 0, 0, 0);
  
  G4ThreeVector basePos;
  basePos.setX(0);
  basePos.setY(-54.*mm + 4./2*mm);
  basePos.setZ(0);

  assembly->AddPlacedVolume(base_log, basePos, &lowerRot);

  // Holder
  G4Tubs* ring = new G4Tubs("holder_ring", 23.4/2*mm, 33.4/2*mm, 15.0/2*mm,
			    45.0*deg, 360.0*deg);

  G4Tubs* cutout = new G4Tubs("holder_cutout", 0, 25.4/2*mm, 8.0/2*mm,
			      45.0*deg, 360.0*deg);

  G4SubtractionSolid* holder_cyl = new G4SubtractionSolid("HolderCyl",
							  ring, cutout);
  
  G4Box* holder_box = new G4Box("HolderBox", 26.0/2*mm, 26.0/2*mm, 26.0/2*mm);

  G4ThreeVector boxShift;
  boxShift.setX(0);
  boxShift.setY(-26.0/2*mm - 4.0*mm);
  boxShift.setZ(0);
  
  G4IntersectionSolid* holder
    = new G4IntersectionSolid("Holder", holder_cyl, holder_box,
  			      G4Transform3D(noRot, boxShift));

  G4ThreeVector holderPos;
  holderPos.setX(0);
  holderPos.setY(0);
  holderPos.setZ(0);

  holder_log = new G4LogicalVolume(holder, EpoxyResin,
				   "Holder_log", 0, 0, 0);
  
  assembly->AddPlacedVolume(holder_log, holderPos, &noRot);
  
  PlaceCradle();

  G4Colour dGrey (0.8, 0.8, 0.8, 1.0);
  G4VisAttributes* Vis = new G4VisAttributes(dGrey);
  Vis->SetVisibility(true);
  Vis->SetForceSolid(true);

  upper_leg_log->SetVisAttributes(Vis);
  lower_leg_log->SetVisAttributes(Vis);
  holder_log->SetVisAttributes(Vis);
  base_log->SetVisAttributes(Vis);
    
  return;
}
//---------------------------------------------------------------------
void Source_Cradle::PlaceCradle()
{

    assembly->MakeImprint(expHall_log, Pos, &Rot, 100000);

}
//---------------------------------------------------------------------
