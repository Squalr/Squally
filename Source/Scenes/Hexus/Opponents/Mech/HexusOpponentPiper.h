#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentPiper : public HexusOpponentData
{
public:
	static HexusOpponentPiper* getInstance();

private:
	HexusOpponentPiper();
	~HexusOpponentPiper();

	static const std::string StringKeyOpponentName;
	static HexusOpponentPiper* instance;
};
