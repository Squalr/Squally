#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentGarin : public HexusOpponentData
{
public:
	static HexusOpponentGarin* getInstance();

private:
	HexusOpponentGarin();
	~HexusOpponentGarin();

	static const std::string StringKeyOpponentName;
	static HexusOpponentGarin* instance;
};
