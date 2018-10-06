#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRuinsPoseidon : public HexusOpponentData
{
public:
	static HexusOpponentRuinsPoseidon* getInstance();

private:
	HexusOpponentRuinsPoseidon();
	~HexusOpponentRuinsPoseidon();

	static const std::string StringKeyOpponentName;
	static HexusOpponentRuinsPoseidon* instance;
};
