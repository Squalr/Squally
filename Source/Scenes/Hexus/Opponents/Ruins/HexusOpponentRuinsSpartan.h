#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsSpartan : public HexusOpponentData
{
public:
	static HexusOpponentRuinsSpartan* getInstance();

private:
	HexusOpponentRuinsSpartan();
	~HexusOpponentRuinsSpartan();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsSpartan* instance;
};
