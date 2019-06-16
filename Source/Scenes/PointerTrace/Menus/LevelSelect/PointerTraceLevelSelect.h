#pragma once

#include "Scenes/MapBase.h"

namespace cocos2d
{
	class Event;
}

class Music;

class PointerTraceLevelSelect  : public MapBase
{
public:
	static void registerGlobalScene();

protected:
	PointerTraceLevelSelect();
	~PointerTraceLevelSelect();

private:
	typedef MapBase super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	Music* music;

	static PointerTraceLevelSelect* instance;
};
