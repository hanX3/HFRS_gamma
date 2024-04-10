#include "LaBr3Detector.hh"

#include <string>
#include "TString.h"

//
LaBr3Detector::LaBr3Detector(G4LogicalVolume *log)
: exp_hall_log(log)
{
  al_shell_thickness = LaBr3AlShellThickness;
  check_overlaps = true;
}

//
LaBr3Detector::~LaBr3Detector()
{

}

// LaBr3
G4LogicalVolume *LaBr3Detector::ConstructLaBr3Detector(const std::array<G4double, 2> &labr3_par, G4Material *mat)
{
  std::cout << "start const LaBr3 Detector." << std::endl;

  TString labr3_solid_name = TString::Format("%s_solid", labr3_name.c_str());
  // std::cout << labr3_solid_name << std::endl;
  
  labr3_detector_solid = new G4Tubs("labr3_detector_solid", 0.*mm, 
                                    LaBr3Detector::map_labr3_par[labr3_name][0]/2. *mm, 
                                    LaBr3Detector::map_labr3_par[labr3_name][1]/2. *mm,
                                    0. *deg,
                                    360. *deg);

  TString labr3_log_name = TString::Format("%s_log", labr3_name.c_str());
  labr3_detector_log = new G4LogicalVolume(labr3_detector_solid, mat, labr3_log_name.Data());
  
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

// Al shell
G4LogicalVolume *LaBr3Detector::ConstructAlShell(const std::array<G4double, 2> &al_par, G4Material *mat)
{
  std::cout << "start const Al Shell Detector." << std::endl;

  TString al_shell_solid_name = TString::Format("%s_al_shell_solid", labr3_name.c_str());
  // std::cout << labr3_solid_name << std::endl;
  
  al_shell_temp_solid = new G4Tubs("al_shell_temp_solid", 0.*mm, 
                                    LaBr3Detector::map_al_par[labr3_name][0]/2. *mm, 
                                    LaBr3Detector::map_al_par[labr3_name][1]/2. *mm,
                                    0. *deg,
                                    360. *deg);

  G4Tubs *cut_tubs_solid = new G4Tubs("cut_tubs_solid", 0.*mm,
                                      LaBr3Detector::map_al_par[labr3_name][0]/2. *mm - al_shell_thickness, 
                                      LaBr3Detector::map_al_par[labr3_name][1]/2. *mm,
                                      0. *deg,
                                      360. *deg);
  al_shell_solid = new G4SubtractionSolid(al_shell_solid_name.Data(), al_shell_temp_solid, cut_tubs_solid, nullptr, G4ThreeVector(0.,0.,al_shell_thickness));

  TString al_shell_log_name = TString::Format("%s_al_shell_log", labr3_name.c_str());
  al_shell_log = new G4LogicalVolume(al_shell_solid, mat, al_shell_log_name.Data());
  
  // color
  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(LaBr3Detector::map_color_al_shell_par[labr3_name][0], 
                                                          LaBr3Detector::map_color_al_shell_par[labr3_name][1], 
                                                          LaBr3Detector::map_color_al_shell_par[labr3_name][2], 
                                                          LaBr3Detector::map_color_al_shell_par[labr3_name][3]));
  vis_att->SetForceSolid(true);
  al_shell_log->SetVisAttributes(vis_att);

  return al_shell_log;
}

//
G4VPhysicalVolume *LaBr3Detector::PlaceAlShell(G4RotationMatrix *rot, const G4ThreeVector &pos)
{
  TString al_shell_phy_name = TString::Format("%s_al_shell_phy", labr3_name.c_str());
  al_shell_phy = new G4PVPlacement(new G4RotationMatrix(rot->inverse()), pos, al_shell_log, al_shell_phy_name.Data(), exp_hall_log, false, sector_id, check_overlaps);

  return al_shell_phy;
}

//
G4VPhysicalVolume *LaBr3Detector::PlaceAlShell(const G4Transform3D &transfrom_3d)
{
  // adjust transfrom_3d
  G4RotationMatrix rot = transfrom_3d.getRotation();
  G4ThreeVector pos = rot.inverse()*transfrom_3d.getTranslation();

  double x = pos.x();
  double y = pos.y();
  double z = pos.z();
  G4cout << "x = " << x << " y = " << y << " z = " << z << G4endl;

  z = z - al_shell_thickness - (LaBr3Detector::map_labr3_par[labr3_name][1]-LaBr3Detector::map_al_par[labr3_name][1])/2.;
  G4ThreeVector pos_new = rot*G4ThreeVector(x, y, z);
  G4Transform3D transform_3d_new(rot, pos_new);

  TString al_shell_phy_name = TString::Format("%s_al_shell_phy", labr3_name.c_str());
  labr3_detector_phy = new G4PVPlacement(transform_3d_new, al_shell_log, al_shell_phy_name.Data(), exp_hall_log, false, sector_id, check_overlaps);

  return al_shell_phy;
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
  {"LaBr3_01", 10},
  {"LaBr3_27", 8}
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
  {"LaBr3_01", {680., 9.8}},
  {"LaBr3_27", {400., 65.}}
};

// 0: diameter outer
// 1: length
std::map<G4String, std::array<G4double, 2>> LaBr3Detector::map_al_par = {
  {"LaBr3_01", {55.8, 75.4}},
  {"LaBr3_27", {55.8, 75.4}}
};

//
std::map<G4String, std::array<G4double, 4>> LaBr3Detector::map_color_par = {
  {"LaBr3_01", {0., 0., 1., 0.3}}, // blue
  {"LaBr3_27", {0., 0., 1., 0.3}} // blue
};

//
std::map<G4String, std::array<G4double, 4>> LaBr3Detector::map_color_al_shell_par = {
  {"LaBr3_01", {0.2, 0., 1., 0.3}},
  {"LaBr3_27", {0.2, 0., 1., 0.3}}
};