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
    int qbLimit;
    int rbLimit;
    int wrLimit;
    int teLimit;
    

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
        std::ofstream Empty_Top_300;
        std::ofstream Empty_qb;
        std::ofstream Empty_rb;
        std::ofstream Empty_wr;
        std::ofstream Empty_te;

        Empty_Top_300.open("Empty_Top_300.txt");
        Empty_qb.open("Empty_qb.txt");
        Empty_rb.open("Empty_rb.txt");
        Empty_wr.open("Empty_wr.txt");
        Empty_te.open("Empty_te.txt");


        // Verifies that the file can be opened
        if (!NFL_Top_300.is_open() || !qb.is_open() || !rb.is_open() || !wr.is_open() || !te.is_open() || !Empty_Top_300.is_open()) {
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


        std::cout << "Enter QB Limit: " << std::endl;
        std::cin >> qbLimit;


        std::cout << "Enter RB Limit: " << std::endl;
        std::cin >> rbLimit;

        std::cout << "Enter WR Limit: " << std::endl;
        std::cin >> wrLimit;

        std::cout << "Enter TE Limit: " << std::endl;
        std::cin >> teLimit;


        // all draft stuff here























        // End of draft stuff

        // closes nfl top 300 file
        Empty_Top_300.close();
        Empty_qb.close();
        Empty_rb.close();
        Empty_wr.close();
        Empty_te.close();
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