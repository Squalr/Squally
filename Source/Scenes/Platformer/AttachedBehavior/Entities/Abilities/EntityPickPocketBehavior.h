#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class MinMaxPool;
class PlatformerEntity;
class PocketPoolDeserializer;
class Squally;

class EntityPickPocketBehavior : public AttachedBehavior
{
public:
	static EntityPickPocketBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityPickPocketBehavior(GameObject* owner);
	virtual ~EntityPickPocketBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void attemptPickPocket();
	bool canPickPocket();
	bool wasPickPocketed();
	void onPickPocketed();
	void updateIconVisibility();

	PlatformerEntity* entity;
	Squally* squally;
	MinMaxPool* pocketPool;
	PocketPoolDeserializer* pocketPoolDeserializer;
	cocos2d::Sprite* pickPocketIcon;

	std::string currentHelperName;

	static const std::string SavePropertyKeyWasPickPocketed;
	static const std::string MapKeyPocketPool;
};
