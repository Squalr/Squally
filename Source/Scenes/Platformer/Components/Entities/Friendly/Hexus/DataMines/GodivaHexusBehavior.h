#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class GodivaHexusBehavior : public HexusBehaviorBase
{
public:
	static GodivaHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GodivaHexusBehavior(GameObject* owner);
	virtual ~GodivaHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
