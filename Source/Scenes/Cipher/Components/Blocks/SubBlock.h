#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class SubBlock : public BlockBase
{
public:
	static SubBlock* create(bool isToolBoxItem = false);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	SubBlock(bool isToolBoxItem);
	~SubBlock();

	void onEnter() override;
	void initializePositions() override;
};
