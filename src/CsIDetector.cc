#include "CsIDetector.hh"

#include <string>
#include "TString.h"

//
CsIDetector::CsIDetector(G4LogicalVolume *log)
: exp_hall_log(log)
{
  G4NistManager* nist_manager = G4NistManager::Instance();

  csi_mat = nist_manager->FindOrBuildMaterial("G4_CESIUM_IODIDE");
  mylar_mat = nist_manager->FindOrBuildMaterial("G4_MYLAR");

  check_overlaps = true;
}

//
CsIDetector::~CsIDetector()
{

}

//
G4LogicalVolume *CsIDetector::ConstructCsIDetector(const double (&trap_par)[11], const std::array<G4double, 6> &box_par)
{
  std::cout << "start const CsI Detector." << std::endl;

  TString end_cup_solid_name = TString::Format("%s_solid", csi_name.c_str());
  // std::cout << end_cup_solid_name << std::endl;
  
  G4Trap *end_cup_trap_solid = new G4Trap("end_cup_trap_solid", 
                                          trap_par[0] *mm, // pDz,
                                          trap_par[1] *deg, trap_par[2] *deg, // pTheta, pPhi
                                          trap_par[3] *mm, trap_par[4] *mm, trap_par[5] *mm, // pDy1, pDx1, pDx2
                                          trap_par[6] *deg, // pAlp1
                                          trap_par[7] *mm, trap_par[8] *mm, trap_par[9] *mm, // pDy2, pDx3, pDx4,
                                          trap_par[10] *deg); // pAlp2

  G4Box *cut= new G4Box("cut_solid", 40.0 *mm, 40.0 *mm, 40.0 *mm);
  G4RotationMatrix *rotation_left_end_cup = new G4RotationMatrix();
  rotation_left_end_cup->rotateY(60.0 *deg);
  G4RotationMatrix *rotation_right_end_cup = new G4RotationMatrix();
  rotation_right_end_cup->rotateY(-62.40*deg);

  G4SubtractionSolid *end_cup_temp_solid = new G4SubtractionSolid("end_cup_temp_solid", end_cup_trap_solid, cut, rotation_left_end_cup, G4ThreeVector(box_par[0]*mm, box_par[1]*mm, box_par[2]*mm));
  G4SubtractionSolid* end_cup_solid = new G4SubtractionSolid(end_cup_solid_name.Data(), end_cup_temp_solid, cut, rotation_right_end_cup, G4ThreeVector(box_par[3]*mm, box_par[4]*mm, box_par[5]*mm));

  TString end_cup_log_name = TString::Format("%s_log", csi_name.c_str());
  csi_detector_log = new G4LogicalVolume(end_cup_solid, csi_mat, end_cup_log_name.Data());
  
  // color
  G4VisAttributes *vis_att = new G4VisAttributes(G4Colour(CsIDetector::map_color_par[csi_name][0], CsIDetector::map_color_par[csi_name][1], CsIDetector::map_color_par[csi_name][2], CsIDetector::map_color_par[csi_name][3]));
  vis_att->SetForceSolid(true);
  csi_detector_log->SetVisAttributes(vis_att);

  return csi_detector_log;
}

//
G4VPhysicalVolume *CsIDetector::PlaceCsIDetector(G4RotationMatrix *rot, const G4ThreeVector &pos)
{
  TString end_cup_phy_name = TString::Format("%s_phy", csi_name.c_str());
  csi_detector_phy = new G4PVPlacement(rot, pos, csi_detector_log, end_cup_phy_name.Data(), exp_hall_log, false, sector_id, check_overlaps);

  return csi_detector_phy;
}

//
G4VPhysicalVolume *CsIDetector::PlaceCsIDetector(const G4Transform3D &transfrom_3d)
{
  TString end_cup_phy_name = TString::Format("%s_phy", csi_name.c_str());
  csi_detector_phy = new G4PVPlacement(transfrom_3d, csi_detector_log, end_cup_phy_name.Data(), exp_hall_log, false, sector_id, check_overlaps);

  return csi_detector_phy;
}

//
std::map<G4String, G4int> CsIDetector::map_name_to_ring_id = {
  {"EndCup09", 9},
  {"EndCup10", 10},
  {"EndCup11", 11},
  {"EndCup12", 12},
  {"EndCup13", 13},
  
  {"EndCup14", 14},
  {"EndCup15", 15},
  {"EndCup16", 16},
  {"EndCup17", 17},
  {"EndCup18", 18},
  
  {"EndCup19", 19},
  {"EndCup20", 20},
  {"EndCup21", 21},
  {"EndCup22", 22},
  {"EndCup23", 23},
  {"EndCup24", 24}
};

//
std::map<G4int, G4String> CsIDetector::map_ring_id_to_name = {
  {9, "EndCup09"},
  {10, "EndCup10"},
  {11, "EndCup11"},
  {12, "EndCup12"},
  {13, "EndCup13"},
  
  {14, "EndCup14"},
  {15, "EndCup15"},
  {16, "EndCup16"},
  {17, "EndCup17"},
  {18, "EndCup18"},
  
  {19, "EndCup19"},
  {20, "EndCup20"},
  {21, "EndCup21"},
  {22, "EndCup22"},
  {23, "EndCup23"},
  {24, "EndCup24"}
};

