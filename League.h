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
    

public:
    // Constructor
    League(const std::string& name, int numTeams) : leagueName(name), numMembers(numTeams), leagueMembers(numTeams) {
        std::cout << "League created! " << std::endl;
    };

    void addMembers() {


        for (int i = 0; i < numMembers; ++i) {
            std::string name;
            std::cout << "Enter name for member " << (i + 1) << ": ";
            std::cin >> name;
            leagueMembers[i] = name;
        }
        std::cout << "Welcome to " << leagueName << " Fantasy Football League\n";
        std::cout << "Fantasy Football League Members:\n";

        for (int i = 0; i < numMembers; ++i) {
            std::cout << "Member " << (i + 1) << ": " << leagueMembers[i] << std::endl;
        }
    }


};