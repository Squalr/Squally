#pragma once
#include "cocos2d.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentGramps : public HexusOpponentData
{
public:
	static HexusOpponentGramps* getInstance();

private:
	HexusOpponentGramps();
	~HexusOpponentGramps();

	static const std::string OpponentSaveKey;
	static HexusOpponentGramps* instance;
};
