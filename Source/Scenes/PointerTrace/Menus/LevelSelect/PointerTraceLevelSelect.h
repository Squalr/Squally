#pragma once

#include "Scenes/MapBase.h"

class PointerTraceLevelSelect  : public MapBase
{
public:
	static PointerTraceLevelSelect* getInstance();

protected:
	PointerTraceLevelSelect();
	virtual ~PointerTraceLevelSelect();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef MapBase super;

	static PointerTraceLevelSelect* instance;
};
