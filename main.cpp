#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "Ranking.h"
#include "League.h"
#include "Draft.h"
#include "CustomLeague.h"



int draft::totalDrafts = 0;

int main()
{
	int draftType;

	std::cout << "Choose draft format (1 - standard, 2 - PPR, 3 - half PPR): " << std::endl;
	std::cin >> draftType;

	ranking draftRanking(draftType);
	draftRanking.originalOperate();


	CustomLeague myLeague("", 0);
	std::thread leagueThread(&CustomLeague::getLeagueInfo, &myLeague);
	// Wait for the thread to finish its execution
	leagueThread.join();
 

	// testing draft file
	
	draft testDraft(myLeague.addMembers(), myLeague.getQbLimit(), myLeague.getRbLimit(), myLeague.getWrLimit(), myLeague.getTeLimit(), myLeague.getRoundLimit(), draftType);
	
	testDraft.operate();
	std::cout << "Number of drafts completed: " << draft::totalDrafts << std::endl;


	return 0;
}