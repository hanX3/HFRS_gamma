#include "NaIArray.hh"
#include "NaIDetector.hh"

#include <cmath>
#include "TString.h"

//
NaIArray::NaIArray(G4LogicalVolume *log)
: exp_hall_log(log)
{
  nai_numbers = 0;

  for(auto it=NaIDetector::map_name_to_sectors.begin();it!=NaIDetector::map_name_to_sectors.end();it++){
   map_name_to_d_phi[it->first] = 360./it->second;
   nai_numbers += it->second;
  }

  for(auto it=map_name_to_d_phi.begin();it!=map_name_to_d_phi.end();it++){
    G4cout << "name " << it->first << " d_phi " << it->second << G4endl;
  }
  
  //
  G4NistManager *nist_manager = G4NistManager::Instance();

  nai_mat = nist_manager->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  
  PrintDetectorDimensionInfo();
}

//
NaIArray::~NaIArray()
{

}

//
void NaIArray::Construct()
{
  std::vector<NaIDetector*>::iterator it = v_nai_detector.begin();
  // clear all elements from the array
  for(;it!=v_nai_detector.end();it++) delete *it;
  v_nai_detector.clear();

  std::map<G4int, G4int> map_i2ring;
  std::map<G4int, G4int> map_i2sector;
  std::map<G4int, G4String> map_i2name;
  int ii = 0;
  for(auto it=NaIDetector::map_name_to_ring_id.begin();it!=NaIDetector::map_name_to_ring_id.end();it++){
    for(int j=0;j<NaIDetector::map_name_to_sectors[it->first];j++){
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

  for(int i=0;i<nai_numbers;i++){
    v_nai_detector.push_back(new NaIDetector(exp_hall_log));
    v_nai_detector[i]->SetName(map_i2name[i]);
    v_nai_detector[i]->SetRingId(map_i2ring[i]);
    v_nai_detector[i]->SetSectorId(map_i2sector[i]);
  }

  for(it=v_nai_detector.begin();it!=v_nai_detector.end();it++){
    (*it)->ConstructNaIDetector(NaIDetector::map_nai_par[(*it)->GetName()], nai_mat);
    (*it)->PlaceNaIDetector(CalculatePlacement((*it)->GetName(), (*it)->GetSectorId()));
  }
}

//
void NaIArray::MakeSensitive(NaISD *nai_sd)
{
  std::vector<NaIDetector*>::iterator it = v_nai_detector.begin();
  for(;it!=v_nai_detector.end();it++){
     (*it)->GetLog()->SetSensitiveDetector(nai_sd);
  }
}

//
G4Transform3D NaIArray::CalculatePlacement(G4String name, G4int sector_id)
{
  G4RotationMatrix *rot_matrix = new G4RotationMatrix();
  G4double rot_x_angle = 0. *deg;
  G4double rot_y_angle = NaIDetector::map_placement_par[name][1] *deg;
  G4double rot_z_angle = map_name_to_d_phi[name]*sector_id *deg;
  G4cout << "y angle " << rot_y_angle << " z angle " << rot_z_angle << G4endl;
  rot_matrix->rotateY(rot_y_angle);
  rot_matrix->rotateZ(rot_z_angle);

  rot_matrix->print(G4cout);

  G4double x = 0. *mm;
  G4double y = 0. *mm;
  G4double z = NaIDetector::map_placement_par[name][0] *mm;
  G4ThreeVector pos = (*rot_matrix)*G4ThreeVector(x, y, z);
  G4cout << "pos x " << pos.x() << "pos y " << pos.y() << "pos z " << pos.z() << G4endl;

  G4Transform3D transform(*rot_matrix, pos);

  return transform;
}

//
void NaIArray::PrintDetectorDimensionInfo()
{
  for(auto it=NaIDetector::map_nai_par.begin();it!=NaIDetector::map_nai_par.end();it++){
    std::cout << it->first << std::endl;
    for(auto j=0;j<it->second.size();j++){
      std::cout << it->second[j] << " ";
    }
    std::cout <<std::endl;
  }
}