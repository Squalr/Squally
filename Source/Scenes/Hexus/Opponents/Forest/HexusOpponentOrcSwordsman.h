#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentOrcSwordsman : public HexusOpponentData
{
public:
	static HexusOpponentOrcSwordsman* getInstance();

private:
	HexusOpponentOrcSwordsman();
	~HexusOpponentOrcSwordsman();

	static const std::string OpponentSaveKey;
	static HexusOpponentOrcSwordsman* instance;
};
