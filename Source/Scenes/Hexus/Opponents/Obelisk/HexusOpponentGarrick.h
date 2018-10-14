#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentGarrick : public HexusOpponentData
{
public:
	static HexusOpponentGarrick* getInstance();

private:
	HexusOpponentGarrick();
	~HexusOpponentGarrick();

	static const std::string OpponentSaveKey;
	static HexusOpponentGarrick* instance;
};
