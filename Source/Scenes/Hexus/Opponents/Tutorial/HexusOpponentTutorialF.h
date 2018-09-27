#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentTutorialF : public HexusOpponentData
{
public:
	static HexusOpponentTutorialF* getInstance();

private:
	HexusOpponentTutorialF();
	~HexusOpponentTutorialF();

	static const std::string StringKeyOpponentName;
	static HexusOpponentTutorialF* instance;
};
