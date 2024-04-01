#include "EventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "CsISD.hh"
#include "RootIO.hh"

#include "TMath.h"

//
EventAction::EventAction(PrimaryGeneratorAction *pg, RootIO *rio)
: G4UserEventAction(),
  primary(pg),
  root_io(rio)
{
  hc_id = -1;
  csi_threshold = CsIEnergyResolution;
  csi_energy_resolution = CsIEnergyResolution;

  event_data.Clear();
}

//
EventAction::~EventAction()
{}

//
void EventAction::BeginOfEventAction(const G4Event*)
{
  auto sd_manager = G4SDManager::GetSDMpointer();
  hc_id = sd_manager->GetCollectionID("CsISD/CsIHitCollection");
}

//
void EventAction::EndOfEventAction(const G4Event* event)
{
  if((MASK&0b001)==0b001){
    auto hce = event->GetHCofThisEvent();

    // CsI array, ring 9,10,...,24. sector 0,1,...,47
    auto hc = static_cast<CsIHitsCollection*>(hce->GetHC(hc_id));
    for(auto i=0;i<hc->GetSize();i++){
      event_data.event = event->GetEventID();
      event_data.ring = (*hc)[i]->GetRingId();
      event_data.sector = (*hc)[i]->GetSectorId();
      event_data.e = (*hc)[i]->GetEdep();
      event_data.x = (*hc)[i]->GetPos().x();
      event_data.y = (*hc)[i]->GetPos().y();
      event_data.z = (*hc)[i]->GetPos().z();

      GausCsIEnergy();
      if(IfCsIThresholdTrigger()){
        root_io->FillEventTree(event_data);
      }
    }
  }

  // periodic printing
  G4int eventID = event->GetEventID();
  if ( eventID < 10 || eventID % 1000 == 0) {
    G4cout << ">>> Event: " << eventID  << G4endl;
  }
}

//
void EventAction::GausCsIEnergy()
{
  event_data.e = G4RandGauss::shoot(event_data.e, csi_energy_resolution*event_data.e/2.355);
}

//
bool EventAction::IfCsIThresholdTrigger()
{
  if(event_data.e >= csi_threshold) return true;
  else return false;
}
