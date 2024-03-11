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

public:
    // Constructor
    CustomLeague(const std::string& name, int numTeams) : leagueName(name), numMembers(numTeams), leagueMembers(numTeams) {

        std::cout << "\nLeague created with ID#: " << ptrToLeague << std::endl;
    };


    // Asks for user input of the league
    void getLeagueInfo() override {
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

        // position and round limits



        std::cout << "Enter QB Limit: " << std::endl;
        std::cin >> qbLimit;


        std::cout << "Enter RB Limit: " << std::endl;
        std::cin >> rbLimit;

        std::cout << "Enter WR Limit: " << std::endl;
        std::cin >> wrLimit;

        std::cout << "Enter TE Limit: " << std::endl;
        std::cin >> teLimit;

        std::cout << "The total roster limit is: " << qbLimit + rbLimit + wrLimit + teLimit << std::endl;

        bool validRoundLimit = false;

        while (!validRoundLimit)
        {
            std::cout << "\nEnter number of rounds (must be less than total roster limit): " << std::endl;
            std::cin >> roundLimit;

            if (roundLimit <= qbLimit + rbLimit + wrLimit + teLimit)
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
    int getQbLimit() const
    {
        return qbLimit;
    }

    int getRbLimit() const
    {
        return rbLimit;
    }

    int getWrLimit() const
    {
        return wrLimit;
    }

    int getTeLimit() const
    {
        return teLimit;
    }

    int getRoundLimit() const
    {
        return roundLimit;
    }

};

#endif