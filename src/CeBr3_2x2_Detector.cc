#include "CeBr3_2x2_Detector.hh"

CeBr3_2x2_Detector::CeBr3_2x2_Detector(G4LogicalVolume* experimentalHall_log,
				       Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;

  CeBr3 = materials->FindMaterial("CeBr3");
  Al = materials->FindMaterial("Al");
  MuMetal = materials->FindMaterial("MuMetal");
  //pmtMat = materials->FindMaterial("pmtMat");
  quartz = materials->FindMaterial("quartz");
  TeflonTape = materials->FindMaterial("TeflonTape");
  
  crystalLength = 51*mm;      // 2 inches
  crystalRadius = 51/2.0*mm;  // 1 inch

  startAngle      = 45.*deg;
  spanningAngle   = 360.*deg;

  canLength    = 40.0*mm;
  canThickness = 0.5*mm;
  canRadius    = 54.0/2*mm;

  reflectorSideThickness  = 1.0*mm;
  reflectorFrontThickness = 1.0*mm;
  
  // This is the position of the center of the front face of the can.
  DetPos.setX(0);
  DetPos.setY(0);
  DetPos.setZ(0);

  crystalShift.setX(0);
  crystalShift.setY(0);
  crystalShift.setZ(crystalLength/2 + canThickness + reflectorFrontThickness);
  crystalPos = DetPos + crystalShift;

  reflectorShift.setX(0);
  reflectorShift.setY(0);
  reflectorShift.setZ(canThickness);
  reflectorPos = DetPos + reflectorShift;

  canPos = DetPos;
  
  shieldThickness  = 0.64*mm;
  shieldLength     = 120*mm;           // Measured by hand on drawing

  pmtOffset    = 40.0*mm;              // PMT housing, actually
  pmtLength    = 197.0*mm - pmtOffset; // PMT housing, actually
  pmtThickness = 1.0*mm;
  pmtRadius    = 58.8/2*mm;

  windowRadius   = crystalRadius;
  windowLength   = 12.5*mm;            // Not verified

  windowShift.setX(0);
  windowShift.setY(0);
  windowShift.setZ(1); 
  windowShift.setMag(crystalLength + windowLength/2
		     + canThickness + reflectorFrontThickness);
  windowPos = DetPos + windowShift;

  // The G4Polycone position is the center of the z=0 plane, not
  // the center of the solid.
  pmtShift.setX(0);
  pmtShift.setY(0);
  pmtShift.setZ(1); 
  pmtShift.setMag(pmtOffset); 
  pmtPos = DetPos + pmtShift;

  shieldShift.setX(0);
  shieldShift.setY(0);
  shieldShift.setZ(1); 
  shieldShift.setMag(shieldLength/2.0 + pmtOffset); 
  shieldPos = DetPos + shieldShift;

  thetad = 90.*deg;
  phid = 90.*deg;

  DetRot=G4RotationMatrix::IDENTITY;
  DetRot.rotateX(180.*deg);
  DetRot.rotateY(90.*deg+thetad);
  DetRot.rotateZ(phid);

  assembly    = new G4AssemblyVolume();

}

CeBr3_2x2_Detector::~CeBr3_2x2_Detector()
{
}

