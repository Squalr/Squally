#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentCentaur : public HexusOpponentData
{
public:
	static HexusOpponentCentaur* getInstance();

private:
	HexusOpponentCentaur();
	~HexusOpponentCentaur();

	static const std::string StringKeyOpponentName;
	static HexusOpponentCentaur* instance;
};
