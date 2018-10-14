#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentHorus : public HexusOpponentData
{
public:
	static HexusOpponentHorus* getInstance();

private:
	HexusOpponentHorus();
	~HexusOpponentHorus();

	static const std::string OpponentSaveKey;
	static HexusOpponentHorus* instance;
};
