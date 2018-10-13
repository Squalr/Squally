#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentPenguinGrunt : public HexusOpponentData
{
public:
	static HexusOpponentPenguinGrunt* getInstance();

private:
	HexusOpponentPenguinGrunt();
	~HexusOpponentPenguinGrunt();

	static const std::string StringKeyOpponentName;
	static HexusOpponentPenguinGrunt* instance;
};
