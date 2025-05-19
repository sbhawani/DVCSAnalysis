#include "ESAnalysis.h"

ESAnalysis::ESAnalysis()
    : fisLightWeight(false), fIsMC(false), fEvent(nullptr), fTrack(nullptr),
      fEventCuts(nullptr),
      fTrackCutsElectron(nullptr) {
  std::cout << "Performing ESAnalysis Yey!" << std::endl;
}

ESAnalysis::ESAnalysis(bool isMC)
    : fisLightWeight(false), fIsMC(isMC), fEvent(nullptr), fTrack(nullptr),
      fEventCuts(nullptr),
      fTrackCutsElectron(nullptr) {}

ESAnalysis::~ESAnalysis() { // Destructor (clean up if necessary)
  delete fEvent;
  delete fTrack;
  delete fTrackCutsElectron;
  // delete fTrack;
}

void ESAnalysis::UserCreateOutputObjects() {

  if (!fEventCuts) {
    std::cerr << "No Event cuts." << std::endl;
  } else {
    if (!fTaskManager) {
      std::cerr << "Error: Task manager is not set!" << std::endl;
      return;
    }

    fHistMomentum = new TH1F("fHistMomentum", "Momentum Distribution", 100, 0, 10);

    fTree = new TTree("EventTree", "ES Event Data");
    fTree->Branch("Momentum", &fMomentum, "Momentum/F");

    // Ensure the output structure is well-defined
    fTaskManager->CreateHistogramList("analysis_output.root",
                                      "ES_Histograms");
    fTaskManager->AddHistogram("ES_Histograms", fHistMomentum);

    fTaskManager->AddTree("EventTree", fTree);
  }
  fTrack = new Tracks();
}

void ESAnalysis::UserExec(Event &event) {
  if (!event.isValid()) {
    std::cerr << "No events lol." << std::endl;
  } else {
    for (const auto &particle : event.getDetParticles()) {

      fTrack->SetTrack(particle); // is where we set tracks and get possible
                                  // track properties;
      // here we can ask if the particle is of our interest based on the track
      // cuts we have defined
      //std::cout << "Track momentum " << fTrack->GetP() << std::endl;
      //if (fTrackCutsPhoton->isSelected(fTrack)) {
      //  std::cout << "Its a photon" << std::endl;
      //}
      if (fTrackCutsElectron->isSelected(fTrack)) {
        //std::cout << "Its an electron" << std::endl;
        fMomentum = fTrack->GetP();
        //FillTree();
        //FillHistogram();        
      }
      //if (fTrackCutsProton->isSelected(fTrack)) {
      //  std::cout << "Its a proton" << std::endl;
      //}

      // particle.print();
    }
  }
}

// we may use some examples like this
void ESAnalysis::FillTree() {
  if (fTree) {
    fTree->Fill(); // Store the current momentum into the tree
  }
}

void ESAnalysis::FillHistogram() {
  if (fHistMomentum) {
    fHistMomentum->Fill(fMomentum); // Fill histogram with the momentum
  }
}