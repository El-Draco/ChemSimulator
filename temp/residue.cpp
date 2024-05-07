// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <vector>
// #include <string>
// #include <unordered_map>

// // Define a struct to store electron configurations
// struct ElectronConfig {
//     std::vector<int> orbitals;
// };

// // Function to parse electron configurations from a file
// std::unordered_map<int, ElectronConfig> parseElectronConfigurations(const std::string& filename) {
//     std::unordered_map<int, ElectronConfig> electronConfigs;

//     std::ifstream file(filename);
//     if (!file.is_open()) {
//         std::cerr << "Failed to open file: " << filename << std::endl;
//         return electronConfigs;
//     }

//     std::string line;
//     int atomicNumber = 1;
//     while (std::getline(file, line)) {
//         std::istringstream iss(line);
//         std::string orbitalStr;

//         // Parse each orbital
//         std::vector<int> orbitals;
//         while (std::getline(iss, orbitalStr, ',')) {
//             orbitals.push_back(std::stoi(orbitalStr));
//         }

//         // Save electron configuration for the current atomic number
//         electronConfigs[atomicNumber++] = {orbitals};
//     }

//     return electronConfigs;
// }

// // Function to get electron configuration for a specific atomic number
// std::vector<int> getElecConfig(int atomicNumber, const std::unordered_map<int, ElectronConfig>& electronConfigs) {
//     if (electronConfigs.find(atomicNumber) != electronConfigs.end()) {
//         return electronConfigs.at(atomicNumber).orbitals;
//     } else {
//         std::cerr << "Electron configuration not found for atomic number " << atomicNumber << std::endl;
//         return {};
//     }
// }

// int main(int argc, char **argv) {
//     // Parse electron configurations from file
//     std::string filename = "residue.txt";
//     std::unordered_map<int, ElectronConfig> electronConfigs = parseElectronConfigurations(filename);

//     // Get electron configuration for a specific atomic number
//     int atomicNumber = atoi(argv[1]);
//     std::vector<int> config = getElecConfig(atomicNumber, electronConfigs);
//     if (!config.empty()) {
//         std::cout << "Electron configuration for atomic number " << atomicNumber << ": ";
//         for (int orbital : config) {
//             std::cout << orbital << " ";
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }
