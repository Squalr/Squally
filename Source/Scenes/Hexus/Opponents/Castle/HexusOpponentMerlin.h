#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentMerlin : public HexusOpponentData
{
public:
	static HexusOpponentMerlin* getInstance();

private:
	HexusOpponentMerlin();
	~HexusOpponentMerlin();

	static const std::string OpponentSaveKey;
	static HexusOpponentMerlin* instance;
};
