#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentDataSkeletonKing : public HexusOpponentData
{
public:
	static HexusOpponentDataSkeletonKing* getInstance();

private:
	HexusOpponentDataSkeletonKing();
	~HexusOpponentDataSkeletonKing();

	static const std::string StringKeyOpponentName;
	static HexusOpponentDataSkeletonKing* instance;
};
