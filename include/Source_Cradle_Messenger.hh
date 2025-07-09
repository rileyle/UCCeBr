#ifndef Source_Cradle_Messenger_h
#define Source_Cradle_Messenger_h 1

#include "Source_Cradle.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

class Source_Cradle_Messenger: public G4UImessenger
{
  public:
    Source_Cradle_Messenger(Source_Cradle*);
   ~Source_Cradle_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    Source_Cradle* cradle;
   
    G4UIdirectory*             Source_CradleDir;  

    G4UIcmdWithoutParameter* cCmd;
    G4UIcmdWithADoubleAndUnit* rXCmd;
    G4UIcmdWithADoubleAndUnit* rYCmd;
    G4UIcmdWithADoubleAndUnit* rZCmd;
};


#endif

