#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class MatuHexusBehavior : public HexusBehaviorBase
{
public:
	static MatuHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	MatuHexusBehavior(GameObject* owner);
	virtual ~MatuHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
