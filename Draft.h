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
    std::string player; // name of an nfl player
    unsigned int lineNumber = 0; // keeps track of line number of the csv
    std::vector<std::string> leagueMembers; // container with the league members names
    unsigned int qbLimit = 0; // quarterback limit variable
    unsigned int rbLimit = 0; // running back limit variable
    unsigned int wrLimit = 0; // wide receiver limit variable
    unsigned int teLimit = 0; // tight end limit variable
    unsigned int currentRound = 0; // keeps track of the current round of the draft
    unsigned int roundLimit = 0; // limit variable for the number of rounds of the draft
    unsigned int tempPlayer = 0; // temporary variable to start the player selected 
    unsigned int playerCount = 1; // keeps track of the number of players selected, starts at 1
    unsigned char morePlayers = 0; // variable designed to start a y/n response to a question of whether the user wants to see more players
    unsigned int numPlayers = 0; // Outputs the number of players remaining, "Top numPlayers remaining"
    unsigned int defaultPlayers = 10; // default outputs the top 10 players left

    signed int indexHelper = -1; // variable used to help simplify code, reduce the number of "magic numbers" used


    // average salaries of starting nfl players in millions
    float qbSalary = 28.2; 
    float rbSalary = 2.7;
    float wrSalary = 10;
    float teSalary = 8;

    // total estimated salary spent on team 
    double totalSalarySpent = 0.0;

    std::vector<std::pair<std::string, std::vector<std::string>>> topPlayers; // container used to store the players from a csv file
    std::string line; // variable used to store line of the csv
    std::string ownTeam; // variable for user controlled team


    std::map<std::string, std::map<std::string, std::string>> teamPlayerMap;     // create a map of maps to store each drafters picks

    std::map<std::string, int> positionLimits; // container to store the limits of positions

    int pick = 0;

    // containers for positional limits for each team
    std::map<std::string, int> qbLimitContainer; // Key: Team name, Value: Count of QBs taken
    std::map<std::string, int> rbLimitContainer; // Key: Team name, Value: Count of RBs taken
    std::map<std::string, int> wrLimitContainer; // Key: Team name, Value: Count of WRs taken
    std::map<std::string, int> teLimitContainer; // Key: Team name, Value: Count of TEs taken

    bool validChar = false; // used for error handling if a user does not enter a valid character

    

