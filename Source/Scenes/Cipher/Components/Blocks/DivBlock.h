#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class DivBlock : public BlockBase
{
public:
	static DivBlock* create(bool isToolBoxItem = false);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	DivBlock(bool isToolBoxItem);
	~DivBlock();

	void onEnter() override;
	void initializePositions() override;
};
