#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsTigress : public HexusOpponentData
{
public:
	static HexusOpponentRuinsTigress* getInstance();

private:
	HexusOpponentRuinsTigress();
	~HexusOpponentRuinsTigress();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsTigress* instance;
};
