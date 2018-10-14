#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDemonWarrior : public HexusOpponentData
{
public:
	static HexusOpponentDemonWarrior* getInstance();

private:
	HexusOpponentDemonWarrior();
	~HexusOpponentDemonWarrior();

	static const std::string OpponentSaveKey;
	static HexusOpponentDemonWarrior* instance;
};
