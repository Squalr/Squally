#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDataDemonKing : public HexusOpponentData
{
public:
	static HexusOpponentDataDemonKing* getInstance();

private:
	HexusOpponentDataDemonKing();
	~HexusOpponentDataDemonKing();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDataDemonKing* instance;
};
