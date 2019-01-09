#pragma once
#include <functional>

#include "cocos/base/CCEventKeyboard.h"

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class Layer;
	class Event;
	class EventCustom;
	class Node;
}

class CodeEditor;
class RadialMenu;

class HackerModeHud : public Hud
{
public:
	static HackerModeHud* create(std::function<void()> toggleHackermodeCallback);

	cocos2d::Layer* hackableObjectsHud;

private:
	typedef Hud super;
	HackerModeHud(std::function<void()> toggleHackermodeCallback);
	virtual ~HackerModeHud();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onRadialMenuClose();
	void registerHackableObject(cocos2d::EventCustom* args);

	CodeEditor* codeEditor;
	RadialMenu* radialMenu;
	std::function<void()> callback;
};

