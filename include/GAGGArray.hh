#ifndef GAGGArray_h
#define GAGGArray_h 1

#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "Constants.hh"
#include "GAGGDetector.hh"
#include "GAGGSD.hh"

#include <vector>

class GAGGArray
{
public:
  GAGGArray(G4LogicalVolume *log);
  ~GAGGArray();

public:
  void Construct();
  void MakeSensitive(GAGGSD *gagg_sd);

public:
  void PrintDetectorDimensionInfo();

public:
  G4LogicalVolume *exp_hall_log;

private:
  G4double CalculatePhiAngle(G4String name, G4int sector_id);
  G4RotationMatrix *CalculateRotation(G4String name, G4int sector_id);
  G4ThreeVector CalculatePosition(G4String name, G4int sector_id);
  G4Transform3D CalculatePlacement(G4String name, G4int sector_id);

private:
  G4Material *gagg_mat;

private:
  G4int gagg_numbers;
  G4int gagg_rings;

  std::vector<G4String> v_gagg_name;

  std::vector<GAGGDetector*> v_gagg_detector;
};

#endif