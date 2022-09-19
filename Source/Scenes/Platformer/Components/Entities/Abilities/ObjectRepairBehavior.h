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

class ObjectRepairBehavior : public GameComponent
{
public:
	static ObjectRepairBehavior* create(GameObject* owner);
	
	bool canRepair();
	bool wasRepaired();

	static const std::string MapKey;

protected:
	ObjectRepairBehavior(GameObject* owner);
	virtual ~ObjectRepairBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void attemptRepair();
	void onRepaired();
	void updateIconVisibility();
	void refreshCursorState();

	Squally* squally = nullptr;
	cocos2d::Sprite* repairIcon = nullptr;
	std::string repairEvent;

	std::string currentHelperName;

	static const std::string SavePropertyKeyWasRepaired;
	static const std::string MapKeyRepairEvent;
};
