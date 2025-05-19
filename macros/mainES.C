#include <iostream>
#include <string>

void RunESAnalysis(const std::string& inputFile);
int main(int argc, char* argv[]) {
    // Check if the correct number of arguments were passed
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }
    // Pass the command-line argument to FirstESAnalysis
    std::string inputFilePath = argv[1];  // argv[1] is the first argument passed to the program
    RunESAnalysis(inputFilePath);
    return 0;
}
