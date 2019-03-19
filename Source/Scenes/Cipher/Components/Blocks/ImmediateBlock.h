#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class ImmediateBlock : public BlockBase
{
public:
	static ImmediateBlock* create(bool isToolBoxItem = false, bool isStaticObject = false);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	ImmediateBlock(bool isToolBoxItem, bool isStaticObject);
	~ImmediateBlock();

	void onEnter() override;
	void initializePositions() override;
};