//
std::map<G4String, G4int> CsIDetector::map_name_to_sectors = {
  {"EndCup09", 64},
  {"EndCup10", 64},
  {"EndCup11", 64},
  {"EndCup12", 64},
  {"EndCup13", 64},
  
  {"EndCup14", 64},
  {"EndCup15", 64},
  {"EndCup16", 64},
  {"EndCup17", 64},
  {"EndCup18", 64},
  
  {"EndCup19", 64},
  {"EndCup20", 64},
  {"EndCup21", 64},
  {"EndCup22", 64},
  {"EndCup23", 64},
  {"EndCup24", 64}
};

//
std::map<G4String, std::array<G4double, 11>> CsIDetector::map_trap_par = {
  {"EndCup09", {170.0/2, 1.00594, 39.55115, 10.0/2, 13.20/2, 12.14/2, 3.03384, 13.86/2, 18.01/2, 16.53/2, 3.05618}},
  {"EndCup10", {170.0/2, 1.05403, 37.50169, 10.0/2, 14.30/2, 13.24/2, 3.03384, 13.86/2, 19.46/2, 18.0/2, 3.01496}},
  {"EndCup11", {170.0/2, 1.10308, 35.60871, 10.0/2, 15.30/2, 14.25/2, 3.00527, 13.86/2, 20.82/2, 19.37/2, 2.99434}},
  {"EndCup12", {170.0/2, 1.15241, 33.89051, 10.0/2, 16.30/2, 15.26/2, 2.97670, 13.86/2, 22.18/2, 20.73/2, 2.99434}},
  {"EndCup13", {170.0/2, 1.20281, 32.32773, 10.0/2, 17.30/2, 16.27/2, 2.94813, 13.86/2, 23.53/2, 22.10/2, 2.95312}},
  
  {"EndCup14", {160.0/2, 1.25458, 30.84318, 10.0/2, 18.40/2, 17.38/2, 2.91956, 13.63/2, 24.60/2, 23.21/2, 2.91901}},
  {"EndCup15", {160.0/2, 1.30735, 29.48933, 10.0/2, 19.40/2, 18.39/2, 2.89098, 13.63/2, 25.94/2, 24.56/2, 2.89805}},
  {"EndCup16", {160.0/2, 1.35604, 28.34629, 10.0/2, 20.40/2, 19.40/2, 2.86241, 13.63/2, 27.25/2, 25.88/2, 2.87708}},
  {"EndCup17", {160.0/2, 1.40926, 27.20471, 10.0/2, 21.40/2, 20.41/2, 2.83383, 13.63/2, 28.58/2, 27.23/2, 2.83515}},
  {"EndCup18", {160.0/2, 1.45891, 26.21682, 10.0/2, 22.30/2, 21.32/2, 2.80525, 13.63/2, 29.79/2, 28.45/2, 2.81418}},
  
  {"EndCup19", {150.0/2, 1.51414, 25.18142, 10.0/2, 23.30/2, 22.33/2, 2.77667, 13.40/2, 30.64/2, 29.34/2, 2.77710}},
  {"EndCup20", {150.0/2, 1.56017, 24.40172, 10.0/2, 24.30/2, 23.34/2, 2.74809, 13.40/2, 31.90/2, 30.62/2, 2.73444}},
  {"EndCup21", {150.0/2, 1.60555, 23.67524, 10.0/2, 25.20/2, 24.26/2, 2.69092, 13.40/2, 33.06/2, 31.80/2, 2.69177}},
  {"EndCup22", {150.0/2, 1.65208, 22.97974, 10.0/2, 26.10/2, 25.17/2, 2.66234, 13.40/2, 34.22/2, 32.98/2, 2.64911}},
  {"EndCup23", {150.0/2, 1.69876, 22.31392, 10.0/2, 27.0/2, 26.08/2, 2.63375, 13.40/2, 35.39/2, 34.15/2, 2.64911}},
  {"EndCup24", {150.0/2, 1.74572, 21.69145, 10.0/2, 28.0/2, 27.10/2, 2.57657, 13.40/2, 36.65/2, 35.44/2, 2.58511}}
};

