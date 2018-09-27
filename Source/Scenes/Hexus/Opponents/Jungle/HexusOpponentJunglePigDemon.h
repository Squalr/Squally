#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJunglePigDemon : public HexusOpponentData
{
public:
	static HexusOpponentJunglePigDemon* getInstance();

private:
	HexusOpponentJunglePigDemon();
	~HexusOpponentJunglePigDemon();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJunglePigDemon* instance;
};
