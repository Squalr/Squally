#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentVoidDemon : public HexusOpponentData
{
public:
	static HexusOpponentVoidDemon* getInstance();

private:
	HexusOpponentVoidDemon();
	~HexusOpponentVoidDemon();

	static const std::string OpponentSaveKey;
	static HexusOpponentVoidDemon* instance;
};
