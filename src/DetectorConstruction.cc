#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
{
  //  Materials* materials=new Materials();
  materials=new Materials();

  // Experimental Hall

  Experimental_Hall* ExperimentalHall = new Experimental_Hall(materials);
  ExpHall_phys=ExperimentalHall->Construct();
  ExpHall_log=ExperimentalHall->GetLogVolume();
  //   ExperimentalHall->Report();
  ExperimentalHallMessenger = new Experimental_Hall_Messenger(ExperimentalHall);

  // CeBr3 Array

  the_CeBr3_Array = new CeBr3_Array(ExpHall_log, materials);
  the_CeBr3_Array_Messenger = new CeBr3_Array_Messenger(the_CeBr3_Array);

  capsule = new Source_Capsule(ExpHall_log, materials);
  capsule_Messenger = new Source_Capsule_Messenger(capsule);
  
  brick = new Lead_Brick(ExpHall_log, materials);

  brick_Messenger = new Lead_Brick_Messenger(brick);

  bench = new Lab_Bench(ExpHall_log, materials);

  bench_Messenger = new Lab_Bench_Messenger(bench);

  target = new Target(ExpHall_log, materials);

  target_Messenger = new Target_Messenger(target);
}

DetectorConstruction::~DetectorConstruction()
{
  delete ExperimentalHallMessenger;
  delete TrackerGammaSDMessenger;
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{

  the_CeBr3_Array->Construct();

  //------------------------------------------------ 
  // Sensitive detectors
  //------------------------------------------------ 

  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  //------------------------------------------------
  // Detectors sensitive for gamma-ray tracking
  //-------------------------------------------------

  TrackerGamma = new TrackerGammaSD("GammaTracker");
  TrackerGammaSDMessenger = new TrackerGammaSD_Messenger(TrackerGamma);
  SDman->AddNewDetector(TrackerGamma);
  the_CeBr3_Array->MakeSensitive(TrackerGamma);

  return ExpHall_phys;
}
