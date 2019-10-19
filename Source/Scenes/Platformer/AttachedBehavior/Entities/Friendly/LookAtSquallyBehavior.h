#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerFriendly;
class Squally;

class LookAtSquallyBehavior : public AttachedBehavior
{
public:
	static LookAtSquallyBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	LookAtSquallyBehavior(GameObject* owner);
	~LookAtSquallyBehavior();

	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	PlatformerFriendly* npc;
	Squally* squally;
};
