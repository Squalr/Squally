#pragma once

#include "Engine/SmartNode.h"

class LocalizedString;

class PlatformerAttack : public SmartNode
{
public:
	virtual PlatformerAttack* clone() = 0;
	virtual LocalizedString* getString() = 0;
	std::string getIconResource();

protected:
	PlatformerAttack(std::string iconResource);
	~PlatformerAttack() = default;

private:
	typedef SmartNode super;

	std::string iconResource;
};
