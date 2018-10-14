#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRupert : public HexusOpponentData
{
public:
	static HexusOpponentRupert* getInstance();

private:
	HexusOpponentRupert();
	~HexusOpponentRupert();

	static const std::string OpponentSaveKey;
	static HexusOpponentRupert* instance;
};
