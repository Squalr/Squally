#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsMinotaur : public HexusOpponentData
{
public:
	static HexusOpponentRuinsMinotaur* getInstance();

private:
	HexusOpponentRuinsMinotaur();
	~HexusOpponentRuinsMinotaur();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsMinotaur* instance;
};
