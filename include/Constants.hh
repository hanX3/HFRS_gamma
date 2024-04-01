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

// PPAC
constexpr G4double PPACOuterR = 155. *mm;
constexpr G4double PPACInnerR = 10.  *mm;
constexpr G4double PPACThickness = 70. *mm;

constexpr G4double PPACPosZ = 60. *mm;

// Myler face
constexpr G4double MylarFaceOuterR = 155. *mm;
constexpr G4double MylarFaceInnerR = 10. *mm;
constexpr G4double MylarFaceThickness = 20. *um;
constexpr G4double MylarFacePosZ = (PPACPosZ-PPACThickness/2.-MylarFaceThickness/2.);

// Al face
constexpr G4double AlFaceOuterR = 155. *mm;
constexpr G4double AlFaceInnerR = 10. *mm;
constexpr G4double AlFaceThickness = 20. *um;
constexpr G4double AlFacePosZ = (PPACPosZ-PPACThickness/2.-MylarFaceThickness-AlFaceThickness/2.);

//
constexpr G4int CsIRingNumber = 16;
constexpr G4int CsISectorNumber = 64;
constexpr G4double CsIEnergyResolution = 0.06;
constexpr G4double CsIEnergyThreshold = 20. *keV;


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
