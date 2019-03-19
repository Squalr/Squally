#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class InvBlock : public BlockBase
{
public:
	static InvBlock* create(bool isToolBoxItem = false);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	InvBlock(bool isToolBoxItem);
	~InvBlock();

	void onEnter() override;
	void initializePositions() override;
};
