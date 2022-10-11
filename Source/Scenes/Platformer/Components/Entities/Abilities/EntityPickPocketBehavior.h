#pragma once

#include "Engine/Components/GameComponent.h"

namespace cocos2d
{
	class Sprite;
}

class MinMaxPool;
class PlatformerEntity;
class PocketPoolDeserializer;
class Squally;

class EntityPickPocketBehavior : public GameComponent
{
public:
	static EntityPickPocketBehavior* create(GameObject* owner);
	
	bool canPickPocket();
	bool wasPickPocketed();

	static const std::string MapKey;

protected:
	EntityPickPocketBehavior(GameObject* owner);
	virtual ~EntityPickPocketBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void attemptPickPocket();
	void onPickPocketed();
	void updateIconVisibility();
	void refreshCursorState();

	PlatformerEntity* entity = nullptr;
	Squally* squally = nullptr;
	MinMaxPool* pocketPool = nullptr;
	PocketPoolDeserializer* pocketPoolDeserializer = nullptr;
	cocos2d::Sprite* pickPocketIcon = nullptr;

	std::string currentHelperName;

	static const std::string SavePropertyKeyWasPickPocketed;
	static const std::string MapKeyPocketPool;
};
