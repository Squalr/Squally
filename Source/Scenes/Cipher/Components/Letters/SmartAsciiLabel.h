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
	static SmartAsciiLabel* create(unsigned char charValue);

	void setValue(unsigned char value);

private:
	typedef SmartNode super;
	SmartAsciiLabel(unsigned char charValue);
	~SmartAsciiLabel();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void loadDisplayValue();

	AsciiLetter* asciiLetterLabel;
	ConstantString* displayValue;
	LocalizedLabel* displayLabel;

	unsigned char charValue;
	CipherEvents::DisplayDataType displayDataType;
};
