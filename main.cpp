#include <iostream>
#include <fstream>
#include <string>
#include "Ranking.h"
#include "League.h"
#include "Draft.h"

int main()
{

	ranking test;

	// calls operate to output the rankings
	test.operate();


	// league name and players

	// declares input variables
	std::string leagueName;
	int numMembers;

	// asks user for an input
	std::cout << "Enter league name: " << std::endl;
	std::cin >> leagueName;
	std::cout << "Enter number of members: " << std::endl;
	std::cin >> numMembers;

	//creates league and calls function to add members
	League myLeague(leagueName, numMembers);
	myLeague.addMembers();

	// testing draft file

	draft testDraft;
	testDraft.operate();



	return 0;
}