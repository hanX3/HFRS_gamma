#include "LaBr3Detector.hh"

#include <string>
#include "TString.h"

//
LaBr3Detector::LaBr3Detector(G4LogicalVolume *log)
: exp_hall_log(log)
{
  check_overlaps = true;
}

//
LaBr3Detector::~LaBr3Detector()
{

}

//
G4LogicalVolume *LaBr3Detector::ConstructLaBr3Detector(const std::array<G4double, 2> &labr3_par, G4Material *mat)
{
  std::cout << "start const LaBr3 Detector." << std::endl;

  TString labr3_solid_name = TString::Format("%s_solid", labr3_name.c_str());
  // std::cout << labr3_solid_name << std::endl;
  
  G4Tubs *labr3_tubs_solid = new G4Tubs("labr3_tubs_solid", 0.*mm, 
                                        LaBr3Detector::map_labr3_par[labr3_name][0]/2. *mm, 
                                        LaBr3Detector::map_labr3_par[labr3_name][1]/2. *mm,
                                        0. *deg,
                                        360. *deg);

  TString labr3_log_name = TString::Format("%s_log", labr3_name.c_str());
  labr3_detector_log = new G4LogicalVolume(labr3_tubs_solid, mat, labr3_log_name.Data());
  
  // color
  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(LaBr3Detector::map_color_par[labr3_name][0], LaBr3Detector::map_color_par[labr3_name][1], LaBr3Detector::map_color_par[labr3_name][2], LaBr3Detector::map_color_par[labr3_name][3]));
  vis_att->SetForceSolid(true);
  labr3_detector_log->SetVisAttributes(vis_att);

  return labr3_detector_log;
}

//
G4VPhysicalVolume *LaBr3Detector::PlaceLaBr3Detector(G4RotationMatrix *rot, const G4ThreeVector &pos)
{
  TString labr3_phy_name = TString::Format("%s_phy", labr3_name.c_str());
  labr3_detector_phy = new G4PVPlacement(new G4RotationMatrix(rot->inverse()), pos, labr3_detector_log, labr3_phy_name.Data(), exp_hall_log, false, sector_id, check_overlaps);

  return labr3_detector_phy;
}

//
G4VPhysicalVolume *LaBr3Detector::PlaceLaBr3Detector(const G4Transform3D &transfrom_3d)
{
  TString labr3_phy_name = TString::Format("%s_phy", labr3_name.c_str());
  labr3_detector_phy = new G4PVPlacement(transfrom_3d, labr3_detector_log, labr3_phy_name.Data(), exp_hall_log, false, sector_id, check_overlaps);

  return labr3_detector_phy;
}

//
std::map<G4String, G4int> LaBr3Detector::map_name_to_ring_id = {
  {"LaBr3_01", 1},
  {"LaBr3_27", 27}
};

//
std::map<G4int, G4String> LaBr3Detector::map_ring_id_to_name = {
  {1, "LaBr3_01"},
  {27, "LaBr3_27"}
};

//
std::map<G4String, G4int> LaBr3Detector::map_name_to_sectors = {
  {"LaBr3_01", 12},
  {"LaBr3_27", 6}
};

// 0: diameter
// 1: length
std::map<G4String, std::array<G4double, 2>> LaBr3Detector::map_labr3_par = {
  {"LaBr3_01", {50.8, 76.2}},
  {"LaBr3_27", {50.8, 76.2}}
};

// 0: distance
// 1: theta
std::map<G4String, std::array<G4double, 2>> LaBr3Detector::map_placement_par = {
  {"LaBr3_01", {620., 9.8}},
  {"LaBr3_27", {400., 65.}}
};

//
std::map<G4String, std::array<G4double, 4>> LaBr3Detector::map_color_par = {
  {"LaBr3_01", {0., 0., 1., 0.3}}, // blue
  {"LaBr3_27", {0., 0., 1., 0.3}} // blue
};