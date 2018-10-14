#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentOrcBomber : public HexusOpponentData
{
public:
	static HexusOpponentOrcBomber* getInstance();

private:
	HexusOpponentOrcBomber();
	~HexusOpponentOrcBomber();

	static const std::string OpponentSaveKey;
	static HexusOpponentOrcBomber* instance;
};
