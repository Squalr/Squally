#pragma once
#include "cocos/base/CCEventKeyboard.h"

#include "Engine/GlobalScene.h"

namespace cocos2d
{
	class Event;
	class Sprite;
}

class Hud;
class LevelSegment;

class PointerTraceLevelSelect : public GlobalScene
{
public:
	static void registerGlobalScene();

protected:
	PointerTraceLevelSelect();
	~PointerTraceLevelSelect();

private:
	typedef GlobalScene super;
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void addSegment(LevelSegment* levelSegment);
	void stitchSegments();

	cocos2d::Sprite* background;
	cocos2d::Node* segmentsNode;
	Hud* hud;

	std::vector<LevelSegment*> levelSegments;

	static PointerTraceLevelSelect* instance;
};
