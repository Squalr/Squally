#pragma once

#include "Scenes/MapBase.h"

class IsometricMap : public MapBase
{
public:
	static void registerGlobalScene();
	void loadMap(SerializableMap* levelMap) override;

protected:
	IsometricMap();
	~IsometricMap();

private:
	typedef MapBase super;
	void initializePositions() override;
	void initializeListeners() override;
	void onEnter() override;

	static IsometricMap* instance;
};
