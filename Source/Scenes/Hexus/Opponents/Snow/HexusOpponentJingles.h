#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentJingles : public HexusOpponentData
{
public:
	static HexusOpponentJingles* getInstance();

private:
	HexusOpponentJingles();
	~HexusOpponentJingles();

	static const std::string OpponentSaveKey;
	static HexusOpponentJingles* instance;
};
