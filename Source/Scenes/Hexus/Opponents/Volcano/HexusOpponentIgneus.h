#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentIgneus : public HexusOpponentData
{
public:
	static HexusOpponentIgneus* getInstance();

private:
	HexusOpponentIgneus();
	~HexusOpponentIgneus();

	static const std::string OpponentSaveKey;
	static HexusOpponentIgneus* instance;
};
