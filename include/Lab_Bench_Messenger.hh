#ifndef Lab_Bench_Messenger_h
#define Lab_Bench_Messenger_h 1

#include "Lab_Bench.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"

class Lab_Bench_Messenger: public G4UImessenger
{
  public:
    Lab_Bench_Messenger(Lab_Bench*);
   ~Lab_Bench_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    Lab_Bench* Bench;
   
    G4UIdirectory*             BenchDir;  

    G4UIcmdWithADoubleAndUnit* XCmd;
    G4UIcmdWithADoubleAndUnit* YCmd;
    G4UIcmdWithADoubleAndUnit* ZCmd;
    G4UIcmdWithADouble* rhoCmd;
    G4UIcmdWithoutParameter*   cCmd;
};

#endif

