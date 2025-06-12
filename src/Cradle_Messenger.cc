#include "Cradle_Messenger.hh"

Cradle_Messenger::Cradle_Messenger(Cradle* C)
:fCradle(C)
{ 
 
  CradleDir = new G4UIdirectory("/Cradle/");
  CradleDir->SetGuidance("Cradle control.");

  XCmd = new G4UIcmdWithADoubleAndUnit("/Cradle/setX",this);
  XCmd->SetGuidance("Set the x position of the center of the top of the cradle");
  XCmd->SetParameterName("choice",false);
  XCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  YCmd = new G4UIcmdWithADoubleAndUnit("/Cradle/setY",this);
  YCmd->SetGuidance("Set the y position of the center of the top of the cradle");
  YCmd->SetParameterName("choice",false);
  YCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ZCmd = new G4UIcmdWithADoubleAndUnit("/Cradle/setZ",this);
  ZCmd->SetGuidance("Set the z position of the center of the top of the cradle");
  ZCmd->SetParameterName("choice",false);
  ZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  cCmd = new G4UIcmdWithoutParameter("/Cradle/Construct",this);
  cCmd->SetGuidance("Construct the cradle");
  cCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

Cradle_Messenger::~Cradle_Messenger()
{
  delete CradleDir;
  delete XCmd;
  delete YCmd;
  delete ZCmd;
  delete cCmd;
}

void Cradle_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == XCmd )
    {fCradle->setX(XCmd->GetNewDoubleValue(newValue));}
  if( command == YCmd )
    {fCradle->setY(YCmd->GetNewDoubleValue(newValue));}
  if( command == ZCmd )
    {fCradle->setZ(ZCmd->GetNewDoubleValue(newValue));}
  if( command == cCmd )
    {fCradle->Construct();}
}
