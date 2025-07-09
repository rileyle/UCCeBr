#include "Source_Cradle_Messenger.hh"

Source_Cradle_Messenger::Source_Cradle_Messenger(Source_Cradle* sc)
:cradle(sc)
{ 
 
  Source_CradleDir = new G4UIdirectory("/Source/Cradle/");
  Source_CradleDir->SetGuidance("Source_Cradle control.");

  cCmd = new G4UIcmdWithoutParameter("/Source/Cradle/Construct",this);
  cCmd->SetGuidance("Construct the source cradle");
  cCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  rXCmd = new G4UIcmdWithADoubleAndUnit("/Source/Cradle/rotateX", this);
  rXCmd->SetGuidance("Rotate the cradle about the x axis");
  rXCmd->SetParameterName("choice",false);
  rXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rYCmd = new G4UIcmdWithADoubleAndUnit("/Source/Cradle/rotateY", this);
  rYCmd->SetGuidance("Rotate the cradle about the y axis");
  rYCmd->SetParameterName("choice",false);
  rYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rZCmd = new G4UIcmdWithADoubleAndUnit("/Source/Cradle/rotateZ", this);
  rZCmd->SetGuidance("Rotate the cradle about the z axis");
  rZCmd->SetParameterName("choice",false);
  rZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

Source_Cradle_Messenger::~Source_Cradle_Messenger()
{
  delete Source_CradleDir;
  delete cCmd;
  delete rXCmd;
  delete rYCmd;
  delete rZCmd;
}


void Source_Cradle_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == cCmd )
    {cradle->Construct();}
  if( command == rXCmd )
    {cradle->rotateX(rXCmd->GetNewDoubleValue(newValue));}
  if( command == rYCmd )
    {cradle->rotateY(rYCmd->GetNewDoubleValue(newValue));}
  if( command == rZCmd )
    {cradle->rotateZ(rZCmd->GetNewDoubleValue(newValue));}
}

