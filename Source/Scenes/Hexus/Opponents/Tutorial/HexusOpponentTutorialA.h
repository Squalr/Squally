#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentTutorialA : public HexusOpponentData
{
public:
	static HexusOpponentTutorialA* getInstance();

private:
	HexusOpponentTutorialA();
	~HexusOpponentTutorialA();

	static const std::string OpponentSaveKey;
	static HexusOpponentTutorialA* instance;
};
