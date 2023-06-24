#pragma once

#include "Engine/Components/GameComponent.h"

class CollisionObject;
class DialogueOption;
class MayanDoor;
class PlatformerEntity;
class Scrappy;
class Squally;

class GullPuzzleBehavior : public GameComponent
{
public:
	static GullPuzzleBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GullPuzzleBehavior(GameObject* owner);
	virtual ~GullPuzzleBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;
	
	void onPuzzleSolved();

	CollisionObject* pillarCollision = nullptr;
};
