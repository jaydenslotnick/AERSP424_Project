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
		do {
			std::cout << "Choose draft format (1 - standard, 2 - PPR, 3 - half PPR): " << std::endl;
			std::cin >> draftType;

			if (std::cin.fail() || draftType < 1 || draftType > 3)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid Input. Please enter 1, 2, or 3." << std::endl;
			}
			else
			{
				break;
			}
		} while (true);

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

			while (true)
			{
				std::cout << "Would you like to complete another draft (y/n)? " << std::endl;
				std::cin >> anotherDraft;

				if (anotherDraft == 'y' || anotherDraft == 'Y')
				{
					userDraft = false;
					break;
				}
				else if (anotherDraft == 'n' || anotherDraft == 'N')
				{
					userDraft = true;
					break;
				}
				else
				{
					std::cout << "Invalid input. " << std::endl;
				}
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

			while (true)
			{
				std::cout << "Would you like to complete another draft (y/n)? " << std::endl;
				std::cin >> anotherDraft;

				if (anotherDraft == 'y' || anotherDraft == 'Y')
				{
					userDraft = false;
					break;
				}
				else if (anotherDraft == 'n' || anotherDraft == 'N')
				{
					userDraft = true;
					break;
				}
				else
				{
					std::cout << "Invalid input. " << std::endl;
				}
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

			while (true)
			{
				std::cout << "Would you like to complete another draft (y/n)? " << std::endl;
				std::cin >> anotherDraft;

				if (anotherDraft == 'y' || anotherDraft == 'Y')
				{
					userDraft = false;
					break;
				}
				else if (anotherDraft == 'n' || anotherDraft == 'N')
				{
					userDraft = true;
					break;
				}
				else
				{
					std::cout << "Invalid input. " << std::endl;
				}
			}
		}

		/*else		dont think this is needed anymore
		{
			std::cout << "Enter a number 1-3" << std::endl;
		}*/
	}



	std::cout << "Number of drafts completed: " << draft::totalDrafts << std::endl;


	return 0;
}