#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentOrcKing : public HexusOpponentData
{
public:
	static HexusOpponentOrcKing* getInstance();

private:
	HexusOpponentOrcKing();
	~HexusOpponentOrcKing();

	static const std::string StringKeyOpponentName;
	static HexusOpponentOrcKing* instance;
};
