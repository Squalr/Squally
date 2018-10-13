#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentXenon : public HexusOpponentData
{
public:
	static HexusOpponentXenon* getInstance();

private:
	HexusOpponentXenon();
	~HexusOpponentXenon();

	static const std::string StringKeyOpponentName;
	static HexusOpponentXenon* instance;
};
