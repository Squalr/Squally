#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentPoseidon : public HexusOpponentData
{
public:
	static HexusOpponentPoseidon* getInstance();

private:
	HexusOpponentPoseidon();
	~HexusOpponentPoseidon();

	static const std::string OpponentSaveKey;
	static HexusOpponentPoseidon* instance;
};
