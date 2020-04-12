#pragma once

#include "Engine/SmartNode.h"
#include "Engine/Hackables/HackableCode.h"

class ConstantString;
class LocalizedLabel;

class HackablePreview : public SmartNode
{
public:
	void setAssemblyTextVisible(bool isVisible);

	virtual HackablePreview* clone() = 0;

protected:
	HackablePreview();
	virtual ~HackablePreview();

	LocalizedLabel* createRegisterEqualsValueLabel(HackableCode::Register reg, bool isPointer, ConstantString* value);
	LocalizedString* getRegisterString(HackableCode::Register reg);

	cocos2d::Node* assemblyTextNode;
	cocos2d::Node* previewNode;

	static const float PreviewRadius;
	static const cocos2d::Color4B RegisterColor;

private:
	typedef SmartNode super;
};
