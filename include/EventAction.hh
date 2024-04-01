#ifndef B2EventAction_h
#define B2EventAction_h 1

#include "Constants.hh"
#include "DataStructure.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"

class RootIO;
class TFile;
class PrimaryGeneratorAction;

/// Event action class
class EventAction : public G4UserEventAction
{
public:
  EventAction(PrimaryGeneratorAction *pg, RootIO *rio);
  ~EventAction() override;

  void  BeginOfEventAction(const G4Event *) override;
  void  EndOfEventAction(const G4Event *) override;

private:
  void GausCsIEnergy();
  bool IfCsIThresholdTrigger();

private:
  G4int hc_id;

  G4double csi_threshold;
  G4double csi_energy_resolution;

private:
  EventData event_data;

  PrimaryGeneratorAction *primary;
  RootIO *root_io;   
};


#endif
