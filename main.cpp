#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "Ranking.h"
#include "League.h"
#include "Draft.h"
#include "CustomLeague.h"



int draft::totalDrafts = 0;		// global variable used to count how many drafts have been completed

int main()
{

	int draftType; // variable for the draft type
	bool userDraft = false; // error handling if the user enters a invalid input
	char anotherDraft; // designed for a y/n answer to whether the user wants to complete another draft

	std::cout << "Welcome to the Fantasy Football Mock Draft Simulator" << std::endl;
	
	while (userDraft == false)
	{

		// prompts user to choose a draft type out of 3 options and checks the validity of the input
		do {
			std::cout << "Please choose desired draft format (1 - standard, 2 - PPR, 3 - half PPR): " << std::endl;
			std::cin >> draftType;

			if (std::cin.fail() || draftType < 1 || draftType > 3)	// checks if the user input is invalid and makes sure it is either 1, 2, or 3
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

			// outputs the ranking from the standard csv
			ranking standardRanking(draftType);
			standardRanking.originalOperate();


			// calls the custom league class to create a league object for the standard format 
			CustomLeague standardLeague("", 0);
			std::thread standardLeagueThread(&CustomLeague::getLeagueInfo, &standardLeague);
			// Wait for the thread to finish its execution
			standardLeagueThread.join();


			// calls the draft function to excecute the drafting of players
			draft standardDraft(standardLeague.addMembers(), standardLeague.getQbLimit(), standardLeague.getRbLimit(), standardLeague.getWrLimit(), standardLeague.getTeLimit(), standardLeague.getRoundLimit(), draftType);
			standardDraft.operate(); // function that runs all the other functions in the draft class 


			// at the conclusion of the draft, asks user whether they would like to complete another draft
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

			// outputs rankings from the ppr csv file
			ranking PPRRanking(draftType);
			PPRRanking.originalOperate();


			// calls the custom league class to create a league object for the ppr format
			CustomLeague PPRLeague("", 0);
			std::thread PPRLeagueThread(&CustomLeague::getLeagueInfo, &PPRLeague);
			// Wait for the thread to finish its execution
			PPRLeagueThread.join();


			// calls the draft function to excecute the drafting of players
			draft PPRDraft(PPRLeague.addMembers(), PPRLeague.getQbLimit(), PPRLeague.getRbLimit(), PPRLeague.getWrLimit(), PPRLeague.getTeLimit(), PPRLeague.getRoundLimit(), draftType);
			PPRDraft.operate(); // function that runs all the other functions in the draft class 


			// at the conclusion of the draft, asks user whether they would like to complete another draft
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


		// logic for the half PPR draft format
		else if (draftType == 3)
		{

			// outputs the rankings for the half ppr csv file
			ranking HalfPPRRanking(draftType);
			HalfPPRRanking.originalOperate();

			// calls the custom league class to create a league object for the half ppr format
			CustomLeague HalfPPRLeague("", 0);
			std::thread HalfPPRLeagueThread(&CustomLeague::getLeagueInfo, &HalfPPRLeague);
			// Wait for the thread to finish its execution
			HalfPPRLeagueThread.join();


			// calls the draft function to excecute the drafting of players
			draft HalfPPRDraft(HalfPPRLeague.addMembers(), HalfPPRLeague.getQbLimit(), HalfPPRLeague.getRbLimit(), HalfPPRLeague.getWrLimit(), HalfPPRLeague.getTeLimit(), HalfPPRLeague.getRoundLimit(), draftType);
			HalfPPRDraft.operate(); // function that runs all the other functions in the draft class 


			// at the conclusion of the draft, asks user whether they would like to complete another draft
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
	}



	std::cout << "Number of drafts completed: " << draft::totalDrafts << std::endl; // ouputs total number of drafts completed


	return 0;
}