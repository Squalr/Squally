#pragma once

#include "Scenes/MapBase.h"

class PointerTraceMap : public MapBase
{
public:
	static void registerGlobalScene();

protected:
	PointerTraceMap();
	~PointerTraceMap();

private:
	typedef MapBase super;
	void initializePositions() override;
	void initializeListeners() override;
	void onEnter() override;

	static PointerTraceMap* instance;
};
