#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentSkeletonKing : public HexusOpponentData
{
public:
	static HexusOpponentSkeletonKing* getInstance();

private:
	HexusOpponentSkeletonKing();
	~HexusOpponentSkeletonKing();

	static const std::string StringKeyOpponentName;
	static HexusOpponentSkeletonKing* instance;
};
