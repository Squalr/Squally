#pragma once

#include "Engine/Components/GameComponent.h"

class CollisionObject;
class DialogueOption;
class MayanDoor;
class PlatformerEntity;
class Scrappy;
class Squally;

class SeagullPuzzleBehavior : public GameComponent
{
public:
	static SeagullPuzzleBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SeagullPuzzleBehavior(GameObject* owner);
	virtual ~SeagullPuzzleBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;
	
	void onPuzzleSolved();

	PlatformerEntity* entity = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
