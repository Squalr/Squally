#pragma once

#include "Scenes/Platformer/Components/Entities/Friendly/Hexus/HexusBehaviorBase.h"

class CardData;
class MinMaxPool;

class LianaHexusBehavior : public HexusBehaviorBase
{
public:
	static LianaHexusBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	LianaHexusBehavior(GameObject* owner);
	virtual ~LianaHexusBehavior();

	MinMaxPool* generateReward() override;
	std::string getWinLossSaveKey() override;
	std::string getBackgroundResource() override;
	std::vector<CardData*> generateDeck() override;
	StateOverride* getStateOverride() override;
	std::vector<TutorialBase*> getTutorials() override;

private:
	typedef HexusBehaviorBase super;

};
