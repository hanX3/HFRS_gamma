#ifndef GAGGDetector_h
#define GAGGDetector_h 1

#include "Constants.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"

#include "G4SystemOfUnits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

class GAGGDetector
{
public:
  GAGGDetector(G4LogicalVolume *log);
  ~GAGGDetector();

public:
  void SetName(const G4String name) { gagg_name = name; };
  void SetRingId(const G4int id) { ring_id = id; };
  void SetSectorId(const G4int id) { sector_id = id; };
  // GAGG
  G4LogicalVolume *ConstructGAGGDetector(const std::array<G4double, 3> &gagg_par, G4Material *mat);
  G4VPhysicalVolume *PlaceGAGGDetector(G4RotationMatrix *rot, const G4ThreeVector &pos);
  G4VPhysicalVolume *PlaceGAGGDetector(const G4Transform3D &transfrom_3d);

  // ESR
  G4LogicalVolume *ConstructESRSurface(const std::array<G4double, 3> &gagg_par, G4Material *mat);
  G4VPhysicalVolume *PlaceESRSurface(G4RotationMatrix *rot, const G4ThreeVector &pos);
  G4VPhysicalVolume *PlaceESRSurface(const G4Transform3D &transfrom_3d);

public:
  G4String GetName() { return gagg_name; };
  G4int GetRingId() { return ring_id; };
  G4int GetSectorId() { return sector_id; };

  G4LogicalVolume *GetLog() { return gagg_detector_log; };
  G4VPhysicalVolume *GetPhy() { return gagg_detector_phy; };

public:
  G4LogicalVolume *exp_hall_log;

private:
  G4Box *gagg_detector_solid; // for esr
  G4LogicalVolume *gagg_detector_log;
  G4VPhysicalVolume *gagg_detector_phy;

  G4Box *esr_surface_temp_solid; // for next
  G4SubtractionSolid *esr_surface_solid;
  G4LogicalVolume *esr_surface_log;
  G4VPhysicalVolume *esr_surface_phy;

private:
  G4String gagg_name;
  G4int ring_id; // 3,4,...,8
  G4int sector_id; // 0,1,2,...

private:
  G4double esr_surface_thickness;

private:
  G4bool check_overlaps;

public:
  static std::map<G4String, G4int> map_name_to_ring_id;
  static std::map<G4int, G4String> map_ring_id_to_name;
  static std::map<G4String, G4int> map_name_to_sectors;
  static std::map<G4String, std::array<G4double, 3>> map_gagg_par;
  static std::map<G4String, std::array<G4double, 2>> map_placement_par;
  static std::map<G4String, std::array<G4double, 4>> map_color_par;
  static std::map<G4String, std::array<G4double, 4>> map_esr_surface_color_par;

};


#endif