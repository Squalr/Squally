#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsMedusa : public HexusOpponentData
{
public:
	static HexusOpponentRuinsMedusa* getInstance();

private:
	HexusOpponentRuinsMedusa();
	~HexusOpponentRuinsMedusa();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsMedusa* instance;
};
