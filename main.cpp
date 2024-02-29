#include <iostream>
#include <fstream>
#include <string>
#include "Ranking.h"
#include "League.h"
#include "Draft.h"


int draft::totalDrafts = 0;

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
	std::cout << "Number of drafts completed: " << draft::totalDrafts << std::endl;


	return 0;
}