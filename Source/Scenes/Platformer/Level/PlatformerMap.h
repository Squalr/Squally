#pragma once

#include "Scenes/MapBase.h"

class Cipher;
class ClickableTextNode;
class CollectablesMenu;
class GameHud;
class InventoryMenu;
class MapMenu;
class NotificationHud;
class PartyMenu;

class PlatformerMap : public MapBase
{
public:
	static PlatformerMap* create(std::string mapResource, std::string transition = "");

	bool loadMap(std::string mapResource) override;

protected:
	PlatformerMap(std::string transition = "");
	~PlatformerMap();

private:
	typedef MapBase super;
	void initializePositions() override;
	void initializeListeners() override;
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void onExit() override;
	void update(float dt) override;

	GameHud* gameHud;
	NotificationHud* notificationHud;
	Cipher* cipher;
	CollectablesMenu* collectablesMenu;
	MapMenu* mapMenu;
	PartyMenu* partyMenu;
	InventoryMenu* inventoryMenu;

	std::string transition;
};
