#pragma once

#include "Engine/SmartNode.h"

#include "Events/CipherEvents.h"
#include "Engine/Localization/LocalizedLabel.h"

class AsciiLetter;
class ConstantString;
class ClickableTextNode;

class SmartAsciiLabel : public SmartNode
{
public:
	static SmartAsciiLabel* create();

	struct Contrast
	{
		bool doContrast = false;
		unsigned char constrastValue = 0;

		Contrast() { }
		Contrast(unsigned char constrastValue) : doContrast(true), constrastValue(constrastValue) { }
	};

	void setFontSize(LocalizedLabel::FontSize fontSize);
	void loadDisplayValue(unsigned char charValue, CipherEvents::DisplayDataType displayDataType, bool colorize, Contrast contrast = Contrast());

protected:
	SmartAsciiLabel();
	virtual ~SmartAsciiLabel();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef SmartNode super;

	AsciiLetter* asciiLetterLabel = nullptr;
	ConstantString* displayValue = nullptr;
	LocalizedLabel* displayLabel = nullptr;
};
