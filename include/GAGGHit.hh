#ifndef GAGGHit_h
#define GAGGHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>
#include "tls.hh"

//
class GAGGHit : public G4VHit
{
public:
  GAGGHit() = default;
  GAGGHit(G4int rid, G4int sid);
  GAGGHit(const GAGGHit&) = default;
  ~GAGGHit() override = default;

  // operators
  GAGGHit& operator=(const GAGGHit&) = default;
  G4bool operator==(const GAGGHit&) const;

  inline void *operator new(size_t);
  inline void  operator delete(void*);

  // methods from base class
  void Draw() override;
  void Print() override;

  void SetRingId(G4int rid) { ring_id = rid; };
  void SetSectorId(G4int sid) { sector_id = sid; };
  void SetEdep(G4double de) { e_dep = de; };
  void AddEdep(G4double de) { e_dep += de; };
  void SetPos(G4ThreeVector xyz) { pos = xyz; };

  G4int GetRingId() const { return ring_id; };
  G4int GetSectorId() const { return sector_id; };
  G4double GetEdep() const { return e_dep; };
  G4ThreeVector GetPos() const { return pos; };

private:
  G4int ring_id = -1; // 1,2
  G4int sector_id = -1; // 
  G4double e_dep;
  G4ThreeVector pos;
};

//
using GAGGHitsCollection = G4THitsCollection<GAGGHit>;
extern G4ThreadLocal G4Allocator<GAGGHit>* GAGGHitAllocator;

//
inline void* GAGGHit::operator new(size_t)
{
  if(!GAGGHitAllocator) GAGGHitAllocator = new G4Allocator<GAGGHit>;
  return (void *) GAGGHitAllocator->MallocSingle();
}

//
inline void GAGGHit::operator delete(void *hit)
{
  GAGGHitAllocator->FreeSingle((GAGGHit*) hit);
}

#endif
