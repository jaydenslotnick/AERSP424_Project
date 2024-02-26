#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>

class League {
private:
    int numMembers;
    std::string leagueName;
    std::vector<std::string> leagueMembers;
    std::string* ptrToLeague = &leagueName;         // creates a pointer to the memory address of the league name

public:
    // Constructor
    League(const std::string& name, int numTeams) : leagueName(name), numMembers(numTeams), leagueMembers(numTeams) {
        
        std::cout << "\nLeague created with ID#: " << ptrToLeague << std::endl;
    };


    // Asks for user input of the league
    void getLeagueInfo() {
        std::cout << "Enter league name: " << std::endl;
        std::getline(std::cin, leagueName); // Allowing the league name to be multiple words

        std::cout << "Enter number of members: " << std::endl;
        std::cin >> numMembers;
    }


    std::vector<std::string> addMembers() {
        leagueMembers.resize(numMembers); // Resize the vector to accommodate numMembers

        for (int i = 0; i < numMembers; ++i) {
            std::string name;
            std::cout << "Enter name for member (enter in draft order) " << (i + 1) << ": ";
            std::cin >> name;
            leagueMembers[i] = name;
        }

        std::cout << "\nWelcome to " << leagueName << " Fantasy Football League\n";
        std::cout << "Fantasy Football League Members:\n";

        for (int i = 0; i < numMembers; ++i) {
            std::cout << "Member " << (i + 1) << ": " << leagueMembers[i] << std::endl;
        }

        return leagueMembers;
    }

};