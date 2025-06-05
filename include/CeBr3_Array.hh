#ifndef CeBr3_Array_H
#define CeBr3_Array_H 1

#include "CeBr3_2x2_Detector.hh"
#include "CeBr3_3x4_Detector.hh"
#include "CeBr3_3x6_Detector.hh"
#include "TrackerGammaSD.hh"

class CeBr3_Array 
{
public:
  
  CeBr3_Array(G4LogicalVolume*, Materials*);
  ~CeBr3_Array();

  // Used by the CeBr3_Array_Messenger for placing a single detector
  // (when a geometry file is not specified).
  void setX(G4double x){assemblyPos.setX(x);}
  void setY(G4double y){assemblyPos.setY(y);}
  void setZ(G4double z){assemblyPos.setZ(z);}
  void rotateX(G4double ax){assemblyRot.rotateX(ax);}
  void rotateY(G4double ay){assemblyRot.rotateY(ay);}
  void rotateZ(G4double az){assemblyRot.rotateZ(az);}
  void setType(G4String t){detectorType = t;}
  
  void setGeoFile(G4String fname){geoFileName = fname;}

  void Construct();
  
  void MakeSensitive(TrackerGammaSD*);

private:
  G4LogicalVolume *expHall_log;
  Materials *materials;

  CeBr3_2x2_Detector* detector_2x2;
  CeBr3_3x4_Detector* detector_3x4;
  CeBr3_3x6_Detector* detector_3x6;
  
  G4ThreeVector assemblyPos;
  G4RotationMatrix assemblyRot;
  G4String detectorType;
  
  G4String geoFileName;
  std::ifstream geoFile;

};

#endif

