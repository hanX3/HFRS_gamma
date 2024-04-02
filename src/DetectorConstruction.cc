#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4SystemOfUnits.hh"

//
DetectorConstruction::DetectorConstruction()
{
  mat_air = nullptr;
  mat_vaccum = nullptr;
  mat_al = nullptr;

  check_overlaps = true;
}

//
DetectorConstruction::~DetectorConstruction()
{
  delete step_limit;
}

//
G4VPhysicalVolume *DetectorConstruction::Construct()
{
  DefineMaterials();
  return DefineVolumes();
}

//
void DetectorConstruction::DefineMaterials()
{
  G4NistManager* nist_manager = G4NistManager::Instance();

  mat_air = nist_manager->FindOrBuildMaterial("G4_AIR");
  mat_vaccum = nist_manager->FindOrBuildMaterial("G4_Galactic");
  mat_al = nist_manager->FindOrBuildMaterial("G4_Al");

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//
G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
  // define world
  G4Box *world_solid = new G4Box("World", 0.5*WorldSizeX, 0.5*WorldSizeY, 0.5*WorldSizeZ);
  world_log = new G4LogicalVolume(world_solid, mat_air, "World");
  G4VPhysicalVolume *world_phys = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), world_log, "World", 0, false, 0, check_overlaps);

  G4SDManager *sd_manager = G4SDManager::GetSDMpointer();

  // CsI Array
  csi_array = new CsIArray(world_log);
  csi_array->Construct();
  CsISD *csi_sd = new CsISD("CsISD", "CsIHitCollection");
  sd_manager->AddNewDetector(csi_sd);
  csi_array->MakeSensitive(csi_sd);

  // Labr3 Array
  labr3_array = new LaBr3Array(world_log);
  labr3_array->Construct();
  LaBr3SD *labr3_sd = new LaBr3SD("LaBr3SD", "LaBr3HitCollection");
  sd_manager->AddNewDetector(labr3_sd);
  labr3_array->MakeSensitive(labr3_sd);

  // gagg Array
  gagg_array = new GAGGArray(world_log);
  gagg_array->Construct();
  GAGGSD *gagg_sd = new GAGGSD("GAGGSD", "GAGGHitCollection");
  sd_manager->AddNewDetector(gagg_sd);
  gagg_array->MakeSensitive(gagg_sd);

  //
  G4double max_step = 0.4 *um;
  step_limit = new G4UserLimits(max_step);
  // ppac_log->SetUserLimits(step_limit);

  return world_phys;
}

//
void DetectorConstruction::SetMaxStep(G4double max_step)
{
  if ((step_limit)&&(max_step>0.)) step_limit->SetMaxAllowedStep(max_step);
}

//
void DetectorConstruction::SetCheckOverlaps(G4bool co)
{
  check_overlaps = co;
}

