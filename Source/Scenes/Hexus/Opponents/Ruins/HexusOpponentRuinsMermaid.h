#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsMermaid : public HexusOpponentData
{
public:
	static HexusOpponentRuinsMermaid* getInstance();

private:
	HexusOpponentRuinsMermaid();
	~HexusOpponentRuinsMermaid();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsMermaid* instance;
};
