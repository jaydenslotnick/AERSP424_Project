#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <map>

#ifndef DRAFT_H
#define DRAFT_H


class draft {
private:


    std::string player;
    unsigned int lineNumber = 0;
    std::vector<std::string> leagueMembers;
    unsigned int qbLimit = 0;
    unsigned int rbLimit = 0;
    unsigned int wrLimit = 0;
    unsigned int teLimit = 0;
    unsigned int currentRound = 0;
    unsigned int roundLimit = 0;
    unsigned int tempPlayer = 0;
    unsigned int playerCount = 1;
    unsigned char morePlayers = 0;
    unsigned int numPlayers = 0;
    unsigned int defaultPlayers = 10;

    unsigned int qbtaken = 0;
    unsigned int rbtaken = 0;
    unsigned int wrtaken = 0;
    unsigned int tetaken = 0;
    signed int indexHelper = -1;


    // average salaries of starting nfl players in millions
    float qbSalary = 28.2; 
    float rbSalary = 2.7;
    float wrSalary = 10;
    float teSalary = 8;

    // total estimated salary spent on team 
    double totalSalarySpent = 0.0;

    std::vector<std::pair<std::string, std::vector<std::string>>> top300;
    std::string line;
    std::string ownTeam;

    // create a map of maps to store each drafters picks
        // use bool to make sure the player is only listed once per team
    std::map<std::string, std::map<std::string, std::string>> teamPlayerMap;
    std::map<std::string, int> positionLimits;

    std::vector<unsigned int> availablePositions;

    

public:
    static int totalDrafts;

    draft(const std::vector<std::string>& members, int qb, int rb, int wr, int te, int roundLimit) : leagueMembers(members), qbLimit(qb), rbLimit(rb), wrLimit(wr), teLimit(te), roundLimit(roundLimit) 
    {
        for (const auto& team : leagueMembers)
        {
            teamPlayerMap[team] = std::map<std::string, std::string>();
        }
        ++totalDrafts;
        positionLimits = { {"QB",qbLimit}, {"RB",rbLimit}, {"WR", wrLimit}, {"TE", teLimit} };

       // availablePositions.resize(roundLimit, 0xFFFFFFFF);
    }

    std::vector<std::string> draftOrder = leagueMembers;


    // displays the players available
    void displayTopPlayers(int numPlayers) {
        std::cout << "Top " << numPlayers << " players remaining: " << std::endl;
        for (int i = 0; i < numPlayers; ++i) {
            std::cout << i + 1 << ". " << top300[i].first << ", " << top300[i].second[0] << std::endl;
        }
    }

    // asks the user whether they would like to see more top players available
    void promptForMorePlayers() {
        std::cout << "Do you wish to see more players? (y/n)" << std::endl;
        std::cin >> morePlayers;
    }


    // receives user input for the pick that they want
    void getUserPick() {
        std::cout << "It is your turn to pick!" << std::endl;
        std::cout << "Enter desired player (number only): " << std::endl;
        std::cin >> tempPlayer;
        std::cout << "" << std::endl;

        std::cout << playerCount << ". " << ownTeam << " selects: " << top300[tempPlayer + indexHelper].first << ", " << top300[tempPlayer + indexHelper].second[0] << std::endl;
        teamPlayerMap[ownTeam][top300[tempPlayer + indexHelper].first] = top300[tempPlayer + indexHelper].second[0];
        top300.erase(top300.begin() + tempPlayer + indexHelper);
        ++playerCount;
    }


    // simulates the draft with "robots" picking at spots other than the user
    void draftSimulation(int round) {
        // Draft simulation
        for (int round = 1; round <= roundLimit; ++round) {
            std::cout << "\nRound " << round << ":\n";

            // reverses order to represent a snake draft
            if (round % 2 == 0) {
                std::reverse(draftOrder.begin(), draftOrder.end());
            }

            // Goes through draft logic for each team
            for (const auto& team : draftOrder) {
                int teamIndex = 0;

                // goes user control over their own draft slot
                if (team == ownTeam) {
                    std::cout << "" << std::endl;


                    displayTopPlayers(defaultPlayers);


                    // asks users if they want to see any more players
                    std::cout << "" << std::endl;
                    promptForMorePlayers();

                    // will run until user does not want to see any more new players
                    while (morePlayers == 'y')
                    {
                        std::cout << "Enter number of players you would like to see: " << std::endl;
                        std::cin >> numPlayers;
                        std::cout << "Top " << numPlayers << " players remaining: " << std::endl;

                        for (int i = 0; i < numPlayers; ++i) {
                            std::cout << i + 1 << ". " << top300[i].first << ", " << top300[i].second[0] << std::endl;
                        }
                        std::cout << "" << std::endl;
                        std::cout << "Do you wish to see more players? (y/n)" << std::endl;
                        std::cin >> morePlayers;
                    }

                    // gets user inputted pick
                    std::cout << "" << std::endl;
                    std::cout << "It is your turn to pick!" << std::endl;
                    std::cout << "Enter desired player (number only): " << std::endl;
                    std::cin >> tempPlayer;
                    std::cout << "" << std::endl;
                   // takePosition(top300[tempPlayer + indexHelper].second[0]);

                    std::cout << playerCount << ". " << team << " selects: " << top300[tempPlayer + indexHelper].first << ", " << top300[tempPlayer + indexHelper].second[0] << std::endl;
                    teamPlayerMap[team][top300[tempPlayer + indexHelper].first] = top300[tempPlayer + indexHelper].second[0];
                    top300.erase(top300.begin() + tempPlayer + indexHelper);



                    // increases overall pick nymber
                    ++playerCount;
                }

                else {
                    // Use iterators to find the player by rank
                    auto it = top300.begin();
                    if (it != top300.end()) {
                        std::string& selectedPlayer = it->first; // First element is the player name
                        std::cout << playerCount << ". " << team << " selects: " << selectedPlayer << ", " << it->second[0] << std::endl;
                        teamPlayerMap[team][selectedPlayer] = it->second[0];   // updates the team map for each team
                        top300.erase(it);
                        ++playerCount;
                       // takePosition(it->second[0]);
                    }
                    else {
                        std::cerr << "Error: player not found for round " << round << std::endl;
                    }
                }
                ++teamIndex;
            }
            std::cout << std::endl;     // used to make output nicer and more read-able
        }
    }




