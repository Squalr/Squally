#pragma once

#include "Engine/Components/GameComponent.h"

class ChestBase;
class PlatformerEntity;

// Coordinates shared state between chests and enemies across maps.
// For example, if an enemy dies in one map, it can also be killed in another map.
// If a chest is looted in one, it can appear looted in another.
class MapLinkBehavior : public GameComponent
{
public:
	static MapLinkBehavior* create(GameObject* owner);

	void enablePortal();

	static const std::string MapKey;

protected:
	MapLinkBehavior(GameObject* owner);
	virtual ~MapLinkBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	ChestBase* ownerAsChest = nullptr;
	PlatformerEntity* ownerAsEntity = nullptr;
	std::string mapLinkSaveKey;
};
