#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include "League.h"
#include <regex>

#ifndef CUSTOMLEAGUE_H
#define CUSTOMLEAGUE_H


// derived class from the base class league
class CustomLeague : public League {
private:
    int numMembers; // number of league members
    std::string leagueName; // league name variable
    std::vector<std::string> leagueMembers; // container for the league members
    std::string* ptrToLeague = &leagueName; // creates a pointer to the memory address of the league name
    int maxLeagueMembers = 16; // maximum league members this code will support

    // positional and round limits
    // qb - quarterback, rb - running back, wr - wide receiver, te - tight end
    int qbLimit = 0;
    int rbLimit = 0;
    int wrLimit = 0;
    int teLimit = 0;
    int roundLimit = 0;


    // error handling if the user enters a wrong input
    bool validqbLimit = false;
    bool validrbLimit = false;
    bool validwrLimit = false;
    bool validteLimit = false;



public:
    // Constructor, passes in league name and number of teams
    CustomLeague(const std::string& name, int numTeams) : League(name, numTeams), leagueName(name), numMembers(numTeams), leagueMembers(numTeams) {

        std::cout << "\nLeague created with ID#: " << ptrToLeague << std::endl; // outputs memory address of where league is created
    };




    // virtual function to ask for user input of the league
    void getLeagueInfo() override {

        // checks to make sure the user input a valid league name
        bool validLeagueName = false;
        while (!validLeagueName)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter league name consisting of only letters and spaces: " << std::endl;
            std::getline(std::cin, leagueName); // Allowing the league name to be multiple words

            if (leagueName.empty())             // does not allow the league name to be empty
            {
                std::cout << "Please enter a valid non-empty league name. " << std::endl;
                continue;
            }

            std::regex pattern("[a-zA-Z ]+");   // defines a regular expression pattern that matches a sequence of upper or lower case letters and spaces
            if (std::regex_match(leagueName, pattern))  // checks if the string leagueName matches the regex pattern
            {
                validLeagueName = true;
            }
            else
            {
                std::cout << "Please enter a valid league name consisting only of letters and spaces." << std::endl;
            }

        }
        std::cout << "League name entered: " << leagueName << std::endl;

        // Lambda function for input validation and assignment for the positional limits
        auto positionLimitValidation = [](int& limit) 
            {

            // forces user to enter a positive integer for the position limit
            while (true) 
            {
                std::cin >> limit;
               
                if (std::cin.fail() || limit < 0) 
                {
                    std::cout << "Invalid input. Please enter 0 or a positive integer." << std::endl;
                    std::cin.clear(); // clears the invalid input
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clears the invalid input
                }

                // breaks out of the loop if the user entered a valid input
                else 
                {
                    break;
                }
            }
        };

        // Lambda function for input validation and assignment for the round limit
        auto roundLimitValidation = [](int& roundLimit, int& qbLimit, int& rbLimit, int& wrLimit, int& teLimit) {

            bool validRoundLimit = false;

            // forces user to enter a positive integer that is less than or equal to the sum of the position limits
            while (!validRoundLimit)
            {
                std::cout << "\nEnter number of rounds (must be less than or equal to the total roster limit): " << std::endl;
                std::cin >> roundLimit;

                if (std::cin.fail() || roundLimit <= 0)
                {
                    std::cout << "\nInvalid input. Please enter a valid number." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                // breaks out of the loop if valid round limit input
                else if (roundLimit <= qbLimit + rbLimit + wrLimit + teLimit)
                {
                    validRoundLimit = true;
                }

                else
                {
                    std::cout << "\nPlease input number of rounds that are less than the total roster limit";
                }
            }
            };

        // prompts user for position and round limits and calls lambda functions to execute
        std::cout << "Enter QB Limit: " << std::endl;
        positionLimitValidation(qbLimit);

        std::cout << "Enter RB Limit: " << std::endl;
        positionLimitValidation(rbLimit);

        std::cout << "Enter WR Limit: " << std::endl;
        positionLimitValidation(wrLimit);

        std::cout << "Enter TE Limit: " << std::endl;
        positionLimitValidation(teLimit);


        roundLimit = qbLimit + rbLimit + wrLimit + teLimit;
        std::cout << "The total roster limit is: " << roundLimit << std::endl;
        roundLimitValidation(roundLimit, qbLimit, rbLimit, wrLimit, teLimit);




        // prompts user for league member number and checks to make sure it was a valid input
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

    // virtual function to add members to the league
    std::vector<std::string> addMembers() override {
        leagueMembers.resize(numMembers); // Resize the vector to accommodate numMembers

        for (int i = 0; i < numMembers; ++i) {

            // prompts user to enter the names of the league members in the correct draft order
            std::string name;
            std::cout << "Enter name for member (enter in draft order) " << (i + 1) << ": ";
            while (true)
            {
                std::cin >> name;

                bool isValid = true;
                for (char c : name)
                {
                    if (!std::isalpha(c))
                    {
                        isValid = false;
                        break;
                    }
                }
                if (isValid)
                {
                    break;  // exit the loop if the name is valid
                }
                else
                {
                    std::cout << "Invalid input. Please enter a valid name: ";
                }
            }
            leagueMembers[i] = name;
        }


        // Welcome message and outputs the league members
        std::cout << "\nWelcome to " << leagueName << " Fantasy Football League\n";
        std::cout << "Fantasy Football League Members:\n";

        for (int i = 0; i < numMembers; ++i) {
            std::cout << "Member " << (i + 1) << ": " << leagueMembers[i] << std::endl;
        }

        return leagueMembers; // Return the populated member list
    }

    // Virtual accessor functions for position limits and round limit
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