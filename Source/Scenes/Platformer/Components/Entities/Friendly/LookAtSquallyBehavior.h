#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;
class Squally;

class LookAtSquallyBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* entity;
	Squally* squally;
};
