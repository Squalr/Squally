#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class CleopatraHexusBehavior : public HexusBehaviorBase
{
public:
	static CleopatraHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	CleopatraHexusBehavior(GameObject* owner);
	virtual ~CleopatraHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
