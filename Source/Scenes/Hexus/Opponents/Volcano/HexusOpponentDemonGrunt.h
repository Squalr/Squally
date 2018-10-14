#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDemonGrunt : public HexusOpponentData
{
public:
	static HexusOpponentDemonGrunt* getInstance();

private:
	HexusOpponentDemonGrunt();
	~HexusOpponentDemonGrunt();

	static const std::string OpponentSaveKey;
	static HexusOpponentDemonGrunt* instance;
};
