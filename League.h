#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifndef LEAGUE_H
#define LEAGUE_H

class League {

protected:
	int numMembers;
	std::string leagueName;
	std::vector<std::string> leagueMembers;

public:

    // constructor, pass in league name and number of teams
	League(const std::string& name, int numTeams) : leagueName(name), numMembers(numTeams){}

	virtual ~League() {}


    // virtual functions

    // Pure virtual function for getting league info
    virtual void getLeagueInfo() = 0;

    // Pure virtual function for adding members
    virtual std::vector<std::string> addMembers() = 0;

    // Accessor function for league name
    std::string getLeagueName() const {
        return leagueName;
    }

    // Virtual functions for getting position limits
    virtual int getQbLimit() = 0;
    virtual int getRbLimit() = 0;
    virtual int getWrLimit() = 0;
    virtual int getTeLimit() = 0;
    virtual int getRoundLimit() = 0;

};


#endif