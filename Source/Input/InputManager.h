#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class InputManager : public Node
{
public:
	static InputManager * ClaimInstance();
	static InputManager * GetInstance();

	bool IsKeyJustPressed(EventKeyboard::KeyCode keyCode);
	bool IsPressed(EventKeyboard::KeyCode keyCode);
	bool IsReleased(EventKeyboard::KeyCode keyCode);

private:
	InputManager();
	~InputManager();

	void InitializeListeners();

	void update(float dt) override;
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	std::unordered_map<EventKeyboard::KeyCode, bool>* pressedKeysPrevious;
	std::unordered_map<EventKeyboard::KeyCode, bool>* pressedKeys;

	static InputManager * inputManagerInstance;
};
