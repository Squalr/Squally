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

	struct Contrast
	{
		bool doContrast;
		unsigned char constrastValue;

		Contrast() : doContrast(false), constrastValue((unsigned char)(0)) { }
		Contrast(unsigned char constrastValue) : doContrast(true), constrastValue(constrastValue) { }
	};

	void loadDisplayValue(unsigned char charValue, CipherEvents::DisplayDataType displayDataType, Contrast contrast = Contrast());

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
