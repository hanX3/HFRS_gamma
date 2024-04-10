#ifndef CsIDetector_h
#define CsIDetector_h 1

#include "Constants.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Trap.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"

#include "G4SystemOfUnits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

class CsIDetector
{
public:
  CsIDetector(G4LogicalVolume *log);
  ~CsIDetector();

public:
  void SetName(const G4String name) { csi_name = name; };
  void SetRingId(const G4int id) { ring_id = id; };
  void SetSectorId(const G4int id) { sector_id = id; };
  // CsI crystal
  G4LogicalVolume *ConstructCsIDetector(const double (&trap_par)[11], const std::array<G4double, 6> &box_par, G4Material *mat);
  G4VPhysicalVolume *PlaceCsIDetector(G4RotationMatrix *rot, const G4ThreeVector &pos);
  G4VPhysicalVolume *PlaceCsIDetector(const G4Transform3D &transfrom_3d);

  // ESR
  G4LogicalVolume *ConstructESRSurface(const std::array<G4double, 6> &box_par, G4Material *mat);
  G4VPhysicalVolume *PlaceESRSurface(G4RotationMatrix *rot, const G4ThreeVector &pos);
  G4VPhysicalVolume *PlaceESRSurface(const G4Transform3D &transfrom_3d);

  // Teflon
  G4LogicalVolume *ConstructTeflonSurface(const std::array<G4double, 6> &box_par, G4Material *mat);
  G4VPhysicalVolume *PlaceTeflonSurface(G4RotationMatrix *rot, const G4ThreeVector &pos);
  G4VPhysicalVolume *PlaceTeflonSurface(const G4Transform3D &transfrom_3d);

  // Teflon
  G4LogicalVolume *ConstructMylarSurface(const std::array<G4double, 6> &box_par, G4Material *mat);
  G4VPhysicalVolume *PlaceMylarSurface(G4RotationMatrix *rot, const G4ThreeVector &pos);
  G4VPhysicalVolume *PlaceMylarSurface(const G4Transform3D &transfrom_3d);

public:
  G4String GetName() { return csi_name; };
  G4int GetRingId() { return ring_id; };
  G4int GetSectorId() { return sector_id; };

  G4LogicalVolume *GetLog() { return csi_detector_log; };
  G4VPhysicalVolume *GetPhy() { return csi_detector_phy; };

public:
  G4LogicalVolume *exp_hall_log;

private:
  G4Trap *trap_csi_detector_solid;
  G4SubtractionSolid *csi_detector_solid;
  G4LogicalVolume *csi_detector_log;
  G4VPhysicalVolume *csi_detector_phy;

  G4Trap *trap_esr_surface_solid;
  G4SubtractionSolid *esr_surface_temp_solid; // for construct teflon
  G4SubtractionSolid *esr_surface_solid;
  G4LogicalVolume *esr_surface_log;
  G4VPhysicalVolume *esr_surface_phy;

  G4Trap *trap_teflon_surface_solid;
  G4SubtractionSolid *teflon_surface_temp_solid; // for construct mylar
  G4SubtractionSolid *teflon_surface_solid;
  G4LogicalVolume *teflon_surface_log;
  G4VPhysicalVolume *teflon_surface_phy;

  G4Trap *trap_mylar_surface_solid;
  G4SubtractionSolid *mylar_surface_temp_solid; // for next
  G4SubtractionSolid *mylar_surface_solid;
  G4LogicalVolume *mylar_surface_log;
  G4VPhysicalVolume *mylar_surface_phy;

private:
  G4String csi_name;
  G4int ring_id; // 9,10,...,24
  G4int sector_id; // 0,2,...,47

private:
  G4double esr_surface_thickness;
  G4double teflon_surface_thickness;
  G4double mylar_surface_thickness;

private:
  G4bool check_overlaps;

private:
  void GetVertices(G4Trap *trap, G4double offset, G4ThreeVector pt[8]);

public:
  static std::map<G4String, G4int> map_name_to_ring_id;
  static std::map<G4int, G4String> map_ring_id_to_name;
  static std::map<G4String, G4int> map_name_to_sectors;
  
  static std::map<G4String, std::array<G4double, 11>> map_trap_par;
  static std::map<G4String, std::array<G4double, 6>> map_box_par;
  static G4double interval_between_crystal;
  static std::map<G4String, std::array<G4double, 4>> map_placement_par;
  static std::map<G4String, std::array<G4double, 4>> map_color_par;
  static std::map<G4String, std::array<G4double, 4>> map_esr_surface_color_par;
  static std::map<G4String, std::array<G4double, 4>> map_teflon_surface_color_par;
  static std::map<G4String, std::array<G4double, 4>> map_mylar_surface_color_par;
};


#endif