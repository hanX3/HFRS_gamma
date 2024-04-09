#ifndef DataStructure_H
#define DataStructure_H 1

#include <globals.hh>
#include <cstring>

//
struct EventData{
  G4long event;
  G4int ring;
  G4int sector;
  G4double e;
  G4double x;
  G4double y;
  G4double z;

  //
  EventData() : 
    event(0),
    ring(0),
    sector(0),
    e(0.), 
    x(0.), y(0.), z(0.)
  {

  }

  //
  void Clear() {
    *this = EventData();
  }
};

//
struct TrackData{
  G4int event_id; 
  G4int track_id;
  G4double e;
  G4double ts;
  char particle_name[128];
  G4double x;
  G4double y;
  G4double z;
  G4double length;

  //
  TrackData() : 
    event_id(-1), 
    track_id(-1), 
    e(0.),
    ts(0.), 
    x(0.), y(0.), z(0.),
    length(0.)
  {
    std::memset(particle_name, '\0', sizeof(particle_name));
  }

  //
  void Clear() {
    *this = TrackData();
  }
};

//
struct StepData{
  G4int event_id;
  G4double de;
  G4int track_id;
  char particle_name[128];
  char detector_name[128];
  G4double pre_x;
  G4double pre_y;
  G4double pre_z;
  G4double pre_total_energy;
  G4double pre_kine_energy;
  G4double post_x;
  G4double post_y;
  G4double post_z;
  G4double post_total_energy;
  G4double post_kine_energy;
  G4double length;
  char process_name[128];

  //
  StepData() : 
    event_id(-1), 
    de(0.), 
    track_id(-1), 
    pre_x(0.), pre_y(0.), pre_z(0.),
    pre_total_energy(0.), pre_kine_energy(0.),
    post_x(0.), post_y(0.), post_z(0.), 
    post_total_energy(0.), post_kine_energy(0.),
    length(0.)
  {
    std::memset(particle_name, '\0', sizeof(particle_name));
    std::memset(detector_name, '\0', sizeof(detector_name));
    std::memset(process_name, '\0', sizeof(process_name));
  }

  //
  void Clear() {
    *this = StepData();
  }
};
#endif
