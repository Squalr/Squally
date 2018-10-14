#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJuniper : public HexusOpponentData
{
public:
	static HexusOpponentJuniper* getInstance();

private:
	HexusOpponentJuniper();
	~HexusOpponentJuniper();

	static const std::string OpponentSaveKey;
	static HexusOpponentJuniper* instance;
};
