#include "Lab_Bench.hh"

Lab_Bench::Lab_Bench(G4LogicalVolume* experimentalHall_log,
		     Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;

  EpoxyResin = materials->FindMaterial("EpoxyResin");

  Length = 100*cm;
  Width  = 100*cm;
  Depth  = 2.54*cm;
  
  Pos.setX(0);
  Pos.setY(-3*2.54*cm);
  Pos.setZ(0);

  Rot = G4RotationMatrix::IDENTITY;
}


Lab_Bench::~Lab_Bench()
{
}

void Lab_Bench::Construct()
{

  bench = new G4Box("Bench", Width/2.0, Depth/2.0, Length/2.0);

  bench_log = new G4LogicalVolume(bench, EpoxyResin, "bench_log", 0, 0, 0);

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
//---------------------------------------------------------------------
void Lab_Bench::setX(G4double x)
{
  Pos.setX(x);
}
//---------------------------------------------------------------------
void Lab_Bench::setY(G4double y)
{
  Pos.setY(y);
}
//---------------------------------------------------------------------
void Lab_Bench::setZ(G4double z)
{
  Pos.setZ(z);
}
//---------------------------------------------------------------------

