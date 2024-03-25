#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <random>
#include <limits>

#ifndef DRAFT_H
#define DRAFT_H


class draft {
private:

    std::string draftFileName;      // stores the name of the chosen draft CSV file
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
    std::map<std::string, std::map<std::string, std::string>> teamPlayerMap;
    std::map<std::string, int> positionLimits;

    std::vector<unsigned int> availablePositions;

    int pick = 0;

    // containers for positional limits for each team
    std::map<std::string, int> qbLimitContainer; // Key: Team name, Value: Count of QBs taken
    std::map<std::string, int> rbLimitContainer; // Key: Team name, Value: Count of RBs taken
    std::map<std::string, int> wrLimitContainer; // Key: Team name, Value: Count of WRs taken
    std::map<std::string, int> teLimitContainer; // Key: Team name, Value: Count of TEs taken
    int qbcount = 0;
    int rbcount = 0;
    int wrcount = 0;
    int tecount = 0;


    bool validChar = false;

    

public:
    static int totalDrafts;

    draft(const std::vector<std::string>& members, int qb, int rb, int wr, int te, int roundLimit, int draftType) : leagueMembers(members), qbLimit(qb), rbLimit(rb), wrLimit(wr), teLimit(te), roundLimit(roundLimit) 
    {
        for (const auto& team : leagueMembers)
        {
            teamPlayerMap[team] = std::map<std::string, std::string>();
        }
        ++totalDrafts;
        positionLimits = { {"QB",qbLimit}, {"RB",rbLimit}, {"WR", wrLimit}, {"TE", teLimit} };
        
        // Determine the draft CSV file to use based on the chosen draft type
        switch (draftType)
        {
        case 1:
            draftFileName = "NFL_Top_300.csv";
            break;
        case 2:
            draftFileName = "PPR_Top300.csv";
            break;
        case 3: 
            draftFileName = "Half_PPR_Top300.csv";
            break;
        default:
            std::cerr << "Invalid draft type." << std::endl;
            break;
        }
        
        // resizes positional limit containers based on number of league members
        for (const auto& member : members) {
            qbLimitContainer[member] = 0;
            rbLimitContainer[member] = 0;
            wrLimitContainer[member] = 0;
            teLimitContainer[member] = 0;
        }

       
    }

    std::vector<std::string> draftOrder = leagueMembers;

    // Display top players with default number
    void displayTopPlayers() {
        displayTopPlayers(defaultPlayers);
    }


    // displays the players available
    void displayTopPlayers(int numPlayers) {
        std::cout << "Top " << numPlayers << " players remaining: " << std::endl;
        for (int i = 0; i < numPlayers; ++i) {
            std::cout << i + 1 << ". " << top300[i].first << ", " << top300[i].second[0] << std::endl;
        }
    }

