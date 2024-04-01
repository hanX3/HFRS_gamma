// copy froam extended/radioactivedecay/rdecay02

#ifndef BiasedRDPhysics_h
#define BiasedRDPhysics_h 1

#include "G4VPhysicsConstructor.hh"

class G4Radioactivation;

//
class BiasedRDPhysics : public G4VPhysicsConstructor
{
  public: 
    BiasedRDPhysics(G4int verbose = 1);
    BiasedRDPhysics(const G4String& name);
    virtual ~BiasedRDPhysics();

    // This is a dummy method for physics
    virtual void ConstructParticle();
 
    // This method will be invoked in the Construct() method.
    // each physics process will be instantiated and
    // registered to the process manager of each particle type 
    virtual void ConstructProcess();

};

#endif
