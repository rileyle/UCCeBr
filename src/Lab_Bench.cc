#include "Lab_Bench.hh"

Lab_Bench::Lab_Bench(G4LogicalVolume* experimentalHall_log,
		     Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;

  density = 2.5;

  // Lab bench at Ursinus College, Pfahler Hall 013
  Length = 121.5*cm;
  Width  = 200*cm;
  Depth  = 2.54*cm;

  // Cradles place the crystal axis 2.125" above bench surface
  Pos.setX(0);
  Pos.setY(-54*mm - Depth/2); 
  Pos.setZ(0);

  Rot = G4RotationMatrix::IDENTITY;
}


Lab_Bench::~Lab_Bench()
{
}

void Lab_Bench::Construct()
{

  bench = new G4Box("Bench", Width/2.0, Depth/2.0, Length/2.0);

  // We create the material here so that the user can set the density
  // before calling Construct().
  G4cout << "Density = " << density << ", " << density*mg/cm3 << G4endl;
  material = new G4Material("LabBenchMaterial",
			    density*g/cm3,
			    4);
  material->AddElement(G4Element::GetElement("Carbon"),   21);
  material->AddElement(G4Element::GetElement("Hydrogen"), 25);
  material->AddElement(G4Element::GetElement("Chlorine"),  1);
  material->AddElement(G4Element::GetElement("Oxygen"),    5);
  
  bench_log = new G4LogicalVolume(bench, material,
				  "bench_log", 0, 0, 0);

  PlaceBench();

  G4Colour dGrey (0.8, 0.8, 0.8, 1.0);
  G4VisAttributes* Vis = new G4VisAttributes(dGrey);
  Vis->SetVisibility(true);
  Vis->SetForceSolid(true);

  bench_log->SetVisAttributes(Vis);
 
  return;
}
//---------------------------------------------------------------------
void Lab_Bench::PlaceBench()
{
  // Use the current Pos and Rot to place the bench.
  new G4PVPlacement(G4Transform3D(Rot,Pos),
		    bench_log, "Bench", expHall_log, false, 0); 
}

