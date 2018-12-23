#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentNessie : public HexusOpponentData
{
public:
	static HexusOpponentNessie* getInstance();

private:
	HexusOpponentNessie();
	~HexusOpponentNessie();

	static const std::string OpponentSaveKey;
	static HexusOpponentNessie* instance;
};
