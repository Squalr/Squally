#pragma once

#include "Scenes/Maps/MapBase.h"

class CombatMap : public MapBase
{
public:
	static void registerGlobalScene();

protected:
	CombatMap();
	~CombatMap();

private:
	typedef MapBase super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	static CombatMap* instance;
};
