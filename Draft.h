#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>

class draft {
private:
    std::string player;
    int lineNumber = 0;
    std::vector<std::string> leagueMembers;
    int qbLimit = 0;
    int rbLimit = 0;
    int wrLimit = 0;
    int teLimit = 0;
    int currentRound = 0;
    int roundLimit = 0;
    std::vector<std::string> draftOrder = leagueMembers;
    

public:

    draft(const std::vector<std::string> members) : leagueMembers(members) {}


    void operate() {
      
        
        // opens the NFL Top 300 file
        std::ifstream NFL_Top_300("NFL_TOP_300.txt");
        std::ifstream qb("QB.txt");
        std::ifstream rb("RB.txt");
        std::ifstream wr("WR.txt");
        std::ifstream te("TE.txt");

        // creates and opens empty temp files
        std::ofstream Empty_Top_300("Empty_Top_300.txt");
        std::ofstream Empty_qb("Empty_qb.txt");
        std::ofstream Empty_rb("Empty_rb.txt");
        std::ofstream Empty_wr("Empty_wr.txt");
        std::ofstream Empty_te("Empty_te.txt");

        // Verifies that the file can be opened
        if (!NFL_Top_300.is_open() || !qb.is_open() || !rb.is_open() || !wr.is_open() || !te.is_open()) {
            std::cerr << "Failed to open." << std::endl;
        }


        // Copy contents of all files to the temp files
        char copy;
        while (NFL_Top_300.get(copy)) {
            Empty_Top_300.put(copy);
        }

        while (qb.get(copy)) {
            Empty_qb.put(copy);
        }

        while (rb.get(copy)) {
            Empty_rb.put(copy);
        }

        while (wr.get(copy)) {
            Empty_wr.put(copy);
        }

        while (te.get(copy)) {
            Empty_te.put(copy);
        }

        // closes nfl top 300 file
        Empty_Top_300.close();
        Empty_qb.close();
        Empty_rb.close();
        Empty_wr.close();
        Empty_te.close();

        // opens the NFL Top 300 file
        std::ifstream Empty_Top_300_read("Empty_Top_300.txt");
        std::ifstream Empty_qb_read("Empty_qb.txt");
        std::ifstream Empty_rb_read("Empty_rb.txt");
        std::ifstream Empty_wr_read("Empty_wr.txt");
        std::ifstream Empty_te_read("Empty_te.txt");

        // not sure how we would implement this
        //std::cout << "Enter QB Limit: " << std::endl;
        //std::cin >> qbLimit;


        //std::cout << "Enter RB Limit: " << std::endl;
        //std::cin >> rbLimit;

        //std::cout << "Enter WR Limit: " << std::endl;
        //std::cin >> wrLimit;

        //std::cout << "Enter TE Limit: " << std::endl;
        //std::cin >> teLimit;

        // Assigns values to the currentRound and roundLimit variables
        int currentRound = 1;

        std::cout << "Enter number of rounds: " << std::endl;
        std::cin >> roundLimit;

        // Loops through the draft in a snake draft order
        for (int round = 1; round <= roundLimit; ++round) {
            std::cout << "Round " << round << ":\n";
            if (round % 2 == 0)
                std::reverse(draftOrder.begin(), draftOrder.end());
            for (const auto& team : draftOrder) {
                if (std::getline(Empty_Top_300_read, player))
                    std::cout << team << " selects: " << player << std::endl;
            }
            ++currentRound;
        }


        // End of draft stuff
        // closes nfl top 300 file
        Empty_Top_300_read.close();
        Empty_qb_read.close();
        Empty_rb_read.close();
        Empty_wr_read.close();
        Empty_te_read.close();

        NFL_Top_300.close();
        qb.close();
        rb.close();
        wr.close();
        te.close();



        // deletes the temporary files
        const char* delete_empty = "Empty_Top_300.txt"; 
        const char* delete_empty_qb = "Empty_qb.txt";
        const char* delete_empty_rb = "Empty_rb.txt";
        const char* delete_empty_wr = "Empty_wr.txt"; 
        const char* delete_empty_te = "Empty_te.txt";

        std::remove(delete_empty);
        std::remove(delete_empty_qb);
        std::remove(delete_empty_rb);
        std::remove(delete_empty_wr);
        std::remove(delete_empty_te);

    };

};