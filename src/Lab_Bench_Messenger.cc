#include "Lab_Bench_Messenger.hh"

Lab_Bench_Messenger::Lab_Bench_Messenger(Lab_Bench* B)
:Bench(B)
{ 
 
  BenchDir = new G4UIdirectory("/Bench/");
  BenchDir->SetGuidance("Bench control.");

  XCmd = new G4UIcmdWithADoubleAndUnit("/Bench/setX",this);
  XCmd->SetGuidance("Set the x position of the bench center");
  XCmd->SetParameterName("choice",false);
  XCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  YCmd = new G4UIcmdWithADoubleAndUnit("/Bench/setY",this);
  YCmd->SetGuidance("Set the y position of the bench center");
  YCmd->SetParameterName("choice",false);
  YCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ZCmd = new G4UIcmdWithADoubleAndUnit("/Bench/setZ",this);
  ZCmd->SetGuidance("Set the z position of the bench center");
  ZCmd->SetParameterName("choice",false);
  ZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rhoCmd = new G4UIcmdWithADouble("/Bench/setDensity",this);
  rhoCmd->SetGuidance("Set the density of the bench in g/cm^3");
  rhoCmd->SetParameterName("choice",false);
  rhoCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  cCmd = new G4UIcmdWithoutParameter("/Bench/Construct",this);
  cCmd->SetGuidance("Construct the bench");
  cCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

Lab_Bench_Messenger::~Lab_Bench_Messenger()
{
  delete BenchDir;
  delete XCmd;
  delete YCmd;
  delete ZCmd;
  delete rhoCmd;
  delete cCmd;
}

void Lab_Bench_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == XCmd )
    {Bench->setX(XCmd->GetNewDoubleValue(newValue));}
  if( command == YCmd )
    {Bench->setY(YCmd->GetNewDoubleValue(newValue));}
  if( command == ZCmd )
    {Bench->setZ(ZCmd->GetNewDoubleValue(newValue));}
  if( command == rhoCmd )
    {Bench->setDensity(rhoCmd->GetNewDoubleValue(newValue));}
  if( command == cCmd )
    {Bench->Construct();}
}
