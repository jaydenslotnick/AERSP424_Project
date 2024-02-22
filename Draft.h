#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <map>

class draft {
private:
    std::string player;
    int lineNumber = 0;
    std::vector<std::string> leagueMembers;
    int qbLimit = 0;
    int rbLimit = 0;
    int wrLimit = 0;
    int teLimit = 0;
    int currentRound = 0;
    int roundLimit = 0;
    std::vector<std::string> draftOrder = leagueMembers;
    std::map<std::string, std::vector<std::string>> top300;
    std::string line;
    

public:

    draft(const std::vector<std::string> members) : leagueMembers(members) {}


    void operate() {
      
        
        // opens the NFL Top 300 file
        std::ifstream NFL_Top_300("NFL_TOP_300.csv");
        std::ifstream qb("QB.csv");
        std::ifstream rb("RB.csv");
        std::ifstream wr("WR.csv");
        std::ifstream te("TE.csv");


        // Verifies that the file can be opened
        if (!NFL_Top_300.is_open() || !qb.is_open() || !rb.is_open() || !wr.is_open() || !te.is_open()) {
            std::cerr << "Failed to open." << std::endl;
        }



        while (std::getline(NFL_Top_300, line)) { // Read each line from the file
            std::istringstream iss(line);
            std::vector<std::string> columns;
            std::string column;

            // Split the line into columns
            while (std::getline(iss, column, ',')) { // comma-separated values
                columns.push_back(column);
            }

            if (columns.size() >= 2) { // Ensure there are at least two columns
                // Use the first column as the key and the rest as the value
                std::string key = columns[0];
                columns.erase(columns.begin()); // Remove the first column
                top300[key] = columns;
            }
        }

        // Printing the map
        for (const auto& pair : top300) {
            std::cout << "Player: " << pair.first << ", Position: ";
            for (const auto& column : pair.second) {
                std::cout << column << " ";
            }
            std::cout << std::endl;
        }

        roundLimit = 10;
        // Draft simulation
        for (int round = 1; round <= roundLimit; ++round) {
            std::cout << "Round " << round << ":\n";
            if (round % 2 == 0) {
                std::reverse(draftOrder.begin(), draftOrder.end());
            }
            for (const auto& team : draftOrder) {
                // Use iterators to find the player by rank
                auto it = top300.find(std::to_string(round));
                if (it != top300.end()) {
                    std::string selectedPlayer = it->second.front(); // First element is the player name
                    std::cout << team << " selects: " << selectedPlayer << std::endl;
                    it->second.erase(it->second.begin()); // Remove selected player
                }
                else {
                    std::cerr << "Error: player not found for round " << round << std::endl;
                }
            }
        }







        // not sure how we would implement this
        //std::cout << "Enter QB Limit: " << std::endl;
        //std::cin >> qbLimit;


        //std::cout << "Enter RB Limit: " << std::endl;
        //std::cin >> rbLimit;

        //std::cout << "Enter WR Limit: " << std::endl;
        //std::cin >> wrLimit;

        //std::cout << "Enter TE Limit: " << std::endl;
        //std::cin >> teLimit;

        // Assigns values to the currentRound and roundLimit variables
        //int currentRound = 1;

        //std::cout << "Enter number of rounds: " << std::endl;
        //std::cin >> roundLimit;
































        // End of draft stuff

        // close files
        NFL_Top_300.close();
        qb.close();
        rb.close();
        wr.close();
        te.close();


    };

};