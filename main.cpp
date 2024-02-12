#include <iostream>
#include <fstream>
#include <string>
#include "Ranking.h"
#include "League.h"

int main()
{
	// calling league class and calling addMember function, prints out league
	std::string leagueName;
	int numMembers;
	std::cout << "Enter league name: " << std::endl;
	std::cin >> leagueName;
	std::cout << "Enter number of members: " << std::endl;
	std::cin >> numMembers;
	League myLeague(leagueName, numMembers);
	myLeague.addMembers();

	// calling ranking class and calling operate function
	ranking myRanking;
	myRanking.operate();




	return 0;
}