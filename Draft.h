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
    int tempPlayer;

    std::vector<std::pair<std::string, std::vector<std::string>>> top300;
    std::string line;
    std::string ownTeam;

    // create a map of maps to store each drafters picks
        // use bool to make sure the player is only listed once per team
    std::map<std::string, std::map<std::string, bool>> teamPlayerMap;

public:

    draft(const std::vector<std::string>& members) : leagueMembers(members) 
    {
        for (const auto& team : leagueMembers)
        {
            teamPlayerMap[team] = std::map<std::string, bool>();
        }
    }

    std::vector<std::string> draftOrder = leagueMembers;

    void operate() {

        std::cout << "" << std::endl;
        std::cout << "Enter your Team: " << std::endl;
        std::cin >> ownTeam;
        std::cout << "" << std::endl;

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


        // copies the map into the top300
        std::string line;
        while (std::getline(NFL_Top_300, line)) {
            std::istringstream iss(line);
            std::vector<std::string> columns;
            std::string column;

            // Split the line into columns
            while (std::getline(iss, column, ',')) {
                columns.push_back(column);
            }

            if (columns.size() >= 2) {
                // Use the first column as the player name and the rest as their information
                top300.emplace_back(columns[0], std::vector<std::string>(columns.begin() + 1, columns.end()));
            }
        }

        std::cout << "Enter Round Limit" << std::endl;
        std::cin >> roundLimit;
        std::cout << "\n";



        // Draft simulation
        for (int round = 1; round <= roundLimit; ++round) {
            std::cout << "\nRound " << round << ":\n";
            if (round % 2 == 0) {
                std::reverse(draftOrder.begin(), draftOrder.end());
            }
            for (const auto& team : draftOrder) {
                int teamIndex = 0;

                if (team == ownTeam) {
                    std::cout << "" << std::endl;

                    std::cout << "Top 10 players remaining: " << std::endl;

                    for (int i = 0; i < 10; ++i) {
                        std::cout << i+1 << ". " << top300[i].first << top300[i].second[0] << std::endl;
                    }

                    std::cout << "" << std::endl;
                    std::cout << "Enter desired player (number only): " << std::endl;
                    std::cin >> tempPlayer;
                    std::cout << team << " selects: " << top300[tempPlayer - 1].first << std::endl;
                    teamPlayerMap[team][top300[tempPlayer - 1].first] = true;
                    top300.erase(top300.begin() + tempPlayer - 1);
                }

                else {
                    // Use iterators to find the player by rank
                    auto it = top300.begin();
                    if (it != top300.end()) {
                        std::string selectedPlayer = it->first; // First element is the player name
                        std::cout << team << " selects: " << selectedPlayer << std::endl;
                        teamPlayerMap[team][selectedPlayer] = true;   // updates the team map for each team
                        top300.erase(it);
                    }
                    else {
                        std::cerr << "Error: player not found for round " << round << std::endl;
                    }
                }
                ++teamIndex;
            }
            std::cout << std::endl;     // used to make output nicer and more read-able
        }

        // output each drafters team
        std::cout << "\nTeam List\n" << std::endl;
        for (const auto& teamEntry : teamPlayerMap)
        {
            std::cout << "Team: " << teamEntry.first << std::endl;          // outputs team name
            for (const auto& playerEntry : teamEntry.second)
            {
                std::cout << playerEntry.first << std::endl;            // outputs team players
            }
            std::cout << std::endl;     // used to make output nicer and more read-able
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