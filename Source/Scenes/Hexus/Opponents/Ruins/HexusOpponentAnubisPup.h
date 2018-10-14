#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAnubisPup : public HexusOpponentData
{
public:
	static HexusOpponentAnubisPup* getInstance();

private:
	HexusOpponentAnubisPup();
	~HexusOpponentAnubisPup();

	static const std::string OpponentSaveKey;
	static HexusOpponentAnubisPup* instance;
};
