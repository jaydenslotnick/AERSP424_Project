#include <iostream>
#include <fstream>
#include <string>
#include "Ranking.h"
#include "League.h"
#include "Draft.h"
#include "CustomLeague.h"
#include <thread>


int draft::totalDrafts = 0;

int main()
{

	ranking top300Ranking;

	// introducing a thread to complete the ranking operation
	std::thread rankingThread(&ranking::operate, &top300Ranking);

	rankingThread.join(); // joins ranking thread to the main thread


	//creates league and calls function to add members
	CustomLeague myLeague("", 0);
	myLeague.getLeagueInfo();
 

	// testing draft file
	
	draft testDraft(myLeague.addMembers(), myLeague.getQbLimit(), myLeague.getRbLimit(), myLeague.getWrLimit(), myLeague.getTeLimit(), myLeague.getRoundLimit());
	
	testDraft.operate();
	std::cout << "Number of drafts completed: " << draft::totalDrafts << std::endl;


	return 0;
}