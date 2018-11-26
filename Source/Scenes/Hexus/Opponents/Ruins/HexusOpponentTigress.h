#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentTigress : public HexusOpponentData
{
public:
	static HexusOpponentTigress* getInstance();

private:
	HexusOpponentTigress();
	~HexusOpponentTigress();

	static const std::string OpponentSaveKey;
	static HexusOpponentTigress* instance;
};
