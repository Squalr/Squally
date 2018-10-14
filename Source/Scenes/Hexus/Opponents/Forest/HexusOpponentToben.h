#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentToben : public HexusOpponentData
{
public:
	static HexusOpponentToben* getInstance();

private:
	HexusOpponentToben();
	~HexusOpponentToben();

	static const std::string OpponentSaveKey;
	static HexusOpponentToben* instance;
};
