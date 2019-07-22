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
	static PlatformerMap* create(std::string mapResource, std::vector<std::string> mapArgs);

	void loadMap(std::string mapResource, std::vector<std::string> args) override;

	static const std::string MapArgClearSavedPosition;

protected:
	PlatformerMap();
	~PlatformerMap();

private:
	typedef MapBase super;
	void initializePositions() override;
	void initializeListeners() override;
	void onEnter() override;
	void onExit() override;
	void update(float dt) override;
	void openCipher();
	void onCipherClose();

	GameHud* gameHud;
	Cipher* cipher;
	CollectablesMenu* collectablesMenu;
	MapMenu* mapMenu;
	PartyMenu* partyMenu;
	InventoryMenu* inventoryMenu;
};
