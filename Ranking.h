#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>

class ranking {
private:
    std::string player;
    int lineNumber = 0;
    

public:


    void operate() {
      
        // opens the NFL Top 300 file
        std::ifstream NFL_Top_300("NFL_TOP_300.txt");
       
        // Verifies that the file can be opened
        if (!NFL_Top_300.is_open()) {
            std::cerr << "Failed to open." << std::endl;
        }

        // Variables to store lines and line counter

        //std::cout << "The consensus NFL Top 300 is: " << std::endl;
        // Loop through each line in the NFL_Top_300 file and prints the consensus NFL top 300

        std::cout << "The consensus NFL top 300 is: " << std::endl;
        while (std::getline(NFL_Top_300, player)) {
            std::cout << player << std::endl; // Print the line
            ++lineNumber; // Increment line counter
        }
        lineNumber = 0; // resets line number



        // closes nfl top 300 file
        NFL_Top_300.close();

    };

};