#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class EaxPtrJmp : public HackableObject
{
public:
	static EaxPtrJmp* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyEaxPtrJmp;

protected:
	EaxPtrJmp(cocos2d::ValueMap& initProperties);
	~EaxPtrJmp();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackableObject super;

	cocos2d::Sprite* marker;
};
