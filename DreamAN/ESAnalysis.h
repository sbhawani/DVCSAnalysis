#ifndef ESANALYSIS_H
#define ESANALYSIS_H
// this task related includes

#include "AnalysisTask.h"
#include "Event.h"
#include "Tracks.h"
#include "EventCuts.h"
#include "TrackCuts.h"
#include <TObject.h>
#include <iostream>
#include "AnalysisTaskManager.h"  // Add the include for the complete definition


class ESAnalysis : public AnalysisTask {
public:
  ESAnalysis(); // Declare the constructor
  ESAnalysis(bool isMC); // Declare the constructor
  virtual ~ESAnalysis();
  virtual void UserCreateOutputObjects() ;//override;
  void UserExec(Event &event) ;//override;
  virtual void Terminate(Option_t *) {};

  void SetEventCuts(EventCuts *evtCuts) { fEventCuts = evtCuts; };
  //void SetPhotonCuts(TrackCuts *trkCuts) {fTrackCutsPhoton = trkCuts;};
  void SetElectronCuts(TrackCuts *trkCuts) {fTrackCutsElectron = trkCuts;};
  //void SetProtonCuts(TrackCuts *trkCuts) {fTrackCutsProton = trkCuts;};


private:
  ESAnalysis(const ESAnalysis &task);
  ESAnalysis &operator=(const ESAnalysis &task);
  bool fisLightWeight;  
  bool fIsMC;           
  Event *fEvent;        
  Tracks *fTrack;               
  EventCuts *fEventCuts; 
  //TrackCuts *fTrackCutsPhoton; 
  TrackCuts *fTrackCutsElectron; 
  //TrackCuts *fTrackCutsProton; 

  TH1F* fHistMomentum;
  TTree* fTree;
  float fMomentum;

  void FillTree();
  void FillHistogram();
};
#endif // ESANALYSIS_H
