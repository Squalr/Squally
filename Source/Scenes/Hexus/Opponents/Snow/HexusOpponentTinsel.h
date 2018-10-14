#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentTinsel : public HexusOpponentData
{
public:
	static HexusOpponentTinsel* getInstance();

private:
	HexusOpponentTinsel();
	~HexusOpponentTinsel();

	static const std::string OpponentSaveKey;
	static HexusOpponentTinsel* instance;
};
