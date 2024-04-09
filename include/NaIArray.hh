#ifndef NaIArray_h
#define NaIArray_h 1

#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "Constants.hh"
#include "NaIDetector.hh"
#include "NaISD.hh"

#include <vector>

class NaIArray
{
public:
  NaIArray(G4LogicalVolume *log);
  ~NaIArray();

public:
  void Construct();
  void MakeSensitive(NaISD *nai_sd);

public:
  void PrintDetectorDimensionInfo();

public:
  G4LogicalVolume *exp_hall_log;

private:
  G4Transform3D CalculatePlacement(G4String name, G4int sector_id);

private:
  G4Material *nai_mat;

private:
  G4int nai_numbers;

  std::map<G4String, G4double> map_name_to_d_phi;

  std::vector<NaIDetector*> v_nai_detector;
};

#endif