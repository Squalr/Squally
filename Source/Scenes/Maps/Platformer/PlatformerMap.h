#pragma once
#include "cocos2d.h"

#include "Scenes/Maps/MapBase.h"

using namespace cocos2d;

// Forward declarations
class Hud;
class SerializableMap;

class PlatformerMap : public MapBase
{
public:
	static void registerGlobalScene();

protected:
	PlatformerMap();
	~PlatformerMap();

private:
	void initializePositions() override;
	void initializeListeners() override;
	void onEnter() override;

	static PlatformerMap* instance;
};
