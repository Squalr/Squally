#pragma once
#include "cocos2d.h"

#include "Resources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusOpponentTikiGolem : public HexusOpponentData
{
public:
	static HexusOpponentTikiGolem* getInstance();

private:
	HexusOpponentTikiGolem();
	~HexusOpponentTikiGolem();

	static const std::string OpponentSaveKey;
	static HexusOpponentTikiGolem* instance;
};
