#include "GAGGDetector.hh"

#include <string>
#include "TString.h"

//
GAGGDetector::GAGGDetector(G4LogicalVolume *log)
: exp_hall_log(log)
{
  check_overlaps = true;
}

//
GAGGDetector::~GAGGDetector()
{

}

//
G4LogicalVolume *GAGGDetector::ConstructGAGGDetector(const std::array<G4double, 3> &gagg_par, G4Material *mat)
{
  std::cout << "start const GAGG Detector." << std::endl;

  TString gagg_solid_name = TString::Format("%s_solid", gagg_name.c_str());
  // std::cout << gagg_solid_name << std::endl;
  
  G4Box *gagg_box_solid = new G4Box("gagg_box_solid", 
                                    GAGGDetector::map_gagg_par[gagg_name][0]/2. *mm, 
                                    GAGGDetector::map_gagg_par[gagg_name][1]/2. *mm, 
                                    GAGGDetector::map_gagg_par[gagg_name][2]/2. *mm );

  TString gagg_log_name = TString::Format("%s_log", gagg_name.c_str());
  gagg_detector_log = new G4LogicalVolume(gagg_box_solid, mat, gagg_log_name.Data());
  
  // color
  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(GAGGDetector::map_color_par[gagg_name][0], GAGGDetector::map_color_par[gagg_name][1], GAGGDetector::map_color_par[gagg_name][2], GAGGDetector::map_color_par[gagg_name][3]));
  vis_att->SetForceSolid(true);
  gagg_detector_log->SetVisAttributes(vis_att);

  return gagg_detector_log;
}

//
G4VPhysicalVolume *GAGGDetector::PlaceGAGGDetector(G4RotationMatrix *rot, const G4ThreeVector &pos)
{
  TString gagg_phy_name = TString::Format("%s_phy", gagg_name.c_str());
  gagg_detector_phy = new G4PVPlacement(rot, pos, gagg_detector_log, gagg_phy_name.Data(), exp_hall_log, false, sector_id, check_overlaps);

  return gagg_detector_phy;
}

//
G4VPhysicalVolume *GAGGDetector::PlaceGAGGDetector(const G4Transform3D &transfrom_3d)
{
  TString gagg_phy_name = TString::Format("%s_phy", gagg_name.c_str());
  gagg_detector_phy = new G4PVPlacement(transfrom_3d, gagg_detector_log, gagg_phy_name.Data(), exp_hall_log, false, sector_id, check_overlaps);

  return gagg_detector_phy;
}

//
std::map<G4String, G4int> GAGGDetector::map_name_to_ring_id = {
  {"GAGG_03", 3},
  {"GAGG_04", 4},
  {"GAGG_05", 5}
};

//
std::map<G4int, G4String> GAGGDetector::map_ring_id_to_name = {
  {3, "GAGG_03"},
  {4, "GAGG_04"},
  {5, "GAGG_05"}
};

//
std::map<G4String, G4int> GAGGDetector::map_name_to_sectors = {
  {"GAGG_03", 12},
  {"GAGG_04", 6},
  {"GAGG_05", 6}
};

// 0: x
// 1: y
// 2: z
std::map<G4String, std::array<G4double, 3>> GAGGDetector::map_gagg_par = {
  {"GAGG_03", {20., 20., 75.}}, // imp add 3 GAGG detectors to one
  {"GAGG_04", {35., 35., 75.}}, // BNU 
  {"GAGG_05", {35., 35., 120.}}, // PKU
};

// 0: distance
// 1: theta
std::map<G4String, std::array<G4double, 2>> GAGGDetector::map_placement_par = {
  {"GAGG_03", {540., 14.2}},
  {"GAGG_04", {540., 14.2}},
  {"GAGG_05", {540.+(120-35)/2., 14.2}}
};

//
std::map<G4String, std::array<G4double, 4>> GAGGDetector::map_color_par = {
  {"GAGG_03", {0.8, 0.3, 0.3, 0.3}}, //
  {"GAGG_04", {0.3, 0.8, 0.3, 0.3}}, // 
  {"GAGG_05", {0.3, 0.3, 0.8, 0.3}} // 
};