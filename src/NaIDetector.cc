#include "NaIDetector.hh"

#include <string>
#include "TString.h"

//
NaIDetector::NaIDetector(G4LogicalVolume *log)
: exp_hall_log(log)
{
  check_overlaps = true;
}

//
NaIDetector::~NaIDetector()
{

}

//
G4LogicalVolume *NaIDetector::ConstructNaIDetector(const std::array<G4double, 3> &nai_par, G4Material *mat)
{
  std::cout << "start const NaI Detector." << std::endl;

  TString nai_solid_name = TString::Format("%s_solid", nai_name.c_str());
  // std::cout << nai_solid_name << std::endl;
  
  G4Box *nai_box_solid = new G4Box("nai_box_solid", NaIDetector::map_nai_par[nai_name][0]/2. *mm, 
                                    NaIDetector::map_nai_par[nai_name][1]/2. *mm, 
                                    NaIDetector::map_nai_par[nai_name][2]/2. *mm);

  TString nai_log_name = TString::Format("%s_log", nai_name.c_str());
  nai_detector_log = new G4LogicalVolume(nai_box_solid, mat, nai_log_name.Data());
  
  // color
  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(NaIDetector::map_color_par[nai_name][0], NaIDetector::map_color_par[nai_name][1], NaIDetector::map_color_par[nai_name][2], NaIDetector::map_color_par[nai_name][3]));
  vis_att->SetForceSolid(true);
  nai_detector_log->SetVisAttributes(vis_att);

  return nai_detector_log;
}

//
G4VPhysicalVolume *NaIDetector::PlaceNaIDetector(G4RotationMatrix *rot, const G4ThreeVector &pos)
{
  TString nai_phy_name = TString::Format("%s_phy", nai_name.c_str());
  nai_detector_phy = new G4PVPlacement(new G4RotationMatrix(rot->inverse()), pos, nai_detector_log, nai_phy_name.Data(), exp_hall_log, false, sector_id, check_overlaps);

  return nai_detector_phy;
}

//
G4VPhysicalVolume *NaIDetector::PlaceNaIDetector(const G4Transform3D &transfrom_3d)
{
  TString nai_phy_name = TString::Format("%s_phy", nai_name.c_str());
  nai_detector_phy = new G4PVPlacement(transfrom_3d, nai_detector_log, nai_phy_name.Data(), exp_hall_log, false, sector_id, check_overlaps);

  return nai_detector_phy;
}

//
std::map<G4String, G4int> NaIDetector::map_name_to_ring_id = {
  {"NaI_25", 25},
  {"NaI_26", 26}
};

//
std::map<G4int, G4String> NaIDetector::map_ring_id_to_name ={
  {25, "NaI_25"},
  {26, "NaI_26"}
};

//
std::map<G4String, G4int> NaIDetector::map_name_to_sectors = {
  {"NaI_25", 30},
  {"NaI_26", 30}
};

// 0: x
// 1: y
// 2: z
std::map<G4String, std::array<G4double, 3>> NaIDetector::map_nai_par = {
  {"NaI_25", {60., 60., 120.}},
  {"NaI_26", {60., 60., 120.}}
};

// 0: distance
// 1: theta
std::map<G4String, std::array<G4double, 2>> NaIDetector::map_placement_par = {
  {"NaI_25", {500., 45.}},
  {"NaI_26", {450., 55.}}
};

//
std::map<G4String, std::array<G4double, 4>> NaIDetector::map_color_par = {
  {"NaI_25", {0.4, 0.4, 0.3, 0.3}},
  {"NaI_26", {0.4, 0.4, 0.6, 0.3}}
};