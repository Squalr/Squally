#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

class AddBlock;
class AndBlock;
class BlockBase;
class BruteForceBlock;
class CshlBlock;
class CshrBlock;
class DivBlock;
class EqualsBlock;
class GreaterThanBlock;
class GreaterThanOrEqualsBlock;
class ImmediateBlock;
class InvBlock;
class LessThanBlock;
class LessThanOrEqualsBlock;
class LocalizedLabel;
class ModBlock;
class MulBlock;
class NotEqualsBlock;
class OrBlock;
class ScrollPane;
class ShlBlock;
class ShrBlock;
class SplitterBlock;
class SubBlock;
class XorBlock;

class ToolBox : public CipherComponentBase
{
public:
	static ToolBox* create();

protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	ToolBox();
	~ToolBox();

	void onEnter() override;
	void initializePositions() override;

	ScrollPane* scrollPane;
	AddBlock* addBlock;
	AndBlock* andBlock;
	BruteForceBlock* bruteForceBlock;
	CshlBlock* cshlBlock;
	CshrBlock* cshrBlock;
	DivBlock* divBlock;
	EqualsBlock* equalsBlock;
	GreaterThanBlock* greaterThanBlock;
	GreaterThanOrEqualsBlock* greaterThanOrEqualsBlock;
	ImmediateBlock* immediateBlock;
	InvBlock* invBlock;
	LessThanBlock* lessThanBlock;
	LessThanOrEqualsBlock* lessThanOrEqualsBlock;
	ModBlock* modBlock;
	MulBlock* mulBlock;
	NotEqualsBlock* notEqualsBlock;
	OrBlock* orBlock;
	ShlBlock* shlBlock;
	ShrBlock* shrBlock;
	SplitterBlock* splitterBlock;
	SubBlock* subBlock;
	XorBlock* xorBlock;
	LocalizedLabel* cipherToolsLabel;
	LocalizedLabel* specialLabel;
	LocalizedLabel* binaryOperatorsLabel;
	LocalizedLabel* basicOperatorsLabel;
	LocalizedLabel* comparisonLabel;

	std::vector<BlockBase*> specialBlocks;
	std::vector<BlockBase*> binaryOperatorBlocks;
	std::vector<BlockBase*> basicOperatorBlocks;
	std::vector<BlockBase*> comparisonBlocks;
};
