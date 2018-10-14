#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentReanimatedPig : public HexusOpponentData
{
public:
	static HexusOpponentReanimatedPig* getInstance();

private:
	HexusOpponentReanimatedPig();
	~HexusOpponentReanimatedPig();

	static const std::string OpponentSaveKey;
	static HexusOpponentReanimatedPig* instance;
};
