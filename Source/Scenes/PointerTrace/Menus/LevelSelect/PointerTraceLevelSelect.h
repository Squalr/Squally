#pragma once
#include "cocos/base/CCEventKeyboard.h"

#include "Scenes/MapBase.h"

namespace cocos2d
{
	class Event;
}

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
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	static PointerTraceLevelSelect* instance;
};
