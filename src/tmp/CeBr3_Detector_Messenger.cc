#include "CeBr3_Detector_Messenger.hh"

CeBr3_Detector_Messenger::CeBr3_Detector_Messenger(CeBr3_Detector* SD)
:CeBr3Det(SD)
{ 
 
  CeBr3Dir = new G4UIdirectory("/CeBr3/");
  CeBr3Dir->SetGuidance("CeBr3 control.");

  TCmd = new G4UIcmdWithAString("/CeBr3/Type",this);
  TCmd->SetGuidance("Set the detector type (2x2 | 3x4 | 3x6).");
  TCmd->SetParameterName("choice",false);
  TCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  XCmd = new G4UIcmdWithADoubleAndUnit("/CeBr3/setX",this);
  XCmd->SetGuidance("Set the x position of the detector (crystal center)");
  XCmd->SetParameterName("choice",false);
  XCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  YCmd = new G4UIcmdWithADoubleAndUnit("/CeBr3/setY",this);
  YCmd->SetGuidance("Set the y position of the detector (crystal center)");
  YCmd->SetParameterName("choice",false);
  YCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ZCmd = new G4UIcmdWithADoubleAndUnit("/CeBr3/setZ",this);
  ZCmd->SetGuidance("Set the z position of the detector (crystal center)");
  ZCmd->SetParameterName("choice",false);
  ZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  //  RCmd = new G4UIcmdWithADoubleAndUnit("/CeBr3/setR",this);
  //  RCmd->SetGuidance("Set the radius of the CeBr3 crystal");
  //  RCmd->SetParameterName("choice",false);
  //  RCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  //  LCmd = new G4UIcmdWithADoubleAndUnit("/CeBr3/setL",this);
  //  LCmd->SetGuidance("Set the length of the CeBr3 crystal");
  //  LCmd->SetParameterName("choice",false);
  //  LCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rXCmd = new G4UIcmdWithADoubleAndUnit("/CeBr3/rotateX",this);
  rXCmd->SetGuidance("Rotate the detector about the x axis");
  rXCmd->SetParameterName("choice",false);
  rXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rYCmd = new G4UIcmdWithADoubleAndUnit("/CeBr3/rotateY",this);
  rYCmd->SetGuidance("Rotate the detector about the y axis");
  rYCmd->SetParameterName("choice",false);
  rYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  rZCmd = new G4UIcmdWithADoubleAndUnit("/CeBr3/rotateZ",this);
  rZCmd->SetGuidance("Rotate the detector about the z axis");
  rZCmd->SetParameterName("choice",false);
  rZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  GCmd = new G4UIcmdWithAString("/CeBr3/GeometryFile",this);
  GCmd->SetGuidance("Set the geometry file name.");
  GCmd->SetParameterName("choice",false);
  GCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}



CeBr3_Detector_Messenger::~CeBr3_Detector_Messenger()
{
  delete CeBr3Dir;
  delete TCmd;
  delete XCmd;
  delete YCmd;
  delete ZCmd;
  //  delete RCmd;
  //  delete LCmd;
  delete rXCmd;
  delete rYCmd;
  delete rZCmd;
  delete GCmd;
}


void CeBr3_Detector_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == TCmd )
    {CeBr3Det->setType(newValue);}
  if( command == XCmd )
    {CeBr3Det->setX(XCmd->GetNewDoubleValue(newValue));}
  if( command == YCmd )
    {CeBr3Det->setY(YCmd->GetNewDoubleValue(newValue));}
  if( command == ZCmd )
    {CeBr3Det->setZ(ZCmd->GetNewDoubleValue(newValue));}
  //  if( command == RCmd )
  //    {CeBr3Det->setR(RCmd->GetNewDoubleValue(newValue));}
  //  if( command == LCmd )
  //    {CeBr3Det->setL(LCmd->GetNewDoubleValue(newValue));}
  if( command == ZCmd )
    {CeBr3Det->setZ(ZCmd->GetNewDoubleValue(newValue));}
  if( command == rXCmd )
    {CeBr3Det->rotateX(rXCmd->GetNewDoubleValue(newValue));}
  if( command == rYCmd )
    {CeBr3Det->rotateY(rYCmd->GetNewDoubleValue(newValue));}
  if( command == rZCmd )
    {CeBr3Det->rotateZ(rZCmd->GetNewDoubleValue(newValue));}
  if( command == GCmd )
    {CeBr3Det->setGeoFile(newValue);}
}
