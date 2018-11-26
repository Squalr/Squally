#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentRhinoman : public HexusOpponentData
{
public:
	static HexusOpponentRhinoman* getInstance();

private:
	HexusOpponentRhinoman();
	~HexusOpponentRhinoman();

	static const std::string OpponentSaveKey;
	static HexusOpponentRhinoman* instance;
};
