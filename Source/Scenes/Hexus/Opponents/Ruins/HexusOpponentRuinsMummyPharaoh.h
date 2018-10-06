#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsMummyPharaoh : public HexusOpponentData
{
public:
	static HexusOpponentRuinsMummyPharaoh* getInstance();

private:
	HexusOpponentRuinsMummyPharaoh();
	~HexusOpponentRuinsMummyPharaoh();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsMummyPharaoh* instance;
};
