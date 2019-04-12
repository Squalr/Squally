#pragma once

#include "Scenes/MapBase.h"

class Cipher;
class GameHud;

class PlatformerMap : public MapBase
{
public:
	static void registerGlobalScene();
	void loadMap(SerializableMap* levelMap) override;

protected:
	PlatformerMap();
	~PlatformerMap();

private:
	typedef MapBase super;
	void initializePositions() override;
	void initializeListeners() override;
	void onEnter() override;
	void update(float dt) override;
	void openCipher();
	void onCipherClose();

	GameHud* gameHud;
	Cipher* cipher;

	static PlatformerMap* instance;
};
