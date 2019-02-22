#pragma once

#include "Scenes/MapBase.h"

class IsometricMap : public MapBase
{
public:
	static IsometricMap* create();

protected:
	IsometricMap();
	~IsometricMap();

private:
	typedef MapBase super;
	void initializePositions() override;
	void initializeListeners() override;
	void onEnter() override;
};
