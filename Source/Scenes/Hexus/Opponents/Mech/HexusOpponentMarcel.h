#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentMarcel : public HexusOpponentData
{
public:
	static HexusOpponentMarcel* getInstance();

private:
	HexusOpponentMarcel();
	~HexusOpponentMarcel();

	static const std::string StringKeyOpponentName;
	static HexusOpponentMarcel* instance;
};
