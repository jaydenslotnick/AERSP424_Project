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

	League(const std::string& name, int numTeams) : leagueName(name), numMembers(numTeams), leagueMembers(numTeams) {}

	virtual ~League() {}


    // virtual functions

    // Pure virtual function for getting league info
    virtual void getLeagueInfo() = 0;

    // Pure virtual function for adding members
    virtual void addMembers() = 0;

    // Accessor function for league name
    std::string getLeagueName() const {
        return leagueName;
    }

    // Virtual functions for getting position limits
    virtual int getQbLimit() const = 0;
    virtual int getRbLimit() const = 0;
    virtual int getWrLimit() const = 0;
    virtual int getTeLimit() const = 0;

};


#endif