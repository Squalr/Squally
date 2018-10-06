#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsAres : public HexusOpponentData
{
public:
	static HexusOpponentRuinsAres* getInstance();

private:
	HexusOpponentRuinsAres();
	~HexusOpponentRuinsAres();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsAres* instance;
};
