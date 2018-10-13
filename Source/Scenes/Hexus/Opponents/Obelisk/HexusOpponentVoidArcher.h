#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentVoidArcher : public HexusOpponentData
{
public:
	static HexusOpponentVoidArcher* getInstance();

private:
	HexusOpponentVoidArcher();
	~HexusOpponentVoidArcher();

	static const std::string StringKeyOpponentName;
	static HexusOpponentVoidArcher* instance;
};
