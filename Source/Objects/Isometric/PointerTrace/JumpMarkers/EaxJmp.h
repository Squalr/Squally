#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class EaxJmp : public HackableObject
{
public:
	static EaxJmp* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyEaxJmp;

protected:
	EaxJmp(cocos2d::ValueMap& initProperties);
	~EaxJmp();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackableObject super;

	cocos2d::Sprite* marker;
};
