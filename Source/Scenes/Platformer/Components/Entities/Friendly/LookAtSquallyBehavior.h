#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class Squally;

class LookAtSquallyBehavior : public GameComponent
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
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
	Squally* squally = nullptr;
};
