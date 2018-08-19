#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Resources.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class IntelliText : public Node
{
public:
	struct IntelliTextItem
	{
		std::string text;
		bool requiresInput;
		std::function<void()> callback;

		IntelliTextItem(std::string text, bool requiresInput, std::function<void()> callback) : text(text), requiresInput(requiresInput), callback(callback)
		{

		}
	};

	static IntelliText * create();
	static IntelliText * create(IntelliTextItem textItem);

	void enqueueText(IntelliTextItem textItem);

private:
	IntelliText();
	~IntelliText();

	RichText* displayedText;
};
