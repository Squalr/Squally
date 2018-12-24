#pragma once

#include "Scenes/Maps/MapBase.h"

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
	void update(float dt) override;

	static PlatformerMap* instance;
};
