#include "./../DreamAN/ESAnalysis.h"
#include "./../DreamAN/EventProcessor.h"
#include "./../DreamAN/AnalysisTaskManager.h"
#include <iostream>

void RunESAnalysis(const std::string& inputFile) {
    bool testFile = true; // just to see if file exists;
    if (inputFile == "") {
        std::cerr << "Usage: " << inputFile << " <input_file>" << std::endl;
        return;
    }

    if(testFile){
    std::string fileName = "/cache/clas12/rg-k/production/recon/fall2018/torus+1/6535MeV/pass2/v0/dst/recon/005958/rec_clas_005958.evio.00165-00169.hipo";
    clas12::clas12reader reader(fileName);
    
    std::cout << "File name: " << reader.getFilename() << std::endl;
    std::cout << "Is file open: " << reader.isOpen() << std::endl;
    
    if (!reader.isOpen()) {
        std::cerr << "Failed to open file." << std::endl;
        return ;
    }
    }

    AnalysisTaskManager taskManager;

    //TrackCuts *PhotonCuts =TrackCuts::PhotonCuts();
    //PhotonCuts->SetChargeCut(0);
    //PhotonCuts->SetPIDCut(22,3.0); // set pdg and the chisquared

    TrackCuts *ElectronCuts =TrackCuts::ElectronCuts();
    ElectronCuts->SetChargeCut(-1);
    ElectronCuts->SetPIDCut(11,3.0); // set pdg and the chisquared

    //TrackCuts *ProtonCuts =TrackCuts::ProtonCuts();
    //ProtonCuts->SetChargeCut(1);
    //ProtonCuts->SetPIDCut(2212,3.0); // set pdg and the chisquared


    /// here we call our task and set the track event cut settings
    std::unique_ptr<ESAnalysis> EStask = std::make_unique<ESAnalysis>();

    EStask->SetElectronCuts(ElectronCuts);

    /// pass the task to the task manager to do the laborious stuff
    taskManager.AddTask(std::move(EStask)); // Use smart pointer to memory stuff
    std::cout << "adding the task in the ES analysis" << std::endl;
   
    std::cout << "Going to Event Processor" << std::endl;
    EventProcessor processor(inputFile, taskManager);
    std::cout << "Event Proceesing is in progress " << std::endl;
    processor.ProcessEvents(); // Start event loop

    //taskManager.SaveOutput();
}
