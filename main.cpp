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


	//creates league and calls function to add members
	League myLeague("", 0);
	myLeague.getLeagueInfo();
	std::vector<std::string> leagueMembers = myLeague.addMembers();



	// testing draft file

	draft testDraft(leagueMembers);
	testDraft.operate();



	return 0;
}