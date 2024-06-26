#ifndef B2RunAction_h
#define B2RunAction_h 1

#include "Constants.hh"
#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class G4Timer;

class RootIO;

/// Run action class
class RunAction : public G4UserRunAction
{
public:
  RunAction(RootIO *r_io);
  ~RunAction() override;

  void BeginOfRunAction(const G4Run* run) override;
  void EndOfRunAction(const G4Run* run) override;

private:
  G4Timer *timer;
  RootIO *root_io;
};

#endif
