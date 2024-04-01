#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4IonTable.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4RandomDirection.hh"
#include "G4Gamma.hh"

#include "G4Geantino.hh"

//
PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  gamma_energy = 0. *MeV;

  G4int n_of_particles = 1;
  particle_gun = new G4ParticleGun(n_of_particles);
}

//
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particle_gun;
}

//
void PrimaryGeneratorAction::GeneratePrimaries(G4Event *evt)
{
  //
  // GenerateGammaPrimaries(evt);
  GenerateIonPrimaries(evt);
}

//
void PrimaryGeneratorAction::GenerateGammaPrimaries(G4Event *evt)
{
  // G4cout << "Single Gamma Energy " << G4endl;

  UsePointGun();
  SetDirection(1., 1., 1.);
  SetGammaEnergy(1. *MeV);

  // G4cout << "pos x " << gun_pos.x() << " y " << gun_pos.y() << " z " << gun_pos.z() << G4endl;
  // G4cout << "dir x " << gun_dir.x() << " y " << gun_dir.y() << " z " << gun_dir.z() << G4endl;

  particle_gun->SetParticleDefinition(G4Gamma::Definition());
  particle_gun->SetParticlePosition(gun_pos);
  particle_gun->SetParticleEnergy(gamma_energy);
  particle_gun->SetParticleMomentumDirection(gun_dir);

  particle_gun->GeneratePrimaryVertex(evt);
}

//
void PrimaryGeneratorAction::GenerateIonPrimaries(G4Event *evt)
{
  // G4cout << "Ion Gun " << G4endl;

  UsePointGun();
  gun_dir = G4ThreeVector(0., 0., 0.);

  G4int z = 27, a = 60;
  G4double ion_charge = 0. *eplus;
  G4double excit_energy = 0. *keV;

  G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(z, a, excit_energy);
  particle_gun->SetParticleDefinition(ion);
  particle_gun->SetParticleCharge(ion_charge);
  particle_gun->SetParticlePosition(gun_pos);
  particle_gun->SetParticleEnergy(0. *MeV);
  particle_gun->SetParticleMomentumDirection(gun_dir);

  particle_gun->GeneratePrimaryVertex(evt);
}

//
void PrimaryGeneratorAction::UsePointGun()
{
  G4double gun_pos_x = GunPosX;
  G4double gun_pos_y = GunPosY;
  G4double gun_pos_z = GunPosZ;

  G4double gun_pos_sigma_x = GunPosSigmaX;
  G4double gun_pos_sigma_y = GunPosSigmaY;
  G4double gun_pos_sigma_z = GunPosSigmaZ;

  gun_pos = G4ThreeVector(G4RandGauss::shoot(gun_pos_x,gun_pos_sigma_x), G4RandGauss::shoot(gun_pos_y,gun_pos_sigma_y), G4RandGauss::shoot(gun_pos_z,gun_pos_sigma_z));
}

//
void PrimaryGeneratorAction::UseFaceGun()
{
  G4double gun_r = GunFaceR;
  G4double z = GunFaceZ;

  G4double theta = G4RandFlat::shoot(-CLHEP::pi, CLHEP::pi);
  gun_pos = G4ThreeVector(gun_r*std::sin(theta), gun_r*std::cos(theta), z);
}

//
void PrimaryGeneratorAction::SetDirection(G4double x_max, G4double y_max, G4double z_max)
{
  G4double x = G4RandFlat::shoot(-x_max, x_max);
  G4double y = G4RandFlat::shoot(-y_max, y_max);
  G4double z = z_max;
  G4double condizione = std::sqrt(x*x + y*y + z*z);
  x = x/condizione;
  y = y/condizione;
  z = z/condizione;
  
  gun_dir = G4ThreeVector(x, y, z);
}