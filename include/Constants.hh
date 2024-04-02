#ifndef Constants_h
#define Constants_h 1

#include "globals.hh"
#include "G4SystemOfUnits.hh"

#define DATAPATH "../data"  // no "/"

// 0b0001 event data
// 0b0010 track data
// 0b0100 step data
constexpr G4int MASK = 0b001;

constexpr G4double WorldSizeX = 2. *m;
constexpr G4double WorldSizeY = 2. *m;
constexpr G4double WorldSizeZ = 2. *m;

// CsI array
constexpr G4int CsIRingNumber = 16;
constexpr G4int CsISectorNumber = 64;
constexpr G4double CsIEnergyResolution = 0.06;
constexpr G4double CsIEnergyThreshold = 20. *keV;

// LaBr3 array
constexpr G4int LaBr3RingNumber = 2;
constexpr G4double LaBr3EnergyResolution = 0.02;
constexpr G4double LaBr3EnergyThreshold = 20. *keV;

// GAGG array
constexpr G4int GAGGRingNumber = 3;
constexpr G4double GAGGEnergyResolution = 0.04;
constexpr G4double GAGGEnergyThreshold = 20. *keV;

// Point Gun
constexpr G4double GunPosX = 0. *mm;
constexpr G4double GunPosY = 0. *mm;
constexpr G4double GunPosZ = 0. *mm;
constexpr G4double GunPosSigmaX = 0. *mm;
constexpr G4double GunPosSigmaY = 0. *mm;
constexpr G4double GunPosSigmaZ = 0. *mm;

// Face Gun
constexpr G4double GunFaceR = 10. *mm;
constexpr G4double GunFaceZ = 0. *mm;

#endif
