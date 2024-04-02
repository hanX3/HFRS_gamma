#ifndef LaBr3Array_h
#define LaBr3Array_h 1

#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "Constants.hh"
#include "LaBr3Detector.hh"
#include "LaBr3SD.hh"

#include <vector>

class LaBr3Array
{
public:
  LaBr3Array(G4LogicalVolume *log);
  ~LaBr3Array();

public:
  void Construct();
  void MakeSensitive(LaBr3SD *labr3_sd);

public:
  void PrintDetectorDimensionInfo();

public:
  G4LogicalVolume *exp_hall_log;

private:
  G4RotationMatrix *CalculateRotation(G4String name, G4int sector_id);
  G4ThreeVector CalculatePosition(G4String name, G4int sector_id);
  G4Transform3D CalculatePlacement(G4String name, G4int sector_id);

private:
  G4Material *labr3_mat;

private:
  G4int labr3_numbers;
  G4int labr3_rings;

  std::vector<G4String> v_labr3_name;
  std::map<G4String, G4int> map_name_to_d_phi;

  std::vector<LaBr3Detector*> v_labr3_detector;
};

#endif