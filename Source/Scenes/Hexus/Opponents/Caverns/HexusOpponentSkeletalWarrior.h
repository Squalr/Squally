#pragma once
#include "cocos2d.h"

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentSkeletalWarrior : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalWarrior* getInstance();

private:
	HexusOpponentSkeletalWarrior();
	~HexusOpponentSkeletalWarrior();

	static const std::string OpponentSaveKey;
	static HexusOpponentSkeletalWarrior* instance;
};
