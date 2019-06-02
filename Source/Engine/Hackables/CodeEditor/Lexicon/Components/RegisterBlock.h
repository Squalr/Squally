#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class ConstantString;

class RegisterBlock : public SmartNode
{
public:
	static RegisterBlock* create();

protected:
	RegisterBlock();
	~RegisterBlock();
	
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	cocos2d::Sprite* registerBlock;
	LocalizedLabel* eaxLabel;
	LocalizedLabel* ebxLabel;
	LocalizedLabel* ecxLabel;
	LocalizedLabel* edxLabel;
	LocalizedLabel* ediLabel;
	LocalizedLabel* esiLabel;
	LocalizedLabel* ebpLabel;
	LocalizedLabel* espLabel;
	LocalizedLabel* eipLabel;

	ConstantString* eaxString;
	ConstantString* ebxString;
	ConstantString* ecxString;
	ConstantString* edxString;
	ConstantString* ediString;
	ConstantString* esiString;
	ConstantString* ebpString;
	ConstantString* espString;
	ConstantString* eipString;

	unsigned long eax;
	unsigned long ebx;
	unsigned long ecx;
	unsigned long edx;
	unsigned long edi;
	unsigned long esi;
	unsigned long ebp;
	unsigned long esp;
	unsigned long eip;
};
