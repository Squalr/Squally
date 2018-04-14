#ifndef VARIABLEINSTANCENAMEANDIDMAP_H
#define VARIABLEINSTANCENAMEANDIDMAP_H

#include <vector>
#include <map>

namespace SpriterEngine
{

	class UniversalObjectInterface;
	class Variable;

	typedef std::vector<UniversalObjectInterface*> VariableInstanceVector;
	typedef std::map<std::string, UniversalObjectInterface*> VariableInstanceNameMap;

	class VariableInstanceNameAndIdMap
	{
	public:
		VariableInstanceNameAndIdMap();
		~VariableInstanceNameAndIdMap();

		UniversalObjectInterface *getVariable(int variableIndex);
		UniversalObjectInterface *getVariable(std::string variableName);

		void pushBackVariable(Variable * variable);

		bool isEmpty();

	private:
		VariableInstanceVector variables;
		VariableInstanceNameMap variableNameMap;
	};

}

#endif // VARIABLEINSTANCENAMEANDIDMAP_H
