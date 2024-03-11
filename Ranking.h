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


public:


    void operate() {

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
