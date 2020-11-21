#pragma once

#include "cocos/base/CCInputEvents.h"

#include "Engine/SmartNode.h"

class KSequence : public SmartNode
{
public:
	static KSequence* create(std::vector<cocos2d::InputEvents::KeyCode> sequence, std::function<void()> callback, bool interruptable = true);

protected:
	KSequence(std::vector<cocos2d::InputEvents::KeyCode> sequence, std::function<void()> callback, bool interruptable);
	virtual ~KSequence();

	void onEnter() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void processInput(cocos2d::InputEvents::KeyCode keycode);

	std::vector<cocos2d::InputEvents::KeyCode> sequence;
	std::function<void()> callback;
	bool interruptable;
	bool completed;
	int currentIndex;
};
