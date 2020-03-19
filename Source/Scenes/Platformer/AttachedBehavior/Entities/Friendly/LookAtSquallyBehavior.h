#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class Squally;

class LookAtSquallyBehavior : public AttachedBehavior
{
public:
	static LookAtSquallyBehavior* create(GameObject* owner);

	static const std::string MapKey;
	static const std::string MapKeyAlias;

protected:
	LookAtSquallyBehavior(GameObject* owner);
	virtual ~LookAtSquallyBehavior();

	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	Squally* squally;
};
