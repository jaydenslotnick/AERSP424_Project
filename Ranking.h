#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>

class ranking {
private:
    static const int arraySize = 1000; 
    std::string player;
    int lineNumber = 0;
    

public:
    int qbPref;
    int rbPref;
    int wrPref;
    int tePref;


    void operate() {
        // Quarterback preference selection
        // Loop until valid input is provided
        while (true) {
            // Read user input
            std::cout << "Enter preference for quarterback 1 (highest) - 4 (lowest)" << std::endl;
            std::cin >> qbPref;

            // Check if input is within the valid range
            if (qbPref >= 1 && qbPref <= 4) 
            {
                // Input is valid, break out of the loop
                break;
            }
            else 
            {
                // Input is invalid, prompt the user to try again
                std::cout << "Invalid input! Please enter a number between 1 and 4: ";

                // Clear the input stream to remove any remaining characters
                //std::cin.clear();
                // THESE 2 LINES (DIRECTLY ABOVE AND BELOW) WERE ADDED BY CHAT BUT I COMMENTED THEM OUT BC I DON'T KNOW WHAT THEY DO
                // Ignore any remaining characters in the input buffer
                //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        // Output the valid input
        std::cout << "You entered: " << qbPref << " for quarterback preference" << std::endl;


        // Running Back preference selection
        // Loop until valid input is provided
        while (true) {
            // Read user input
            std::cout << "Enter preference for running back 1 (highest) - 4 (lowest)" << std::endl;
            std::cin >> rbPref;

            // Check if input is within the valid range
            if (rbPref >= 1 && rbPref <= 4)
            {
                // Input is valid, break out of the loop
                break;
            }
            else
            {
                // Input is invalid, prompt the user to try again
                std::cout << "Invalid input! Please enter a number between 1 and 4: ";
            }
        }

        // Output the valid input
        std::cout << "You entered: " << rbPref << " for running back preference" << std::endl;

        // Wide Receiver preference selection
        // Loop until valid input is provided
        while (true) {
            // Read user input
            std::cout << "Enter preference for wide receiver 1 (highest) - 4 (lowest)" << std::endl;
            std::cin >> wrPref;

            // Check if input is within the valid range
            if (wrPref >= 1 && wrPref <= 4)
            {
                // Input is valid, break out of the loop
                break;
            }
            else
            {
                // Input is invalid, prompt the user to try again
                std::cout << "Invalid input! Please enter a number between 1 and 4: ";
            }
        }

        // Output the valid input
        std::cout << "You entered: " << wrPref << " for wide receiver preference" << std::endl;

        // Tight End preference selection
        // Loop until valid input is provided
        while (true) {
            // Read user input
            std::cout << "Enter preference for tighet end 1 (highest) - 4 (lowest)" << std::endl;
            std::cin >> tePref;

            // Check if input is within the valid range
            if (tePref >= 1 && tePref <= 4)
            {
                // Input is valid, break out of the loop
                break;
            }
            else
            {
                // Input is invalid, prompt the user to try again
                std::cout << "Invalid input! Please enter a number between 1 and 4: ";

                // Clear the input stream to remove any remaining characters
                //std::cin.clear();
                // THESE 2 LINES (DIRECTLY ABOVE AND BELOW) WERE ADDED BY CHAT BUT I COMMENTED THEM OUT BC I DON'T KNOW WHAT THEY DO
                // Ignore any remaining characters in the input buffer
                //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        // Output the valid input
        std::cout << "You entered: " << tePref << " for tight end preference" << std::endl;


        // opens the NFL Top 300 file
        std::ifstream NFL_Top_300("NFL_TOP_300.txt");
        std::ifstream qb("QB.txt");
        std::ifstream rb("RB.txt");
        std::ifstream wr("WR.txt");
        std::ifstream te("TE.txt");
        

        std::array<std::string, arraySize> emptyTop300;


        // Verifies that the file can be opened
        if (!NFL_Top_300.is_open() || !qb.is_open() || !rb.is_open() || !wr.is_open() || !te.is_open()) {
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


        // This will eventually be the loop that goes through each file and assigns preferences to each and builds top 300
        while (std::getline(qb, player) && lineNumber < arraySize) {
            std::cout << player << std::endl; // Print the line
            emptyTop300[lineNumber] = player; // Store the line in the array
            ++lineNumber; // Increment line counter
        }


        // closes nfl top 300 file
        NFL_Top_300.close();
        qb.close();
        rb.close();
        wr.close();
        te.close();
    };

};