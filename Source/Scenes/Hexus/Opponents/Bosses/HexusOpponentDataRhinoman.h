#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDataRhinoman : public HexusOpponentData
{
public:
	static HexusOpponentDataRhinoman* getInstance();

private:
	HexusOpponentDataRhinoman();
	~HexusOpponentDataRhinoman();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDataRhinoman* instance;
};
