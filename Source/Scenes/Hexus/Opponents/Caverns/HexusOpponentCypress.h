#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentCypress : public HexusOpponentData
{
public:
	static HexusOpponentCypress* getInstance();

private:
	HexusOpponentCypress();
	~HexusOpponentCypress();

	static const std::string StringKeyOpponentName;
	static HexusOpponentCypress* instance;
};
