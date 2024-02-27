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
        bool validLeagueName = false;
        while (!validLeagueName)
        {
            std::cout << "Enter league name: " << std::endl;
            std::getline(std::cin, leagueName); // Allowing the league name to be multiple words

            validLeagueName = true;
            for (char c : leagueName)       // iterates over each character in the string leagueName
            {
                if (!std::isalpha(c) && c != ' ')       // make sure the user enters only letters or spaces for the league name
                {
                    validLeagueName = false;
                    break;
                }
            }
            if (!validLeagueName)                     // prints an error message if the user enters an invalid name
            {
                std::cout << "Please enter a valid league name consisting only of letters and spaces." << std::endl;
            }
        }
        std::cout << "League name entered: " << leagueName << std::endl;

        bool validNumMembers = false;        
        while (!validNumMembers)
        {
            std::cout << "Enter number of members (up to 10): " << std::endl;
            std::cin >> numMembers;

            if (std::cin.fail() || numMembers <= 0 || numMembers > 10)
            {
                std::cout << "Please enter a positive integer up to 10." << std::endl;
                std::cin.clear();       // clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');     // discard invalid input
            }
            else
            {
                validNumMembers = true;
            }
        }
        std::cout << "You entered: " << numMembers << std::endl;
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