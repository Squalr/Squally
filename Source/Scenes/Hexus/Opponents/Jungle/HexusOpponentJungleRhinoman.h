#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleRhinoman : public HexusOpponentData
{
public:
	static HexusOpponentJungleRhinoman* getInstance();

private:
	HexusOpponentJungleRhinoman();
	~HexusOpponentJungleRhinoman();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleRhinoman* instance;
};
