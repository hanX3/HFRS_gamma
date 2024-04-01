#ifndef CsISD_h
#define CsISD_h 1

#include "Constants.hh"
#include "CsIHit.hh"

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"

#include <vector>

//
class CsISD : public G4VSensitiveDetector
{
public:
  CsISD(const G4String &name, const G4String &hits_collection_name);
  ~CsISD() override = default;

  // methods from base class
  void Initialize(G4HCofThisEvent *) override;
  G4bool ProcessHits(G4Step *step, G4TouchableHistory *history) override;
  void EndOfEvent(G4HCofThisEvent *) override;

private:
  CsIHitsCollection *hits_collection;
  G4int hc_id;
};


#endif
