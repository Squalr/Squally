#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAspen : public HexusOpponentData
{
public:
	static HexusOpponentAspen* getInstance();

private:
	HexusOpponentAspen();
	~HexusOpponentAspen();

	static const std::string OpponentSaveKey;
	static HexusOpponentAspen* instance;
};
