#include "Lab_Bench.hh"

Lab_Bench::Lab_Bench(G4LogicalVolume* experimentalHall_log,
		     Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;

  density = 2.6;

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
  //
  // The material is likely an epoxy resin
  // (C21 H25 Cl O5, density 0.9 - 2.6 g/cm3)
  // with some kind of silica (Si O2) mixed in.
  // (density 1.4 - 2.8 mg/cm3)
  //
  // Here, we assume equal densities for the resin and silica.

  G4double resin_frac = 0.8;

  G4double m_resin  = 12.011*21 + 1.0079*25 + 35.45 + 15.9994*5;
  G4double m_silica = 28.0855 + 15.9994*2;
  G4double m_total  = resin_frac*m_resin + (1-resin_frac)*m_silica;
  
  G4double C_frac   = resin_frac*12.011*21/m_total;
  G4double H_frac   = resin_frac*1.0079*25/m_total;
  G4double Cl_frac  = resin_frac*35.45/m_total;
  G4double O_frac   = (resin_frac*15.9994*5 + (1-resin_frac)*15.9994*2)/m_total;
  G4double Si_frac  = (1-resin_frac)*28.0855/m_total;
  
  material = new G4Material("LabBenchMaterial",
			    density*g/cm3,
			    5);
  material->AddElement(G4Element::GetElement("Carbon"),   C_frac);
  material->AddElement(G4Element::GetElement("Hydrogen"), H_frac);
  material->AddElement(G4Element::GetElement("Chlorine"), Cl_frac);
  material->AddElement(G4Element::GetElement("Oxygen"),   O_frac);
  material->AddElement(G4Element::GetElement("Silicon"),  Si_frac);

  G4cout << "Lab Bench composition: " 
  	 << "C: "   << C_frac << ", H: "  << H_frac  << ", Cl: " << Cl_frac
  	 << ", O: " << O_frac << ", Si: " << Si_frac << G4endl;
  G4cout << "Lab Bench density = " << density << " g/cm3" << G4endl;
  
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

