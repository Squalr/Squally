#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRobin : public HexusOpponentData
{
public:
	static HexusOpponentRobin* getInstance();

private:
	HexusOpponentRobin();
	~HexusOpponentRobin();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRobin* instance;
};
