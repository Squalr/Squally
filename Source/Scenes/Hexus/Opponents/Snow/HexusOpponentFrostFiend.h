#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentFrostFiend : public HexusOpponentData
{
public:
	static HexusOpponentFrostFiend* getInstance();

private:
	HexusOpponentFrostFiend();
	~HexusOpponentFrostFiend();

	static const std::string OpponentSaveKey;
	static HexusOpponentFrostFiend* instance;
};
