#ifndef B2PrimaryGeneratorAction_h
#define B2PrimaryGeneratorAction_h 1

#include "Constants.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

#include "G4ThreeVector.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"

//
class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();
  ~PrimaryGeneratorAction() override;

  void GeneratePrimaries(G4Event *evt) override;

  G4ParticleGun *GetParticleGun() {return particle_gun;}

  // Set methods
  void SetRandomFlag(G4bool );

public:
  G4ThreeVector gun_pos;
  G4ThreeVector gun_dir;

  void UsePointGun();
  void UseFaceGun();
  void SetDirection(G4double x_max, G4double y_max, G4double z_max); // (-pi,pi)
  void SetDirectionPlusZ();

  void SetGammaEnergy(G4double e) { gamma_energy = e; };

private:
  inline void GenerateGammaPrimaries(G4Event *evt);
  inline void GenerateIonPrimaries(G4Event *evt);


private:
  G4double gamma_energy;

private:
  G4ParticleGun *particle_gun = nullptr;
};


#endif
