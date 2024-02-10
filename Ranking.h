#include <iostream>
#include <fstream>
#include <string>


void operate() {

    // opens the NFL Top 300 file
    std::ifstream NFL_Top_300("NFL_TOP_300.txt");


    // Verifies that the file can be opened
    if (!NFL_Top_300.is_open()) {
        std::cerr << "Failed to open the NFL_Top_300." << std::endl;
    }

    // Variables to store lines and line counter
    std::string line;
    int lineNumber = 0;

    std::cout << "The consensus NFL Top 300 is: " << std::endl;
    // Loop through each line in the NFL_Top_300 file and prints the consensus NFL top 300
    while (std::getline(NFL_Top_300, line)) {
        std::cout << line << std::endl; // Print the line
        ++lineNumber; // Increment line counter
    }



    // closes nfl top 300 file
    NFL_Top_300.close();
};