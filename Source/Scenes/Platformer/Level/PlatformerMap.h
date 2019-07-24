#pragma once

#include "Scenes/MapBase.h"

class Cipher;
class ClickableTextNode;
class CollectablesMenu;
class GameHud;
class InventoryMenu;
class MapMenu;
class PartyMenu;

class PlatformerMap : public MapBase
{
public:
	static PlatformerMap* create(std::string mapResource, std::vector<std::string> mapArgs, std::string transition = "");

	void loadMap(std::string mapResource, std::vector<std::string> args) override;

	static const std::string MapArgClearSavedPosition;

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
	Cipher* getCipherInstance();

	GameHud* gameHud;
	Cipher* cipher;
	CollectablesMenu* collectablesMenu;
	MapMenu* mapMenu;
	PartyMenu* partyMenu;
	InventoryMenu* inventoryMenu;

	std::string transition;
};
