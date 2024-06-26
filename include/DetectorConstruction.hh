#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "Constants.hh"
#include "CsISD.hh"
#include "CsIArray.hh"
#include "LaBr3SD.hh"
#include "LaBr3Array.hh"
#include "GAGGSD.hh"
#include "GAGGArray.hh"
#include "NaISD.hh"
#include "NaIArray.hh"

#include "G4VUserDetectorConstruction.hh"
#include "tls.hh"

#include "G4Element.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PhysicalConstants.hh"

class G4LogicalVolume;
class G4Material;
class G4UserLimits;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  ~DetectorConstruction() override;

public:
  G4VPhysicalVolume* Construct() override;

  // Set methods
  void SetMaxStep(G4double );
  void SetCheckOverlaps(G4bool );

private:
  // methods
  void DefineMaterials();
  G4VPhysicalVolume *DefineVolumes();

private:
  CsIArray *csi_array;
  LaBr3Array *labr3_array;
  GAGGArray *gagg_array;
  NaIArray *nai_array;

private:
  //
  G4LogicalVolume *world_log;

  //
  G4Material *air_mat;
  G4Material *vaccum_mat;
  G4Material *al_mat;

  G4UserLimits *step_limit;
  G4bool check_overlaps;

  //
};

#endif
