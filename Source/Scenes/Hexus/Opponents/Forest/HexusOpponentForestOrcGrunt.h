#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentForestOrcGrunt : public HexusOpponentData
{
public:
	static HexusOpponentForestOrcGrunt* getInstance();

private:
	HexusOpponentForestOrcGrunt();
	~HexusOpponentForestOrcGrunt();

	static const std::string StringKeyOpponentName;
	static HexusOpponentForestOrcGrunt* instance;
};
