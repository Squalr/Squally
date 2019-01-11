#pragma once

#include "Engine/SmartNode.h"

class HackablePreview : public SmartNode
{
public:
	void setAssemblyTextVisible(bool isVisible);

	virtual HackablePreview* clone() = 0;

protected:
	HackablePreview();
	~HackablePreview() = default;

	cocos2d::Node* assemblyTextNode;
	cocos2d::Node* previewNode;

	static const float PreviewRadius;
	static const cocos2d::Color4B RegisterColor;

private:
	typedef SmartNode super;
};
