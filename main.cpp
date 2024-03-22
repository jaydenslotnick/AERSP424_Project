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



	int draftType1 = 1;
	int draftType2 = 2;
	int draftType3 = 3;

	ranking standard(draftType1);
	standard.originalOperate();
	ranking ppr(draftType2);
	ppr.originalOperate();
	ranking superflex(draftType3);
	superflex.originalOperate();


	CustomLeague myLeague("", 0);
	std::thread leagueThread(&CustomLeague::getLeagueInfo, &myLeague);
	// Wait for the thread to finish its execution
	leagueThread.join();
 

	// testing draft file
	
	draft testDraft(myLeague.addMembers(), myLeague.getQbLimit(), myLeague.getRbLimit(), myLeague.getWrLimit(), myLeague.getTeLimit(), myLeague.getRoundLimit());
	
	testDraft.operate();
	std::cout << "Number of drafts completed: " << draft::totalDrafts << std::endl;


	return 0;
}