#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentTutorialB : public HexusOpponentData
{
public:
	static HexusOpponentTutorialB* getInstance();

private:
	HexusOpponentTutorialB();
	~HexusOpponentTutorialB();

	static const std::string OpponentSaveKey;
	static HexusOpponentTutorialB* instance;
};
