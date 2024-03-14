#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include "League.h"

#ifndef CUSTOMLEAGUE_H
#define CUSTOMLEAGUE_H

int maxLeagueMembers = 16;

class CustomLeague : public League {
private:
    int numMembers;
    std::string leagueName;
    std::vector<std::string> leagueMembers;
    std::string* ptrToLeague = &leagueName;         // creates a pointer to the memory address of the league name

    int qbLimit = 0;
    int rbLimit = 0;
    int wrLimit = 0;
    int teLimit = 0;
    int roundLimit = 0; // New member variable for round limit

    bool validqbLimit = false;
    bool validrbLimit = false;
    bool validwrLimit = false;
    bool validteLimit = false;


public:
    // Constructor
    CustomLeague(const std::string& name, int numTeams) : League(name, numTeams), leagueName(name), numMembers(numTeams), leagueMembers(numTeams) {

        std::cout << "\nLeague created with ID#: " << ptrToLeague << std::endl;
    };


    // Asks for user input of the league
    void getLeagueInfo() override {
        bool validLeagueName = false;
        while (!validLeagueName)
        {
            std::cout << "Enter league name consisting of only letters and spaces: " << std::endl;
            std::getline(std::cin, leagueName); // Allowing the league name to be multiple words

            if (leagueName.empty())             // does not allow the league name to be empty
            {
                std::cout << "Please enter a valid non-empty league name. " << std::endl;
                continue;
            }

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

        // position and round limits

        std::cout << "Enter QB Limit: " << std::endl;
        std::cin >> qbLimit;
        
        while (validqbLimit != true) 
        {
            if (std::cin.fail())
            {
                std::cout << "Invalid input. Please enter an integer." << std::endl;
                std::cin.clear(); // clears the invalid input
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clears the invalid input
                std::cout << "Enter QB Limit: " << std::endl;
                std::cin >> qbLimit;
            }
            else
            {
                validqbLimit = true;
            }
                
        }


        std::cout << "Enter RB Limit: " << std::endl;
        std::cin >> rbLimit;

        while (validrbLimit != true)
        {
            if (std::cin.fail())
            {
                std::cout << "Invalid input. Please enter an integer." << std::endl;
                std::cin.clear(); // clears the invalid input
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clears the invalid input
                std::cout << "Enter RB Limit: " << std::endl;
                std::cin >> rbLimit;
            }
            else
            {
                validrbLimit = true;
            }

        }

        std::cout << "Enter WR Limit: " << std::endl;
        std::cin >> wrLimit;

        while (validwrLimit != true)
        {
            if (std::cin.fail())
            {
                std::cout << "Invalid input. Please enter an integer." << std::endl;
                std::cin.clear(); // clears the invalid input
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clears the invalid input
                std::cout << "Enter WR Limit: " << std::endl;
                std::cin >> wrLimit;
            }
            else
            {
                validwrLimit = true;
            }

        }

        std::cout << "Enter TE Limit: " << std::endl;
        std::cin >> teLimit;

        while (validteLimit != true)
        {
            if (std::cin.fail())
            {
                std::cout << "Invalid input. Please enter an integer." << std::endl;
                std::cin.clear(); // clears the invalid input
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clears the invalid input
                std::cout << "Enter TE Limit: " << std::endl;
                std::cin >> teLimit;
            }
            else
            {
                validteLimit = true;
            }

        }

        std::cout << "The total roster limit is: " << qbLimit + rbLimit + wrLimit + teLimit << std::endl;

        bool validRoundLimit = false;

        while (!validRoundLimit)
        {
            std::cout << "\nEnter number of rounds (must be less than or equal to the total roster limit): " << std::endl;
            std::cin >> roundLimit;

            if (std::cin.fail())
            {
                std::cout << "\nInvalid input. Please enter a valid number." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            else if (roundLimit <= qbLimit + rbLimit + wrLimit + teLimit)
            {
                validRoundLimit = true;
            }

            else
            {
                std::cout << "\nPlease input number of rounds that are less than the total roster limit";
            }
        }



        bool validNumMembers = false;
        while (!validNumMembers)
        {
            std::cout << "Enter number of league members (up to " << maxLeagueMembers << "): " << std::endl;
            std::cin >> numMembers;

            if (std::cin.fail() || numMembers <= 0 || numMembers > maxLeagueMembers)
            {
                std::cout << "Please enter a positive integer up to " << maxLeagueMembers << "." << std::endl;
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


    std::vector<std::string> addMembers() override {
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

        return leagueMembers; // Return the populated member list
    }

    // Accessor functions for position limits and round limit
    int getQbLimit() override
    {
        return qbLimit;
    }

    int getRbLimit() override
    {
        return rbLimit;
    }

    int getWrLimit() override
    {
        return wrLimit;
    }

    int getTeLimit() override
    {
        return teLimit;
    }

    int getRoundLimit() override
    {
        return roundLimit;
    }

};

#endif