#ifndef CeBr3_Detector_Messenger_h
#define CeBr3_Detector_Messenger_h 1

#include "CeBr3_Detector.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

class CeBr3_Detector_Messenger: public G4UImessenger
{
  public:
    CeBr3_Detector_Messenger(CeBr3_Detector*);
   ~CeBr3_Detector_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    CeBr3_Detector* CeBr3Det;
   
    G4UIdirectory*             CeBr3Dir;  

    G4UIcmdWithAString* TCmd;
    G4UIcmdWithADoubleAndUnit* XCmd;
    G4UIcmdWithADoubleAndUnit* YCmd;
    G4UIcmdWithADoubleAndUnit* ZCmd;
  //    G4UIcmdWithADoubleAndUnit* RCmd;
  //    G4UIcmdWithADoubleAndUnit* LCmd;
    G4UIcmdWithADoubleAndUnit* rXCmd;
    G4UIcmdWithADoubleAndUnit* rYCmd;
    G4UIcmdWithADoubleAndUnit* rZCmd;
    G4UIcmdWithAString* GCmd;
};


#endif

