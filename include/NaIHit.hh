#ifndef NaIHit_h
#define NaIHit_h 1

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
class NaIHit : public G4VHit
{
public:
  NaIHit() = default;
  NaIHit(G4int rid, G4int sid);
  NaIHit(const NaIHit&) = default;
  ~NaIHit() override = default;

  // operators
  NaIHit& operator=(const NaIHit&) = default;
  G4bool operator==(const NaIHit&) const;

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
using NaIHitsCollection = G4THitsCollection<NaIHit>;
extern G4ThreadLocal G4Allocator<NaIHit>* NaIHitAllocator;

//
inline void* NaIHit::operator new(size_t)
{
  if(!NaIHitAllocator) NaIHitAllocator = new G4Allocator<NaIHit>;
  return (void *) NaIHitAllocator->MallocSingle();
}

//
inline void NaIHit::operator delete(void *hit)
{
  NaIHitAllocator->FreeSingle((NaIHit*) hit);
}

#endif
