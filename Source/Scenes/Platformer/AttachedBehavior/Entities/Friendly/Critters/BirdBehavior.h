#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class Squally;

class BirdBehavior : public AttachedBehavior
{
public:
	static BirdBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	BirdBehavior(GameObject* owner);
	virtual ~BirdBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void tryPeck();
	void queueNextAction();
	void flyAway();

	PlatformerEntity* entity;
	Squally* squally;
	bool wasStartled;
};
