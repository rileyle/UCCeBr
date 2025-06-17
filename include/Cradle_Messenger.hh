#ifndef Cradle_Messenger_h
#define Cradle_Messenger_h 1

#include "Cradle.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

class Cradle_Messenger: public G4UImessenger
{
  public:
    Cradle_Messenger(Cradle*);
   ~Cradle_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    Cradle* fCradle;
   
    G4UIdirectory*             CradleDir;  

    G4UIcmdWithADoubleAndUnit* XCmd;
    G4UIcmdWithADoubleAndUnit* YCmd;
    G4UIcmdWithADoubleAndUnit* ZCmd;
    G4UIcmdWithADoubleAndUnit* rXCmd;
    G4UIcmdWithADoubleAndUnit* rYCmd;
    G4UIcmdWithADoubleAndUnit* rZCmd;
    G4UIcmdWithADoubleAndUnit* OCmd;
    G4UIcmdWithoutParameter*   cCmd;
};

#endif

