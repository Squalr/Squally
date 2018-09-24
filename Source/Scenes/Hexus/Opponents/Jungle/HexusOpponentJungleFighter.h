#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJungleFighter : public HexusOpponentData
{
public:
	static HexusOpponentJungleFighter* getInstance();

private:
	HexusOpponentJungleFighter();
	~HexusOpponentJungleFighter();

	static const std::string StringKeyOpponentName;
	static HexusOpponentJungleFighter* instance;
};
