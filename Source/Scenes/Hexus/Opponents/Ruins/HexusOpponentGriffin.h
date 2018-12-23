#pragma once
#include <string>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"


class HexusOpponentGriffin : public HexusOpponentData
{
public:
	static HexusOpponentGriffin* getInstance();

private:
	HexusOpponentGriffin();
	~HexusOpponentGriffin();

	static const std::string OpponentSaveKey;
	static HexusOpponentGriffin* instance;
};
