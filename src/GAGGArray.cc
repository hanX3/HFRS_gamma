#include "GAGGArray.hh"
#include "GAGGDetector.hh"

#include <cmath>
#include "TString.h"

//
GAGGArray::GAGGArray(G4LogicalVolume *log)
: exp_hall_log(log)
{
  gagg_numbers = 0;

  for(auto it=GAGGDetector::map_name_to_sectors.begin();it!=GAGGDetector::map_name_to_sectors.end();it++){
   gagg_numbers += it->second;
  }
  
  //
  G4NistManager *nist_manager = G4NistManager::Instance();

  G4Element *o_element = nist_manager->FindOrBuildElement("O");
  G4Element *gd_element = nist_manager->FindOrBuildElement("Gd");
  G4Element *ga_element = nist_manager->FindOrBuildElement("Ga");
  G4Element *al_element = nist_manager->FindOrBuildElement("Al");

  gagg_mat = new G4Material("G4_GAGG", 6.63 *g/cm3, 4);
  gagg_mat->AddElement(gd_element, 3);
  gagg_mat->AddElement(al_element, 2);
  gagg_mat->AddElement(ga_element, 3);
  gagg_mat->AddElement(o_element, 12);
  
  PrintDetectorDimensionInfo();
}

//
GAGGArray::~GAGGArray()
{

}

//
void GAGGArray::Construct()
{
  std::vector<GAGGDetector*>::iterator it = v_gagg_detector.begin();
  // clear all elements from the array
  for(;it!=v_gagg_detector.end();it++) delete *it;
  v_gagg_detector.clear();

  std::map<G4int, G4int> map_i2ring;
  std::map<G4int, G4int> map_i2sector;
  std::map<G4int, G4String> map_i2name;
  int ii = 0;
  for(auto it=GAGGDetector::map_name_to_ring_id.begin();it!=GAGGDetector::map_name_to_ring_id.end();it++){
    for(int j=0;j<GAGGDetector::map_name_to_sectors[it->first];j++){
      map_i2ring[ii] = it->second;
      map_i2sector[ii] = j;
      map_i2name[ii] = it->first;
      ii++;
    }
  }

  for(int i=0;i<gagg_numbers;i++){
    v_gagg_detector.push_back(new GAGGDetector(exp_hall_log));
    v_gagg_detector[i]->SetName(map_i2name[i]);
    v_gagg_detector[i]->SetRingId(map_i2ring[i]);
    v_gagg_detector[i]->SetSectorId(map_i2sector[i]);
  }

  for(it=v_gagg_detector.begin();it!=v_gagg_detector.end();it++){
    (*it)->ConstructGAGGDetector(GAGGDetector::map_gagg_par[(*it)->GetName()], gagg_mat);
    (*it)->PlaceGAGGDetector(CalculatePlacement((*it)->GetName(), (*it)->GetSectorId()));
  }
}

//
void GAGGArray::MakeSensitive(GAGGSD *gagg_sd)
{
  std::vector<GAGGDetector*>::iterator it = v_gagg_detector.begin();
  for(;it!=v_gagg_detector.end();it++){
     (*it)->GetLog()->SetSensitiveDetector(gagg_sd);
  }
}

//
G4double GAGGArray::CalculatePhiAngle(G4String name, G4int sector_id)
{
  if(GAGGDetector::map_name_to_ring_id[name]==3){ // for imp GAGG detectors
    return sector_id*10.5;
  }else if(GAGGDetector::map_name_to_ring_id[name]==4){ // for BNU GAGG detectors
    return 134.+sector_id*19;
  }else if(GAGGDetector::map_name_to_ring_id[name]==5){ // for PKU GAGG detectors
    return 250.+sector_id*19;
  }else{
    G4cout << "can not find " << name << ", please check." << G4endl;
    return 0;
  }
}

//
G4Transform3D GAGGArray::CalculatePlacement(G4String name, G4int sector_id)
{
  G4RotationMatrix *rot_matrix = new G4RotationMatrix();
  G4double rot_x_angle = 0. *deg;
  G4double rot_y_angle = GAGGDetector::map_placement_par[name][1] *deg;
  G4double rot_z_angle = CalculatePhiAngle(name, sector_id) *deg;
  G4cout << "y angle " << rot_y_angle << " z angle " << rot_z_angle << G4endl;
  rot_matrix->rotateY(rot_y_angle);
  rot_matrix->rotateZ(rot_z_angle);

  rot_matrix->print(G4cout);

  G4double x = 0. *mm;
  G4double y = 0. *mm;
  G4double z = GAGGDetector::map_placement_par[name][0] *mm;
  G4ThreeVector pos = (*rot_matrix)*G4ThreeVector(x, y, z);
  G4cout << "pos x " << pos.x() << "pos y " << pos.y() << "pos z " << pos.z() << G4endl;

  G4Transform3D transform(*rot_matrix, pos);

  return transform;
}

//
void GAGGArray::PrintDetectorDimensionInfo()
{
  for(auto it=GAGGDetector::map_gagg_par.begin();it!=GAGGDetector::map_gagg_par.end();it++){
    std::cout << it->first << std::endl;
    for(auto j=0;j<it->second.size();j++){
      std::cout << it->second[j] << " ";
    }
    std::cout <<std::endl;
  }
}