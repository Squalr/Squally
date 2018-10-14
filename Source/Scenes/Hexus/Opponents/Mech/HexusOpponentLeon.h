#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentLeon : public HexusOpponentData
{
public:
	static HexusOpponentLeon* getInstance();

private:
	HexusOpponentLeon();
	~HexusOpponentLeon();

	static const std::string OpponentSaveKey;
	static HexusOpponentLeon* instance;
};
