#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class OliveHexusBehavior : public HexusBehaviorBase
{
public:
	static OliveHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	OliveHexusBehavior(GameObject* owner);
	virtual ~OliveHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
