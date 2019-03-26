#pragma once

#include "Engine/SmartNode.h"

#include "Events/CipherEvents.h"

class AsciiLetter;
class ConstantString;
class ClickableTextNode;
class LocalizedLabel;

class SmartAsciiLabel : public SmartNode
{
public:
	static SmartAsciiLabel* create();

	void loadDisplayValue(unsigned char charValue, CipherEvents::DisplayDataType displayDataType);

private:
	typedef SmartNode super;
	SmartAsciiLabel();
	~SmartAsciiLabel();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	AsciiLetter* asciiLetterLabel;
	ConstantString* displayValue;
	LocalizedLabel* displayLabel;
};
