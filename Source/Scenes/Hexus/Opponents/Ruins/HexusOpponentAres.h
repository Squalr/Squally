#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAres : public HexusOpponentData
{
public:
	static HexusOpponentAres* getInstance();

private:
	HexusOpponentAres();
	~HexusOpponentAres();

	static const std::string StringKeyOpponentName;
	static HexusOpponentAres* instance;
};
