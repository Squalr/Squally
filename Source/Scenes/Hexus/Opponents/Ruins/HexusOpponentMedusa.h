#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentMedusa : public HexusOpponentData
{
public:
	static HexusOpponentMedusa* getInstance();

private:
	HexusOpponentMedusa();
	~HexusOpponentMedusa();

	static const std::string OpponentSaveKey;
	static HexusOpponentMedusa* instance;
};
