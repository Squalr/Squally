#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDemonGhost : public HexusOpponentData
{
public:
	static HexusOpponentDemonGhost* getInstance();

private:
	HexusOpponentDemonGhost();
	~HexusOpponentDemonGhost();

	static const std::string OpponentSaveKey;
	static HexusOpponentDemonGhost* instance;
};