    // asks the user whether they would like to see more top players available
    void promptForMorePlayers() {


        // asks user if they want to see more players, forces them to enter y or n or Y or N
        while (validChar == false)
        {

            // prompts user
            std::cout << "Do you wish to see more players? (y/n)" << std::endl;
            std::cin >> morePlayers;


            // condition if they enter the wrong item, the loop will run again
            if (morePlayers != 'y' && morePlayers != 'n' && morePlayers != 'Y' && morePlayers != 'N')
            {
                std::cout << "\nInvalid input. Please enter 'y' or 'n' \n" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            // if the user enters y or Y, the loop will run again to continue to see if they want more players
            else if (morePlayers == 'y' || morePlayers == 'Y')
            {
                while (true)
                {
                    std::cout << "Enter number of players you would like to see: " << std::endl;
                    std::cin >> numPlayers;
                    if (std::cin.fail() || numPlayers < 0)
                    {
                        std::cout << "Invalid input. Please enter a positive integer." << std::endl;
                        std::cin.clear(); // clears the invalid input
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clears the invalid input

                    }
                    else
                    {
                        char nextChar;
                        if (std::cin.get(nextChar) && nextChar != '\n') 
                        {
                            std::cout << "Invalid input. Please enter an integer." << std::endl;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard remaining input
                        }
                        else 
                        {
                            // Input is a valid integer
                            break;
                        }
                    }
                }

                displayTopPlayers(numPlayers);
                validChar = false;
            }

            // breaks while loop, this is if the user enters n or N
            else
            {
                validChar = true;
            }
        }

        // resets the validChar variable so the next time the function is called, the while loop will run
        validChar = false;

    }

    // Function to update the count of positions taken by a team
    void updatePositionCount(const std::string& team, const std::string& position) 
    {
      
        // each time a position is picked for a team, it'll update the container for each team to 
        // keep track of how many of each position they have taken
        if (position == "QB") {
            ++qbLimitContainer[team];
        }
        else if (position == "RB") {
            ++rbLimitContainer[team];
        }
        else if (position == "WR") {
            ++wrLimitContainer[team];
        }
        else if (position == "TE") {
            ++teLimitContainer[team];
        }

    }



    // receives user input for the pick that they want
    void getUserPick() {
        std::cout << "It is your turn to pick!" << std::endl;

        int tempPlayer;

        do {
            std::cout << "Enter desired player (number only): " << std::endl;
            std::cin >> tempPlayer;
            std::cout << "" << std::endl;

            if (std::cin.fail() || tempPlayer <= 0)
            {
                std::cout << "Invalid input. Please enter a positive integer.\n";
                std::cin.clear(); // Clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard input buffer
            }
        }
        while (tempPlayer <= 0);
        std::cout << "You entered: " << tempPlayer << std::endl;

        // Ensure that the position limit is not exceeded
        while (true) 
        {
            std::string selectedPosition = top300[tempPlayer + indexHelper].second[0];
            if (selectedPosition == "QB" && qbLimitContainer[ownTeam] >= qbLimit) {
                std::cout << "Error: QB positional limit exceeded. Please pick another player." << std::endl;
            }
            else if (selectedPosition == "RB" && rbLimitContainer[ownTeam] >= rbLimit) {
                std::cout << "Error: RB positional limit exceeded. Please pick another player." << std::endl;
            }
            else if (selectedPosition == "WR" && wrLimitContainer[ownTeam] >= wrLimit) {
                std::cout << "Error: WR positional limit exceeded. Please pick another player." << std::endl;
            }
            else if (selectedPosition == "TE" && teLimitContainer[ownTeam] >= teLimit) {
                std::cout << "Error: TE positional limit exceeded. Please pick another player." << std::endl;
            }
            else {
                break; // Positional limit not exceeded, break the loop
            }

            promptForMorePlayers();

            std::cout << "It is your turn to pick!" << std::endl;
            std::cout << "Enter desired player (number only): " << std::endl;
            std::cin >> tempPlayer;
            std::cout << "" << std::endl;
        }

        std::cout << playerCount << ". " << ownTeam << " selects: " << top300[tempPlayer + indexHelper].first << ", " << top300[tempPlayer + indexHelper].second[0] << std::endl;
        teamPlayerMap[ownTeam][top300[tempPlayer + indexHelper].first] = top300[tempPlayer + indexHelper].second[0];
        // Update the count of positions taken by the team
        updatePositionCount(ownTeam, top300[tempPlayer + indexHelper].second[0]);
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

                // gives user control over their own draft slot
                if (team == ownTeam) {
                    std::cout << "" << std::endl;


                    displayTopPlayers();


                    // asks users if they want to see any more players
                    std::cout << "" << std::endl;
                    promptForMorePlayers();
                    getUserPick(); // gets user pick
                }

                else 
                {
                    // Use iterators to find the player by rank
                    auto it = top300.begin();
                    if (it != top300.end()) {

                        // adds probability randomization to the draft
                        // 40% chance to pick top pick, 30% second pick, 20% third pick, 10% forth pick
                        pick = pickRandomizer();

                        // advances the top300 to correct pick and chooses the players
                        std::advance(it, pick - 1);
                        

                        bool positionCheck = false;
                        while (positionCheck == false)
                        {
                            // comment in the "moving to next player" lines for debugging purposes to see where the draft gets stuck
                            if (it->second[0] == "QB" && qbLimitContainer[team] >= qbLimit)
                            {
                                //std::cout << "Moving to next player" << std::endl;
                                std::advance(it, 1);
                            }
                            else if (it->second[0] == "RB" && rbLimitContainer[team] >= rbLimit)
                            {
                                //std::cout << "Moving to next player" << std::endl;
                                std::advance(it, 1);
                            }
                            else if (it->second[0] == "WR" && wrLimitContainer[team] >= wrLimit)
                            {
                                //std::cout << "Moving to next player" << std::endl;
                                std::advance(it, 1);
                            }
                            else if (it->second[0] == "TE" && teLimitContainer[team] >= teLimit)
                            {
                                //std::cout << "Moving to next player" << std::endl;
                                std::advance(it, 1);

                            }
                            else
                            {
                                positionCheck = true;
                            }

                        }

                        if (it->second[0] == "void")
                        {
                            std::cout << "No more of the position desired available, voiding pick" << std::endl;
                        }
                        else
                        {
                            updatePositionCount(team, it->second[0]);
                            std::cout << playerCount << ". " << team << " selects: " << it->first << ", " << it->second[0] << std::endl;
                            teamPlayerMap[team][it->first] = it->second[0];   // updates the team map for each team
                            top300.erase(it); // erases player selected from the top300 container
                            ++playerCount;
                        }

                    }
                }
                ++teamIndex;
            }
            std::cout << std::endl;     // used to make output nicer and more read-able
        }
    }

    int pickRandomizer()
    {
        // Define the probabilities
        std::vector<double> probabilities = { 0.4, 0.3, 0.2, 0.1 }; // Probabilities for numbers 1, 2, 3, 4 respectively

        // Create a discrete distribution based on the probabilities
        std::discrete_distribution<int> distribution({ 0.4, 0.3, 0.2, 0.1 });

        // Seed the random number generator
        std::random_device rd;
        std::mt19937 gen(rd());

        // Generate a random number based on the probabilities
        int result = distribution(gen) + 1; // Adding 1 to make the result in the range [1, 4]

        // Output the selected number
        return result;
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


    // operates and runs the functions above
    void operate() 
    {

        std::cout << "" << std::endl;
        std::cout << "Enter your Team (name). If you want to autodraft, enter any character that is not already a team name: " << std::endl;
        std::cin >> ownTeam;
        std::cout << "" << std::endl;

        std::ifstream draftFile(draftFileName);     // open the chosen draft CSV file
        if (!draftFile.is_open())
        {
            std::cerr << "Failed to open draft file: " << draftFileName << std::endl;
            return;
        }

        // opens the NFL Top 300 file
        /*std::ifstream NFL_Top_300("NFL_TOP_300.csv");
        std::ifstream qb("QB.csv");
        std::ifstream rb("RB.csv");
        std::ifstream wr("WR.csv");
        std::ifstream te("TE.csv");*/


        // Verifies that the file can be opened
        //if (!NFL_Top_300.is_open() || !qb.is_open() || !rb.is_open() || !wr.is_open() || !te.is_open()) {
        //    std::cerr << "Failed to open." << std::endl;
        //}


        // copies the map into the top300
        std::string line;
        while (std::getline(draftFile, line)) {
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
        //NFL_Top_300.close();
        //qb.close();
        //rb.close();
        //wr.close();
        //te.close();

        draftFile.close();
    }


};
#endif


