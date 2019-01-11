#pragma once
#include <string>

#include "Engine/SmartNode.h"

class HackablePreview;
class LocalizedString;

class HackableAttribute : public SmartNode
{
public:
	std::string getIconResource();
	LocalizedString* getName();
	HackablePreview* getHackablePreview();

protected:
	HackableAttribute(std::string iconResource, LocalizedString* name, HackablePreview* hackablePreview);
	virtual ~HackableAttribute();

private:
	typedef SmartNode super;

	LocalizedString* name;
	std::string iconResource;
	HackablePreview* hackablePreview;
};
