#include "SteppingAction.hh"
#include "RootIO.hh"

#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
SteppingAction::SteppingAction(DetectorConstruction* dc, RootIO* rio)
  :G4UserSteppingAction(),
   detector_construction(dc),
   root_io(rio)
{
  step_data.Clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void SteppingAction::UserSteppingAction(const G4Step* step)
{
  if((MASK&0b100)==0b100){
    step_data.event_id = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    step_data.de = step->GetTotalEnergyDeposit();
    step_data.track_id = step->GetTrack()->GetTrackID();
    strcpy(step_data.particle_name, step->GetTrack()->GetDefinition()->GetParticleName());
    strcpy(step_data.detector_name, step->GetTrack()->GetVolume()->GetName());
    step_data.pre_x = step->GetPreStepPoint()->GetPosition().x();
    step_data.pre_y = step->GetPreStepPoint()->GetPosition().y();
    step_data.pre_z = step->GetPreStepPoint()->GetPosition().z();
    step_data.pre_total_energy = step->GetPreStepPoint()->GetTotalEnergy();
    step_data.pre_kine_energy = step->GetPreStepPoint()->GetKineticEnergy();
    step_data.post_x = step->GetPostStepPoint()->GetPosition().x();
    step_data.post_y = step->GetPostStepPoint()->GetPosition().y();
    step_data.post_z = step->GetPostStepPoint()->GetPosition().z();
    step_data.post_total_energy = step->GetPreStepPoint()->GetTotalEnergy();
    step_data.post_kine_energy = step->GetPreStepPoint()->GetKineticEnergy();
    step_data.length = step->GetStepLength();
    strcpy(step_data.process_name, step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName());

    /*
    if(strcmp(step_data.particle_name, "gamma")==0 && step->GetTrack()->GetParentID()==1 && strcmp(step_data.detector_name, "Target")==0){
      root_io->FillStepTree(step_data);
    }
    */
    root_io->FillStepTree(step_data);
  }
}

