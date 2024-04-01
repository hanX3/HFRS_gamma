#ifndef CsIHit_h
#define CsIHit_h 1

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
class CsIHit : public G4VHit
{
public:
  CsIHit() = default;
  CsIHit(G4int rid, G4int sid);
  CsIHit(const CsIHit&) = default;
  ~CsIHit() override = default;

  // operators
  CsIHit& operator=(const CsIHit&) = default;
  G4bool operator==(const CsIHit&) const;

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
  G4int ring_id = -1; // 8,9,...,23
  G4int sector_id = -1; // 0,1,...,47
  G4double e_dep;
  G4ThreeVector pos;
};

//
using CsIHitsCollection = G4THitsCollection<CsIHit>;
extern G4ThreadLocal G4Allocator<CsIHit>* CsIHitAllocator;

//
inline void* CsIHit::operator new(size_t)
{
  if(!CsIHitAllocator) CsIHitAllocator = new G4Allocator<CsIHit>;
  return (void *) CsIHitAllocator->MallocSingle();
}

//
inline void CsIHit::operator delete(void *hit)
{
  CsIHitAllocator->FreeSingle((CsIHit*) hit);
}

#endif
