#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentNecron : public HexusOpponentData
{
public:
	static HexusOpponentNecron* getInstance();

private:
	HexusOpponentNecron();
	~HexusOpponentNecron();

	static const std::string OpponentSaveKey;
	static HexusOpponentNecron* instance;
};
