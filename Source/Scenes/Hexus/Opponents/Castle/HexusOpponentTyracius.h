#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentTyracius : public HexusOpponentData
{
public:
	static HexusOpponentTyracius* getInstance();

private:
	HexusOpponentTyracius();
	~HexusOpponentTyracius();

	static const std::string OpponentSaveKey;
	static HexusOpponentTyracius* instance;
};
