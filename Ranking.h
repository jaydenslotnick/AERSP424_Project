#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <map>

#ifndef RANKING_H
#define RANKING_H

class ranking {
private:
    std::string player;
    int lineNumber = 0;
    std::vector<std::pair<std::string, std::vector<std::string>>> top300;
    int rank;
    std::string fileName;
    bool valid = false;


public:

    // Constructor with integer argument
    ranking(int rankingType) : rank(rankingType) {}

    ~ranking(){}

    

    void operate()
    {
        std::cout << "Default operation" << std::endl;
        originalOperate();
    }

    void operate(int val)       // overloading the operate function
    {
        std::cout << "Operation with integer" << val << std::endl;
        originalOperate();
    }


    void originalOperate() {

        std::cout << "Draft Types (1 - standard, 2 - ppr, 3 - half ppr): " << std::endl;
        while (!valid)
        {


            if (rank == 1)
            {

                std::cout << "\n1. Top 300 Standard Format: \n " << std::endl;

                // opens the NFL Top 300 file
                std::ifstream NFL_Top_300("NFL_TOP_300.csv");


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


                // Printing the map using overloaded operator
                std::cout << *this;

                // closes nfl top 300 file
                NFL_Top_300.close();
                valid = true;
            }

            else if (rank == 2)
            {
                std::cout << "\n2. Top 300 PPR Format: \n" << std::endl;

                // opens the ppr Top 300 file
                std::ifstream PPR_Top_300("PPR_TOP_300.csv");


                // copies the map into the ppr top300
                std::string line;
                while (std::getline(PPR_Top_300, line)) {
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


                // Printing the map using overloaded operator
                std::cout << *this;

                // closes ppr top 300 file
                PPR_Top_300.close();
                valid = true;
            }


            else if (rank == 3)
            {

                std::cout << "\n3. Top 300 Half PPR Format: \n" << std::endl;

                // opens the half ppr Top 300 file
                std::ifstream Half_PPR_Top_300("Half_PPR_Top_300.csv");


                // copies the map into the half ppr top300
                std::string line;
                while (std::getline(Half_PPR_Top_300, line)) {
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


                // Printing the map using overloaded operator
                std::cout << *this;

                // closes half ppr top 300 file
                Half_PPR_Top_300.close();
                valid = true;
            }
        }


    };

    // Overloading << operator to print ranking information
    friend std::ostream& operator<<(std::ostream& os, const ranking& rank) {
        for (const auto& pair : rank.top300) {
            os << "Player: " << pair.first << ", Position: ";
            for (const auto& column : pair.second) {
                os << column << " ";
            }
            os << std::endl;
        }
        return os;
    }

};

#endif
