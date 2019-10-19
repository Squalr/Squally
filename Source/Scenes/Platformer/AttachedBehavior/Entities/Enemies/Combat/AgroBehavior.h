#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class Squally;

class AgroBehavior : public AttachedBehavior
{
public:
	static AgroBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	AgroBehavior(GameObject* owner);
	~AgroBehavior();

	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	Squally* squally;
};
