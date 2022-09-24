#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class BurchHexusBehavior : public HexusBehaviorBase
{
public:
	static BurchHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	BurchHexusBehavior(GameObject* owner);
	virtual ~BurchHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
