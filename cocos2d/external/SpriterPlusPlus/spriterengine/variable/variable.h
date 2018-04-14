#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

namespace SpriterEngine
{

	class UniversalObjectInterface;
	class Animation;

	class Variable
	{
	public:
		enum VariableType {
			VARIABLETYPE_STRING,
			VARIABLETYPE_INT,
			VARIABLETYPE_REAL
		};

		Variable(std::string initialName, VariableType initialVariableType);
		~Variable();

		std::string getName() const;

		UniversalObjectInterface *getNewObjectInfoInstance(bool forEntityInstance = false) const;

		UniversalObjectInterface *getDefaultValue() const;

		VariableType getType();

		void setupDefaultInAnimation(Animation *animation, int objectId, int variableId);

	private:
		std::string name;

		VariableType variableType;

		UniversalObjectInterface *defaultValue;
	};

}

#endif // VARIABLE_H
