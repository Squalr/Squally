#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentChiron : public HexusOpponentData
{
public:
	static HexusOpponentChiron* getInstance();

private:
	HexusOpponentChiron();
	~HexusOpponentChiron();

	static const std::string StringKeyOpponentName;
	static HexusOpponentChiron* instance;
};
