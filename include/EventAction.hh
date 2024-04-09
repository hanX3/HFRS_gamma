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
  void GausEnergy(G4double res);
  bool IfThresholdTrigger(G4double threshold);

private:
  G4int hc_id_csi;
  G4int hc_id_labr3;
  G4int hc_id_gagg;
  G4int hc_id_nai;

  G4double threshold_csi;
  G4double energy_resolution_csi;
  G4double threshold_labr3;
  G4double energy_resolution_labr3;
  G4double threshold_gagg;
  G4double energy_resolution_gagg;
  G4double threshold_nai;
  G4double energy_resolution_nai;

private:
  EventData event_data;

  PrimaryGeneratorAction *primary;
  RootIO *root_io;   
};


#endif