    // outputs the teams picks at the end of the draft
    void outputTeamPicks() {
        // output each drafters team
        std::cout << "\nTeam List\n" << std::endl;
        for (const auto& teamEntry : teamPlayerMap)
        {
            totalSalarySpent = 0;

            std::cout << "Team: " << teamEntry.first << std::endl; // outputs team name
            for (const auto& playerEntry : teamEntry.second)
            {
                const std::string& position = playerEntry.second;
                if (position == "QB")
                {
                    std::cout << position << ": " << playerEntry.first << std::endl;
                    totalSalarySpent += qbSalary;
                }
            }
            for (const auto& playerEntry : teamEntry.second)
            {
                const std::string& position = playerEntry.second;
                if (position == "RB")
                {
                    std::cout << position << ": " << playerEntry.first << std::endl;
                    totalSalarySpent += rbSalary;
                }
            }
            for (const auto& playerEntry : teamEntry.second)
            {
                const std::string& position = playerEntry.second;
                if (position == "WR")
                {
                    std::cout << position << ": " << playerEntry.first << std::endl;
                    totalSalarySpent += wrSalary;
                }
            }
            for (const auto& playerEntry : teamEntry.second)
            {
                const std::string& position = playerEntry.second;
                if (position == "TE")
                {
                    std::cout << position << ": " << playerEntry.first << std::endl;
                    totalSalarySpent += teSalary;
                }
            }
            std::cout << "Total estimated salary: $" << totalSalarySpent << " million" << std::endl;
            std::cout << std::endl;     // used to make output nicer and more read-able


            // Output number of players taken per position
            std::cout << "Number of players taken per position:" << std::endl;
           // std::cout << "QB: " << countPlayersTaken("QB") << std::endl;
           // std::cout << "RB: " << countPlayersTaken("RB") << std::endl;
           // std::cout << "WR: " << countPlayersTaken("WR") << std::endl;
           // std::cout << "TE: " << countPlayersTaken("TE") << std::endl;
        
        }
    }

    //// Function to mark a position as taken in a specific round
    //void takePosition(const std::string& position) {
    //    if (position == "QB") {
    //        availablePositions[0] &= ~(1 << 0); // Clear bit representing QB position
    //    }
    //    else if (position == "RB") {
    //        availablePositions[1] &= ~(1 << 1); // Clear bit representing RB position
    //    }
    //    else if (position == "WR") {
    //        availablePositions[2] &= ~(1 << 2); // Clear bit representing WR position
    //    }
    //    else if (position == "TE") {
    //        availablePositions[3] &= ~(1 << 3); // Clear bit representing TE position
    //    }
    //}
    //
    //// Function to count the number of players taken for a given position
    //int countPlayersTaken(const std::string& position) {
    //    int count = 0;
    //    for (int round = 0; round <= roundLimit-1; ++round) {
    //        if (position == "QB") {
    //            count += ((availablePositions[round] & (1 << 0)) != 0);
    //        }
    //        else if (position == "RB") {
    //            count += ((availablePositions[round] & (1 << 1)) != 0);
    //        }
    //        else if (position == "WR") {
    //            count += ((availablePositions[round] & (1 << 2)) != 0);
    //        }
    //        else if (position == "TE") {
    //            count += ((availablePositions[round] & (1 << 3)) != 0);
    //        }
    //    }
    //    return count;
    //}


    // operates and runs the functions above
    void operate() {

        std::cout << "" << std::endl;
        std::cout << "Enter your Team (name): " << std::endl;
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
        draftSimulation(roundLimit);
        outputTeamPicks();


        // close files
        NFL_Top_300.close();
        qb.close();
        rb.close();
        wr.close();
        te.close();


    }


};
#endif
