#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentSkeletalArcher : public HexusOpponentData
{
public:
	static HexusOpponentSkeletalArcher* getInstance();

private:
	HexusOpponentSkeletalArcher();
	~HexusOpponentSkeletalArcher();

	static const std::string StringKeyOpponentName;
	static HexusOpponentSkeletalArcher* instance;
};
