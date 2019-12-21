#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class MinMaxPool;
class PlatformerEntity;
class Squally;

class GuanoPickPocketBehavior : public AttachedBehavior
{
public:
	static GuanoPickPocketBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	GuanoPickPocketBehavior(GameObject* owner);
	~GuanoPickPocketBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void tryPickPocket(PlatformerEntity* target, MinMaxPool* pocketPool, std::string pickPocketSaveKey);

	PlatformerEntity* entity;
	bool isPickPocketing;
};
