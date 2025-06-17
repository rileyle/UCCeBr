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

  rXCmd = new G4UIcmdWithADoubleAndUnit("/Cradle/rotateX",this);
  rXCmd->SetGuidance("Rotate the cradle about the x axis");
  rXCmd->SetParameterName("choice",false);
  rXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rYCmd = new G4UIcmdWithADoubleAndUnit("/Cradle/rotateY",this);
  rYCmd->SetGuidance("Rotate the cradle about the y axis");
  rYCmd->SetParameterName("choice",false);
  rYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rZCmd = new G4UIcmdWithADoubleAndUnit("/Cradle/rotateZ",this);
  rZCmd->SetGuidance("Rotate the cradle about the z axis");
  rZCmd->SetParameterName("choice",false);
  rZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  OCmd = new G4UIcmdWithADoubleAndUnit("/Cradle/setOffset",this);
  OCmd->SetGuidance("Set the offset between cradle halves");
  OCmd->SetParameterName("choice",false);
  OCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
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
  delete rXCmd;
  delete rYCmd;
  delete rZCmd;
  delete OCmd;
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
  if( command == rXCmd )
    {fCradle->rotateX(rXCmd->GetNewDoubleValue(newValue));}
  if( command == rYCmd )
    {fCradle->rotateY(rYCmd->GetNewDoubleValue(newValue));}
  if( command == rZCmd )
    {fCradle->rotateZ(rZCmd->GetNewDoubleValue(newValue));}
  if( command == OCmd )
    {fCradle->setOffset(OCmd->GetNewDoubleValue(newValue));}
  if( command == cCmd )
    {fCradle->Construct(); fCradle->PlaceCradle();}
}