public:
    static int totalDrafts; // keeps track of total drafts completed


    // constructor, passes in the league members, positions limits, round limit, and the draft type
    draft(const std::vector<std::string>& members, int qb, int rb, int wr, int te, int roundLimit, int draftType) : leagueMembers(members), qbLimit(qb), rbLimit(rb), wrLimit(wr), teLimit(te), roundLimit(roundLimit) 
    {

        // populates the team player map with the league members
        for (const auto& team : leagueMembers)
        {
            teamPlayerMap[team] = std::map<std::string, std::string>();
        }
        ++totalDrafts; // increases total drafts completed
        positionLimits = { {"QB",qbLimit}, {"RB",rbLimit}, {"WR", wrLimit}, {"TE", teLimit} }; // fills container with limits for each respective position
        
        // Determine the draft CSV file to use based on the chosen draft type
        switch (draftType)
        {
        case 1:
            draftFileName = "NFL_TopPlayers.csv";
            break;
        case 2:
            draftFileName = "PPR_TopPlayers.csv";
            break;
        case 3: 
            draftFileName = "Half_PPR_TopPlayers.csv";
            break;
        default:
            std::cerr << "Invalid draft type." << std::endl;
            break;
        }
        
        // resizes positional limit containers based on number of league members, initally the number of positions taken is 0
        for (const auto& member : members) {
            qbLimitContainer[member] = 0;
            rbLimitContainer[member] = 0;
            wrLimitContainer[member] = 0;
            teLimitContainer[member] = 0;
        }

       
    }

    std::vector<std::string> draftOrder = leagueMembers; // sets the draft order

    // Display top players with default number
    void displayTopPlayers() {
        displayTopPlayers(defaultPlayers);
    }


    // displays the players available
    void displayTopPlayers(int numPlayers) {
        std::cout << "Top " << numPlayers << " players remaining: " << std::endl;
        for (int i = 0; i < numPlayers; ++i) {
            std::cout << i + 1 << ". " << topPlayers[i].first << ", " << topPlayers[i].second[0] << std::endl;
        }
    }

    // asks the user whether they would like to see more top players available
    void promptForMorePlayers() {


        // asks user if they want to see more players, forces them to enter y or n or Y or N
        while (validChar == false)
        {

            // prompts user to see if they would like to display more players available
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

                displayTopPlayers(numPlayers); // calls function to display top players remaining with user input on the number of players
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

        int tempPlayer; // temp player to pick, resets after each round

        // receives user input for the player they would like to select, error handling added to make sure they enter a correct input
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

        // if valid, will output the selected player
        while (tempPlayer <= 0);
        std::cout << "You entered: " << tempPlayer << std::endl;

        // Ensure that the position limit is not exceeded
        while (true) 
        {
            std::string selectedPosition = topPlayers[tempPlayer + indexHelper].second[0]; // sets selected position variable

            // checks to see if the position limit is within bounds, will force the user to enter another player if condition is not satisfied
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

            // if user exceeds position limit, this will give them the option to see more players 
            promptForMorePlayers();

            std::cout << "It is your turn to pick!" << std::endl;
            std::cout << "Enter desired player (number only): " << std::endl;
            std::cin >> tempPlayer;
            std::cout << "" << std::endl;
        }

        std::cout << playerCount << ". " << ownTeam << " selects: " << topPlayers[tempPlayer + indexHelper].first << ", " << topPlayers[tempPlayer + indexHelper].second[0] << std::endl;  // outputs selected player and position
        teamPlayerMap[ownTeam][topPlayers[tempPlayer + indexHelper].first] = topPlayers[tempPlayer + indexHelper].second[0]; // updates the team player map
        // Update the count of positions taken by the team
        updatePositionCount(ownTeam, topPlayers[tempPlayer + indexHelper].second[0]); // updates the positon that was taken for each team
        topPlayers.erase(topPlayers.begin() + tempPlayer + indexHelper); // erases player from ranking container
        ++playerCount; // increases player count variable
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
                    auto it = topPlayers.begin();
                    if (it != topPlayers.end()) {

                        // adds probability randomization to the draft
                        // 40% chance to pick top pick, 30% second pick, 20% third pick, 10% forth pick
                        pick = pickRandomizer();

                        // advances the topPlayers to correct pick and chooses the players
                        std::advance(it, pick - 1);
                        

                        bool positionCheck = false;
                        while (positionCheck == false)
                        {
                            // comment in the "moving to next player" lines for debugging purposes to see where the draft gets stuck
                            // if the position limit is violated, the next player that satisfies conditions will be selected
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
                                positionCheck = true; // breaks loop
                            }

                        }


                        // if the csv runs out of a certain position, this will be outputted to make the user aware
                        if (it->second[0] == "void")
                        {
                            std::cout << "No more of the position desired available, voiding pick" << std::endl;
                        }

                        // same logic as before, outputs selected player and position, updates map, erases it, increments player
                        else
                        {
                            updatePositionCount(team, it->second[0]);
                            std::cout << playerCount << ". " << team << " selects: " << it->first << ", " << it->second[0] << std::endl;
                            teamPlayerMap[team][it->first] = it->second[0];   // updates the team map for each team
                            topPlayers.erase(it); // erases player selected from the topPlayers container
                            ++playerCount;
                        }

                    }
                }
                ++teamIndex; // advances to the team team
            }
            std::cout << std::endl;     // used to make output nicer and more read-able
        }
    }

    int pickRandomizer()
    {
        // Define the probabilities
        std::vector<double> probabilities = { 0.4, 0.3, 0.2, 0.1 }; // Probabilities for numbers 1, 2, 3, 4 respectively, adds up to 1

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
            

            // outputs in roster format, quarterbacks, running backs, wide receivers, tight ends
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
            std::cout << "Total estimated salary: $" << totalSalarySpent << " million" << std::endl; // estimated salary of the team for fun
            std::cout << std::endl;     // used to make output nicer and more read-able
        
        }
    }


    // operates and runs the functions above
    void operate() 
    {
        // gives the user the option to do a full autodraft
        std::cout << "" << std::endl;
        std::cout << "Enter your Team (name). If you want to autodraft, enter any character that is not already a team name: " << std::endl;
        std::cin >> ownTeam;
        std::cout << "" << std::endl;

        std::ifstream draftFile(draftFileName);     // open the chosen draft CSV file

        // error handling if the csv cannot be opened
        if (!draftFile.is_open())
        {
            std::cerr << "Failed to open draft file: " << draftFileName << std::endl;
            return;
        }


        // copies the map into the topPlayers
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
                topPlayers.emplace_back(columns[0], std::vector<std::string>(columns.begin() + 1, columns.end()));
            }
        }
        draftSimulation(roundLimit); // calls the draft simulation, the brains of the class to run the draft
        outputTeamPicks(); // outputs all the teams at the end of the draft

        draftFile.close(); // closes file
    }


};
#endif


