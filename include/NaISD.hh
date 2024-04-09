#ifndef NaISD_h
#define NaISD_h 1

#include "Constants.hh"
#include "NaIHit.hh"

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"

#include <vector>

//
class NaISD : public G4VSensitiveDetector
{
public:
  NaISD(const G4String &name, const G4String &hits_collection_name);
  ~NaISD() override = default;

  // methods from base class
  void Initialize(G4HCofThisEvent *) override;
  G4bool ProcessHits(G4Step *step, G4TouchableHistory *history) override;
  void EndOfEvent(G4HCofThisEvent *) override;

private:
  NaIHitsCollection *hits_collection;
  G4int hc_id;
};


#endif
