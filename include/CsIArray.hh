#ifndef CsIArray_h
#define CsIArray_h 1

#include "G4Material.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "Constants.hh"
#include "CsIDetector.hh"
#include "CsISD.hh"

#include <vector>

class CsIArray
{
public:
  CsIArray(G4LogicalVolume *log);
  ~CsIArray();

public:
  void Construct();
  void MakeSensitive(CsISD *csi_sd);

public:
  void TrapParamAdjustment(const std::array<G4double, 11> &in, double (&out)[11]);
  void PrintDetectorDimensionInfo();

public:
  G4LogicalVolume *exp_hall_log;

private:
  G4RotationMatrix *CalculateRotation(G4String name, G4int sector_id);
  G4ThreeVector CalculatePosition(G4String name, G4int sector_id);
  G4Transform3D CalculatePlacement(G4String name, G4int sector_id);

private:
  G4Material *csi_mat;
  G4Material *esr_mat;
  G4Material *teflon_mat;
  G4Material *mylar_mat;

private:
  G4int csi_numbers;
  std::map<G4String, G4double> map_name_to_d_phi;
  std::vector<CsIDetector*> v_csi_detector;
};

#endif