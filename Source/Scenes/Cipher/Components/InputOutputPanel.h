#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class CipherState;
class ClickableNode;
class LocalizedLabel;

class InputOutputPanel : public SmartNode
{
public:
	static InputOutputPanel* create(std::string input, std::string output, std::function<void(InputOutputPanel*)> selectCallback);

	void enableInteraction();
	void disableInteraction();
	void setStatusPassed();
	void setStatusFailed();
	void clearStatus();

private:
	typedef SmartNode super;
	InputOutputPanel(std::string input, std::string output, std::function<void(InputOutputPanel*)> selectCallback);
	~InputOutputPanel();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	ClickableNode* panel;
	LocalizedLabel* inputLabel;
	LocalizedLabel* outputLabel;
	cocos2d::Sprite* failedIcon;
	cocos2d::Sprite* passedIcon;

	std::string input;
	std::string output;
	std::function<void(InputOutputPanel*)> selectCallback;
};
