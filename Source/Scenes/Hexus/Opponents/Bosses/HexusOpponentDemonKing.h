#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDemonKing : public HexusOpponentData
{
public:
	static HexusOpponentDemonKing* getInstance();

private:
	HexusOpponentDemonKing();
	~HexusOpponentDemonKing();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDemonKing* instance;
};
