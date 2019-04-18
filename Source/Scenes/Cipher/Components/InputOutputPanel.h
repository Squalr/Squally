#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class CipherState;
class ClickableNode;
class SmartAsciiLabel;

class InputOutputPanel : public SmartNode
{
public:
	static InputOutputPanel* create(unsigned char input, unsigned char output, std::function<void(InputOutputPanel*)> selectCallback);

	void enableInteraction();
	void disableInteraction();
	void setStatusPassed();
	void setStatusFailed();
	void clearStatus();

private:
	typedef SmartNode super;
	InputOutputPanel(unsigned char input, unsigned char output, std::function<void(InputOutputPanel*)> selectCallback);
	~InputOutputPanel();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	ClickableNode* panel;
	SmartAsciiLabel* inputLabel;
	SmartAsciiLabel* outputLabel;
	cocos2d::Sprite* failedIcon;
	cocos2d::Sprite* passedIcon;

	unsigned char input;
	unsigned char output;
	std::function<void(InputOutputPanel*)> selectCallback;
};
