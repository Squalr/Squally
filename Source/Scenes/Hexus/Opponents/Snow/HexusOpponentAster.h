#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentAster : public HexusOpponentData
{
public:
	static HexusOpponentAster* getInstance();

private:
	HexusOpponentAster();
	~HexusOpponentAster();

	static const std::string OpponentSaveKey;
	static HexusOpponentAster* instance;
};
