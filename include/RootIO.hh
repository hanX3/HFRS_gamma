#ifndef RootIO_H
#define RootIO_H 1

#include "Constants.hh"
#include "DataStructure.hh"
#include <globals.hh>

#include <fstream>
#include <map>

#include "TFile.h"
#include "TTree.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class RootIO
{
public:
  RootIO();
  ~RootIO();

// event  
public:  
  void OpenEventFile();
  void CloseEventFile();
  void FillEventTree(EventData& data);

// track  
public:
  void OpenTrackFile();
  void CloseTrackFile();
  void FillTrackTree(TrackData& data);

// step
public:
  void OpenStepFile();
  void CloseStepFile();
  void FillStepTree(StepData& data);

// event 
private:
  EventData event_data;
  TFile* event_file = nullptr;
  TTree* event_tree = nullptr;

// track  
private:
  TrackData track_data;
  TFile* track_file = nullptr;
  TTree* track_tree = nullptr;

// step
private:
  StepData step_data;
  TFile* step_file = nullptr;
  TTree* step_tree = nullptr;

  char file_name[1024];
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