void CeBr3_2x2_Detector::Construct()
{

  // Can

  const G4double czPlane[4] =
    {0,
     canThickness,
     canThickness,
     canLength};
  const G4double crInner[4] = 
    {0,
     0,
     canRadius-canThickness,
     canRadius-canThickness};
  const G4double crOuter[4] =
    {canRadius,
     canRadius,
     canRadius,
     canRadius};
  can = new G4Polycone("Can", startAngle, spanningAngle, 4,
		       czPlane, crInner, crOuter);

  can_log = new G4LogicalVolume(can, Al, "can_log", 0, 0, 0);

  // Reflector
  
  const G4double rzPlane[4] =
    {0,
     reflectorFrontThickness,
     reflectorFrontThickness,
     crystalLength+reflectorFrontThickness};
  const G4double rrInner[4] = 
    {0,
     0,
     crystalRadius,
     crystalRadius};
  const G4double rrOuter[4] =
    {crystalRadius+reflectorSideThickness,
     crystalRadius+reflectorSideThickness,
     crystalRadius+reflectorSideThickness,
     crystalRadius+reflectorSideThickness};
  reflector = new G4Polycone("Reflector", startAngle, spanningAngle, 4,
			     rzPlane, rrInner, rrOuter);

  reflector_log = new G4LogicalVolume(reflector, TeflonTape, "reflector_log",
				      0, 0, 0);

  // PMT (housing)
  
  const G4double pzPlane[4] =
    {0,
     pmtLength - pmtThickness,
     pmtLength - pmtThickness,
     pmtLength};
  const G4double prInner[4] = 
    {pmtRadius - pmtThickness,
     pmtRadius - pmtThickness,
     0,
     0};
  const G4double prOuter[4] =
    {pmtRadius,
     pmtRadius,
     pmtRadius,
     pmtRadius};
  pmt = new G4Polycone("PMT", startAngle, spanningAngle, 4,
		       pzPlane, prInner, prOuter);

  pmt_log = new G4LogicalVolume(pmt, MuMetal, "pmt_log", 0, 0, 0);

  // magnetic shield

  shield = new G4Tubs("shield", canRadius, canRadius + shieldThickness,
		      shieldLength/2., startAngle, spanningAngle);
  
  shield_log = new G4LogicalVolume(shield, MuMetal, "pmt_log", 0, 0, 0);

  // window

  window = new G4Tubs("Window", 0, windowRadius, windowLength/2,
		      startAngle, spanningAngle);

  window_log = new G4LogicalVolume(window, quartz, "window_log",
				   0, 0, 0);
  
  // crystal

  crystal = new G4Tubs("crystal", 0, crystalRadius, crystalLength/2,
		       startAngle, spanningAngle);

  crystal_log = new G4LogicalVolume(crystal, CeBr3, "crystal_log",
				    0, 0, 0);

  assembly->AddPlacedVolume(crystal_log, crystalPos, &DetRot);

  assembly->AddPlacedVolume(can_log, canPos, &DetRot);

  assembly->AddPlacedVolume(reflector_log, reflectorPos, &DetRot);

  assembly->AddPlacedVolume(pmt_log, pmtPos, &DetRot);

  assembly->AddPlacedVolume(shield_log, shieldPos, &DetRot);

  assembly->AddPlacedVolume(window_log, windowPos, &DetRot);

  //Visualization Attributes

  //   CeBr3 Crystal
  G4Colour dgreen (0.0,0.75, 0.0, 1.0); 
  G4VisAttributes* Vis_1 = new G4VisAttributes(dgreen);
  Vis_1->SetVisibility(true);
  Vis_1->SetForceSolid(true);

  //   Can and Reflector
  G4Colour transGrey (0.5, 0.5, 0.5, 0.3);
  G4VisAttributes* Vis_2 = new G4VisAttributes(transGrey);
  Vis_2->SetVisibility(true);
  Vis_2->SetForceSolid(true);

  //   Dead material
  G4Colour dGrey (0.8, 0.8, 0.8, 1.0);
  G4VisAttributes* Vis_3 = new G4VisAttributes(dGrey);
  Vis_3->SetVisibility(true);
  Vis_3->SetForceSolid(true);

  crystal_log->SetVisAttributes(Vis_1);

  can_log->SetVisAttributes(Vis_2);

  reflector_log->SetVisAttributes(Vis_2);

  pmt_log->SetVisAttributes(Vis_3);

  shield_log->SetVisAttributes(Vis_3);

  window_log->SetVisAttributes(Vis_3);
 
}
//---------------------------------------------------------------------
void CeBr3_2x2_Detector::MakeSensitive(TrackerGammaSD* TrackerGamma)
{
  crystal_log->SetSensitiveDetector(TrackerGamma);
}
//---------------------------------------------------------------------
