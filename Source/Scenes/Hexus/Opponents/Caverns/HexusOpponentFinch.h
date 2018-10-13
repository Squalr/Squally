#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentFinch : public HexusOpponentData
{
public:
	static HexusOpponentFinch* getInstance();

private:
	HexusOpponentFinch();
	~HexusOpponentFinch();

	static const std::string StringKeyOpponentName;
	static HexusOpponentFinch* instance;
};
