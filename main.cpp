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
	bool userDraft = false;
	char anotherDraft;



	while (userDraft == false)
	{
		std::cout << "Choose draft format (1 - standard, 2 - PPR, 3 - half PPR): " << std::endl;
		std::cin >> draftType;

		// logic for the standard draft format
		if (draftType == 1)
		{
			ranking standardRanking(draftType);
			standardRanking.originalOperate();

			CustomLeague standardLeague("", 0);
			std::thread standardLeagueThread(&CustomLeague::getLeagueInfo, &standardLeague);
			// Wait for the thread to finish its execution
			standardLeagueThread.join();

			draft standardDraft(standardLeague.addMembers(), standardLeague.getQbLimit(), standardLeague.getRbLimit(), standardLeague.getWrLimit(), standardLeague.getTeLimit(), standardLeague.getRoundLimit(), draftType);

			standardDraft.operate();


			std::cout << "Would you like to complete another draft (y/n)? " << std::endl;
			std::cin >> anotherDraft;

			if (anotherDraft == 'y' || anotherDraft == 'Y')
			{
				userDraft = false;
			}
			else if (anotherDraft == 'n' || anotherDraft == 'N')
			{
				userDraft = true;
			}
			else
			{
				std::cout << "Enter a y/n: " << std::endl;
				std::cin >> userDraft;
			}

		}

		// logic for the PPR draft format
		else if (draftType == 2)
		{
			ranking PPRRanking(draftType);
			PPRRanking.originalOperate();

			CustomLeague PPRLeague("", 0);
			std::thread PPRLeagueThread(&CustomLeague::getLeagueInfo, &PPRLeague);
			// Wait for the thread to finish its execution
			PPRLeagueThread.join();

			draft PPRDraft(PPRLeague.addMembers(), PPRLeague.getQbLimit(), PPRLeague.getRbLimit(), PPRLeague.getWrLimit(), PPRLeague.getTeLimit(), PPRLeague.getRoundLimit(), draftType);

			PPRDraft.operate();

			std::cout << "Would you like to complete another draft (y/n)? " << std::endl;
			std::cin >> anotherDraft;

			if (anotherDraft == 'y' || anotherDraft == 'Y')
			{
				userDraft = false;
			}
			else if (anotherDraft == 'n' || anotherDraft == 'N')
			{
				userDraft = true;
			}
			else
			{
				std::cout << "Enter a y/n: " << std::endl;
				std::cin >> userDraft;
			}
		}


		// logic for the PPR draft format
		else if (draftType == 3)
		{
			ranking HalfPPRRanking(draftType);
			HalfPPRRanking.originalOperate();

			CustomLeague HalfPPRLeague("", 0);
			std::thread HalfPPRLeagueThread(&CustomLeague::getLeagueInfo, &HalfPPRLeague);
			// Wait for the thread to finish its execution
			HalfPPRLeagueThread.join();

			draft HalfPPRDraft(HalfPPRLeague.addMembers(), HalfPPRLeague.getQbLimit(), HalfPPRLeague.getRbLimit(), HalfPPRLeague.getWrLimit(), HalfPPRLeague.getTeLimit(), HalfPPRLeague.getRoundLimit(), draftType);

			HalfPPRDraft.operate();

			std::cout << "Would you like to complete another draft (y/n)? " << std::endl;
			std::cin >> anotherDraft;

			if (anotherDraft == 'y' || anotherDraft == 'Y')
			{
				userDraft = false;
			}
			else if (anotherDraft == 'n' || anotherDraft == 'N')
			{
				userDraft = true;
			}
			else
			{
				std::cout << "Enter a y/n: " << std::endl;
				std::cin >> userDraft;
			}
		}

		else
		{
			std::cout << "Enter a number 1-3" << std::endl;
		}
	}



	std::cout << "Number of drafts completed: " << draft::totalDrafts << std::endl;


	return 0;
}