//
std::map<G4String, std::array<G4double, 6>> CsIDetector::map_box_par = {
  {"EndCup09", {-51.97751, 0, 85, 53.95687, 0, 85}},
  {"EndCup10", {-51.91709, 0, 85, 54.06729, 0, 85}},
  {"EndCup11", {-51.80925, 0, 85, 54.13513, 0, 85}},
  {"EndCup12", {-51.70024, 0, 85, 54.20414, 0, 85}},
  {"EndCup13", {-51.59120, 0, 85, 54.26318, 0, 85}},
  
  {"EndCup14", {-51.63967, 0, 80, 54.28471, 0, 80}},
  {"EndCup15", {-51.52697, 0, 80, 54.33741, 0, 80}},
  {"EndCup16", {-51.50679, 0, 80, 54.46759, 0, 80}},
  {"EndCup17", {-51.39286, 0, 80, 54.51152, 0, 80}},
  {"EndCup18", {-51.32272, 0, 80, 54.59166, 0, 80}},
  
  {"EndCup19", {-51.39130, 0, 75, 54.57308, 0, 75}},
  {"EndCup20", {-51.25992, 0, 75, 54.56446, 0, 75}},
  {"EndCup21", {-51.27978, 0, 75, 54.70460, 0, 75}},
  {"EndCup22", {-51.19843, 0, 75, 54.74595, 0, 75}},
  {"EndCup23", {-51.65073, 0, 75, 54.26365, 0, 75}},
  {"EndCup24", {-51.08823, 0, 75, 54.88615, 0, 75}}
};

//
G4double CsIDetector::interval_between_crystal = 0.;

// 0: rotationX angle
// 1: theta
// 2: r of xy
// 3: r of z
std::map<G4String, std::array<G4double, 4>> CsIDetector::map_placement_par = {
  {"EndCup09", {-16.9, 11.26876, 166.26191, 441.1+31.*CsIDetector::interval_between_crystal+8.50722+91.8}},
  {"EndCup10", {-18.2, 10.67967, 178.76883, 441.1+31.*CsIDetector::interval_between_crystal+8.12931+88.1}},
  {"EndCup11", {-19.5, 10.15851, 191.19372, 441.1+31.*CsIDetector::interval_between_crystal+7.72327+84.2}},
  {"EndCup12", {-20.8, 9.70534, 203.53530, 441.1+31.*CsIDetector::interval_between_crystal+7.28932+80.0}},
  {"EndCup13", {-22.1, 9.30852, 215.78387, 441.1+31.*CsIDetector::interval_between_crystal+6.82768+75.6}},
  
  {"EndCup14", {-23.4, 9.02442, 226.01485, 441.1+31.*CsIDetector::interval_between_crystal+6.33859+66.3}},
  {"EndCup15", {-24.7, 8.71136, 237.94879, 441.1+31.*CsIDetector::interval_between_crystal+5.82230+61.4}},
  {"EndCup16", {-26.0, 8.43065, 249.76616, 441.1+31.*CsIDetector::interval_between_crystal+5.27907+56.3}},
  {"EndCup17", {-27.3, 8.18071, 261.46158, 441.1+31.*CsIDetector::interval_between_crystal+4.70919+51.0}},
  {"EndCup18", {-28.6, 7.94441, 273.01994, 441.1+31.*CsIDetector::interval_between_crystal+4.11295+45.4}},
  
  {"EndCup19", {-29.9, 7.78559, 282.01315, 441.1+31.*CsIDetector::interval_between_crystal+3.49065+35.2}},
  {"EndCup20", {-31.2, 7.59889, 293.19949, 441.1+31.*CsIDetector::interval_between_crystal+2.84262+29.2}},
  {"EndCup21", {-32.5, 7.42052, 304.23170, 441.1+31.*CsIDetector::interval_between_crystal+2.16918+23.0}},
  {"EndCup22", {-33.8, 7.25803, 315.11022, 441.1+31.*CsIDetector::interval_between_crystal+1.47069+16.6}},
  {"EndCup23", {-35.1, 7.20307, 325.89422, 441.1+31.*CsIDetector::interval_between_crystal+0.74751+9.9}},
  {"EndCup24", {-36.4, 6.98365, 336.38857, 441.1+31.*CsIDetector::interval_between_crystal+0.+3.0}}
};

//
std::map<G4String, std::array<G4double, 4>> CsIDetector::map_color_par = {
  {"EndCup09", {0.5, 0.5, 0.5, 0.3}}, // black
  {"EndCup10", {0.5, 0.5, 0.5, 0.3}},
  {"EndCup11", {0.5, 0.5, 0.5, 0.3}},
  {"EndCup12", {0.5, 0.5, 0.5, 0.3}},
  {"EndCup13", {0.5, 0.5, 0.5, 0.3}},
  
  {"EndCup14", {1.0, 0., 0., 0.3}}, // red
  {"EndCup15", {1.0, 0., 0., 0.3}},
  {"EndCup16", {1.0, 0., 0., 0.3}},
  {"EndCup17", {1.0, 0., 0., 0.3}},
  {"EndCup18", {1.0, 0., 0., 0.3}},
  
  {"EndCup19", {0., 1.0, 0., 0.3}}, // green
  {"EndCup20", {0., 1.0, 0., 0.3}},
  {"EndCup21", {0., 1.0, 0., 0.3}},
  {"EndCup22", {0., 1.0, 0., 0.3}},
  {"EndCup23", {0., 1.0, 0., 0.3}},
  {"EndCup24", {0., 1.0, 0., 0.3}}
};