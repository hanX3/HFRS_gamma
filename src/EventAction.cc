#include "EventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "CsISD.hh"
#include "LaBr3SD.hh"
#include "GAGGSD.hh"
#include "NaISD.hh"
#include "RootIO.hh"

#include "TMath.h"

//
EventAction::EventAction(PrimaryGeneratorAction *pg, RootIO *rio)
: G4UserEventAction(),
  primary(pg),
  root_io(rio)
{
  hc_id_csi = -1;
  threshold_csi = CsIEnergyThreshold;
  energy_resolution_csi = CsIEnergyResolution;

  hc_id_labr3 = -1;
  threshold_labr3 = LaBr3EnergyThreshold;
  energy_resolution_labr3 = LaBr3EnergyResolution;

  hc_id_gagg = -1;
  threshold_gagg = GAGGEnergyThreshold;
  energy_resolution_gagg = GAGGEnergyResolution;

  hc_id_nai = -1;
  threshold_nai = NaIEnergyThreshold;
  energy_resolution_nai = NaIEnergyResolution;

  event_data.Clear();
}

//
EventAction::~EventAction()
{}

//
void EventAction::BeginOfEventAction(const G4Event*)
{
  auto sd_manager = G4SDManager::GetSDMpointer();
  hc_id_csi = sd_manager->GetCollectionID("CsISD/CsIHitCollection");
  hc_id_labr3 = sd_manager->GetCollectionID("LaBr3SD/LaBr3HitCollection");
  hc_id_gagg = sd_manager->GetCollectionID("GAGGSD/GAGGHitCollection");
  hc_id_nai = sd_manager->GetCollectionID("NaISD/NaIHitCollection");
}

//
void EventAction::EndOfEventAction(const G4Event* event)
{
  if((MASK&0b001)==0b001){
    auto hce = event->GetHCofThisEvent();

    // CsI array, ring 9,10,...,24. sector 0,1,...,47
    auto hc_csi = static_cast<CsIHitsCollection*>(hce->GetHC(hc_id_csi));
    for(auto i=0;i<hc_csi->GetSize();i++){
      event_data.event = event->GetEventID();
      event_data.ring = (*hc_csi)[i]->GetRingId();
      event_data.sector = (*hc_csi)[i]->GetSectorId();
      event_data.e = (*hc_csi)[i]->GetEdep();
      event_data.x = (*hc_csi)[i]->GetPos().x();
      event_data.y = (*hc_csi)[i]->GetPos().y();
      event_data.z = (*hc_csi)[i]->GetPos().z();

      GausEnergy(energy_resolution_csi);
      if(IfThresholdTrigger(threshold_csi)){
        root_io->FillEventTree(event_data);
      }
    }

    // LaBr3 array, ring 1,2. sector 0,1,...
    auto hc_labr3 = static_cast<LaBr3HitsCollection*>(hce->GetHC(hc_id_labr3));
    for(auto i=0;i<hc_labr3->GetSize();i++){
      event_data.event = event->GetEventID();
      event_data.ring = (*hc_labr3)[i]->GetRingId();
      event_data.sector = (*hc_labr3)[i]->GetSectorId();
      event_data.e = (*hc_labr3)[i]->GetEdep();
      event_data.x = (*hc_labr3)[i]->GetPos().x();
      event_data.y = (*hc_labr3)[i]->GetPos().y();
      event_data.z = (*hc_labr3)[i]->GetPos().z();

      GausEnergy(energy_resolution_labr3);
      if(IfThresholdTrigger(threshold_labr3)){
        root_io->FillEventTree(event_data);
      }
    }

    // GAGG array, ring 3,4,5 sector 0,1,...
    auto hc_gagg = static_cast<GAGGHitsCollection*>(hce->GetHC(hc_id_gagg));
    for(auto i=0;i<hc_gagg->GetSize();i++){
      event_data.event = event->GetEventID();
      event_data.ring = (*hc_gagg)[i]->GetRingId();
      event_data.sector = (*hc_gagg)[i]->GetSectorId();
      event_data.e = (*hc_gagg)[i]->GetEdep();
      event_data.x = (*hc_gagg)[i]->GetPos().x();
      event_data.y = (*hc_gagg)[i]->GetPos().y();
      event_data.z = (*hc_gagg)[i]->GetPos().z();

      GausEnergy(energy_resolution_gagg);
      if(IfThresholdTrigger(threshold_gagg)){
        root_io->FillEventTree(event_data);
      }
    }

    // nAi array, ring 25,26 sector 0,1,...
    auto hc_nai = static_cast<NaIHitsCollection*>(hce->GetHC(hc_id_nai));
    for(auto i=0;i<hc_nai->GetSize();i++){
      event_data.event = event->GetEventID();
      event_data.ring = (*hc_nai)[i]->GetRingId();
      event_data.sector = (*hc_nai)[i]->GetSectorId();
      event_data.e = (*hc_nai)[i]->GetEdep();
      event_data.x = (*hc_nai)[i]->GetPos().x();
      event_data.y = (*hc_nai)[i]->GetPos().y();
      event_data.z = (*hc_nai)[i]->GetPos().z();

      GausEnergy(energy_resolution_nai);
      if(IfThresholdTrigger(threshold_nai)){
        root_io->FillEventTree(event_data);
      }
    }
  }

  // periodic printing
  // G4int eventID = event->GetEventID();
  // if ( eventID < 10 || eventID % 1000 == 0) {
  //   G4cout << ">>> Event: " << eventID  << G4endl;
  // }
}

//
void EventAction::GausEnergy(G4double res)
{
  event_data.e = G4RandGauss::shoot(event_data.e, res*event_data.e/2.355);
}

//
bool EventAction::IfThresholdTrigger(G4double threshold)
{
  if(event_data.e >= threshold) return true;
  else return false;
}
