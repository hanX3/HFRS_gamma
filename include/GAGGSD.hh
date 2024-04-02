#ifndef GAGGSD_h
#define GAGGSD_h 1

#include "Constants.hh"
#include "GAGGHit.hh"

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"

#include <vector>

//
class GAGGSD : public G4VSensitiveDetector
{
public:
  GAGGSD(const G4String &name, const G4String &hits_collection_name);
  ~GAGGSD() override = default;

  // methods from base class
  void Initialize(G4HCofThisEvent *) override;
  G4bool ProcessHits(G4Step *step, G4TouchableHistory *history) override;
  void EndOfEvent(G4HCofThisEvent *) override;

private:
  GAGGHitsCollection *hits_collection;
  G4int hc_id;
};


#endif
