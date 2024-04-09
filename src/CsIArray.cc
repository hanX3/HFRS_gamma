#include "CsIArray.hh"
#include "CsIDetector.hh"

#include <cmath>
#include "TString.h"

//
CsIArray::CsIArray(G4LogicalVolume *log)
: exp_hall_log(log)
{
  csi_numbers = 0;

  for(auto it=CsIDetector::map_name_to_sectors.begin();it!=CsIDetector::map_name_to_sectors.end();it++){
    map_name_to_d_phi[it->first] = 360./it->second;
    csi_numbers += it->second;
  }
  //
  PrintDetectorDimensionInfo();
}

//
CsIArray::~CsIArray()
{

}

//
void CsIArray::Construct()
{
  std::vector<CsIDetector*>::iterator it = v_csi_detector.begin();
  // clear all elements from the array
  for(;it!=v_csi_detector.end();it++) delete *it;
  v_csi_detector.clear();

  std::map<G4int, G4int> map_i2ring;
  std::map<G4int, G4int> map_i2sector;
  std::map<G4int, G4String> map_i2name;
  int ii = 0;
  for(auto it=CsIDetector::map_name_to_ring_id.begin();it!=CsIDetector::map_name_to_ring_id.end();it++){
    for(int j=0;j<CsIDetector::map_name_to_sectors[it->first];j++){
      map_i2ring[ii] = it->second;
      map_i2sector[ii] = j;
      map_i2name[ii] = it->first;
      ii++;
    }
  }

  for(auto it=map_i2ring.begin();it!=map_i2ring.end();it++){
    G4cout << "i " << it->first << " ring " << it->second << G4endl;
  }
  for(auto it=map_i2sector.begin();it!=map_i2sector.end();it++){
    G4cout << "i " << it->first << " sector " << it->second << G4endl;
  }
  for(auto it=map_i2name.begin();it!=map_i2name.end();it++){
    G4cout << "i " << it->first << " name " << it->second << G4endl;
  }

  for(int i=0;i<csi_numbers;i++){
    v_csi_detector.push_back(new CsIDetector(exp_hall_log));
    v_csi_detector[i]->SetName(map_i2name[i]);
    v_csi_detector[i]->SetRingId(map_i2ring[i]);
    v_csi_detector[i]->SetSectorId(map_i2sector[i]);
  }

  G4double trap_par[11] = {};
  for(it=v_csi_detector.begin();it!=v_csi_detector.end();it++){
    TrapParamAdjustment(CsIDetector::map_trap_par[(*it)->GetName()], trap_par);
    (*it)->ConstructCsIDetector(trap_par, CsIDetector::map_box_par[(*it)->GetName()]);
    // (*it)->PlaceCsIDetector(CalculateRotation((*it)->GetName(), (*it)->GetSectorId()), CalculatePosition((*it)->GetName(), (*it)->GetSectorId()));
    (*it)->PlaceCsIDetector(CalculatePlacement((*it)->GetName(), (*it)->GetSectorId()));
  }
}

//
void CsIArray::MakeSensitive(CsISD *csi_sd)
{
  std::vector<CsIDetector*>::iterator it = v_csi_detector.begin();
  for(;it!=v_csi_detector.end();it++){
     (*it)->GetLog()->SetSensitiveDetector(csi_sd);
  }
}

//
void CsIArray::TrapParamAdjustment(const std::array<G4double, 11> &in, double (&out)[11])
{
  // get input
  double dy1 = in[3], dx1 = in[4], dx2 = in[5], alp1 = in[6];
  double dy2 = in[7], dx3 = in[8], dx4 = in[9], alp2 = in[10];

  // adjust alpha
  //alp1 = alp2 = (alp1 + alp2)/2.;
  alp1 = alp2 = std::atan((std::tan(alp1) + std::tan(alp2))/2.);

  // adjust dx
  double k1 = (dx1 - dx2)/(dy1 + dy1);
  double k2 = (dx3 - dx4)/(dy2 + dy2) ;
  double k  = (k1 + k2)/2.;
  double l1 = (dx1 + dx2)/2.;
  double l2 = (dx3 + dx4)/2.;
  dx1 = l1 + k*dy1; dx2 = l1 - k*dy1; 
  dx3 = l2 + k*dy2; dx4 = l2 - k*dy2; 

  // set output
  out[0] = in[0]; out[1] = in[1]; out[2] = in[2];
  out[3] = in[3]; out[4] = dx1; out[5] = dx2; out[6]  = alp1;
  out[7] = in[7]; out[8] = dx3; out[9] = dx4; out[10] = alp2;
} 

//
G4RotationMatrix *CsIArray::CalculateRotation(G4String name, G4int sector_id)
{
  G4RotationMatrix *rot_matrix = new G4RotationMatrix();
  G4double rot_x_angle = CsIDetector::map_placement_par[name][0] *deg;
  G4double rot_y_angle = 0. *deg;
  G4double rot_z_angle = -180. *deg - map_name_to_d_phi[name]*sector_id*deg;
  rot_matrix->rotateZ(rot_z_angle);
  rot_matrix->rotateX(rot_x_angle);
  rot_matrix->print(G4cout);

  return rot_matrix;
}

//
G4ThreeVector CsIArray::CalculatePosition(G4String name, G4int sector_id)
{
  G4double theta_xy = (90.+CsIDetector::map_placement_par[name][1]) *deg + map_name_to_d_phi[name]*sector_id*deg;
  G4double r_xy = CsIDetector::map_placement_par[name][2] *mm;
  G4double x = r_xy*std::cos(theta_xy);
  G4double y = r_xy*std::sin(theta_xy);
  G4double z = CsIDetector::map_placement_par[name][3] *mm;
  G4ThreeVector pos = G4ThreeVector(x, y, z);
  G4cout << "pos x " << pos.x() << "pos y " << pos.y() << "pos z " << pos.z() << G4endl;

  return pos;
}

//
G4Transform3D CsIArray::CalculatePlacement(G4String name, G4int sector_id)
{
  G4RotationMatrix *rot_matrix = new G4RotationMatrix();
  G4double rot_x_angle = CsIDetector::map_placement_par[name][0] *deg;
  G4double rot_y_angle = 0. *deg;
  G4double rot_z_angle = -180. *deg - map_name_to_d_phi[name]*sector_id*deg;
  rot_matrix->rotateZ(rot_z_angle);
  rot_matrix->rotateX(rot_x_angle);
  rot_matrix->print(G4cout);

  G4double theta_xy = (90.+CsIDetector::map_placement_par[name][1]) *deg + map_name_to_d_phi[name]*sector_id*deg;
  G4double r_xy = CsIDetector::map_placement_par[name][2] *mm;
  G4double x = r_xy*std::cos(theta_xy);
  G4double y = r_xy*std::sin(theta_xy);
  G4double z = CsIDetector::map_placement_par[name][3] *mm;
  G4ThreeVector pos = G4ThreeVector(x, y, z);
  G4cout << "pos x " << pos.x() << "pos y " << pos.y() << "pos z " << pos.z() << G4endl;

  G4RotationMatrix *rot_matrix_new = new G4RotationMatrix(rot_matrix->inverse());

  G4Transform3D transform(*rot_matrix_new, pos);

  return transform;
}

//
void CsIArray::PrintDetectorDimensionInfo()
{
  for(auto it=CsIDetector::map_trap_par.begin();it!=CsIDetector::map_trap_par.end();it++){
    std::cout << it->first << std::endl;
    for(auto j=0;j<it->second.size();j++){
      std::cout << it->second[j] << " ";
    }
    std::cout <<std::endl;
  }
}