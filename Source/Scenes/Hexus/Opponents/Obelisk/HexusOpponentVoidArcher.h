#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentVoidArcher : public HexusOpponentData
{
public:
	static HexusOpponentVoidArcher* getInstance();

private:
	HexusOpponentVoidArcher();
	~HexusOpponentVoidArcher();

	static const std::string OpponentSaveKey;
	static HexusOpponentVoidArcher* instance;
};
