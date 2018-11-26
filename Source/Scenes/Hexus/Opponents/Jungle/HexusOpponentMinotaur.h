#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentMinotaur : public HexusOpponentData
{
public:
	static HexusOpponentMinotaur* getInstance();

private:
	HexusOpponentMinotaur();
	~HexusOpponentMinotaur();

	static const std::string OpponentSaveKey;
	static HexusOpponentMinotaur* instance;
};
