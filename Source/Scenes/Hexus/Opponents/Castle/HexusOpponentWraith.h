#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentWraith : public HexusOpponentData
{
public:
	static HexusOpponentWraith* getInstance();

private:
	HexusOpponentWraith();
	~HexusOpponentWraith();

	static const std::string OpponentSaveKey;
	static HexusOpponentWraith* instance;
};
