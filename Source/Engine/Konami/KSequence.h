#pragma once

#include "Engine/SmartNode.h"

class KSequence : public SmartNode
{
public:
	static KSequence* create(std::vector<cocos2d::EventKeyboard::KeyCode> sequence, std::function<void()> callback, bool interruptable = true);

protected:
	KSequence(std::vector<cocos2d::EventKeyboard::KeyCode> sequence, std::function<void()> callback, bool interruptable);
	virtual ~KSequence();

	void onEnter() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void processInput(cocos2d::EventKeyboard::KeyCode keycode);

	std::vector<cocos2d::EventKeyboard::KeyCode> sequence;
	std::function<void()> callback;
	bool interruptable;
	bool completed;
	int currentIndex;
};
