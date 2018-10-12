#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentScarecrow : public HexusOpponentData
{
public:
	static HexusOpponentScarecrow* getInstance();

private:
	HexusOpponentScarecrow();
	~HexusOpponentScarecrow();

	static const std::string StringKeyOpponentName;
	static HexusOpponentScarecrow* instance;
};
