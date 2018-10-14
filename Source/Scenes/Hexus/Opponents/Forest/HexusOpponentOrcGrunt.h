#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentOrcGrunt : public HexusOpponentData
{
public:
	static HexusOpponentOrcGrunt* getInstance();

private:
	HexusOpponentOrcGrunt();
	~HexusOpponentOrcGrunt();

	static const std::string OpponentSaveKey;
	static HexusOpponentOrcGrunt* instance;
};
