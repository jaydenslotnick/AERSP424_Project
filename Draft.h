#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>

class draft {
private:
    std::string player;
    int lineNumber = 0;
    

public:


    void operate() {
      


        // opens the NFL Top 300 file
        std::ifstream NFL_Top_300("NFL_TOP_300.txt");
        std::ifstream qb("QB.txt");
        std::ifstream rb("RB.txt");
        std::ifstream wr("WR.txt");
        std::ifstream te("TE.txt");
        std::ofstream Empty_Top_300;

        Empty_Top_300.open("Empty_Top_300.txt");


        // Verifies that the file can be opened
        if (!NFL_Top_300.is_open() || !qb.is_open() || !rb.is_open() || !wr.is_open() || !te.is_open() || !Empty_Top_300.is_open()) {
            std::cerr << "Failed to open." << std::endl;
        }


        // Copy contents of top 300 rankings to an empty file
        char copy;
        while (NFL_Top_300.get(copy)) {
            Empty_Top_300.put(copy);
        }


        // closes nfl top 300 file
        Empty_Top_300.close();
        NFL_Top_300.close();
        qb.close();
        rb.close();
        wr.close();
        te.close();



        // deletes the temporary top 300 file 
        const char* delete_empty = "Empty_Top_300.txt"; 

        // tracks to see if the file was actually deleted
        int result = std::remove(delete_empty);

        // Prints result of the deletion
        if (result != 0) {
            // If deletion fails, print an error message
            perror("Error deleting file");
        }

        else {
            // If deletion succeeds, print a success message
            //std::cout << "File deleted successfully." << std::endl; // add if needed
        }


    };

};