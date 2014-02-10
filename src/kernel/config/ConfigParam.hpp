#pragma once

#include <list>
#include <string>

namespace drt
{
class ConfigParam
{
	public:
		class IValue
		{
			public:
				IValue(const std::string &name, bool mendatory, const std::string &defaultValue);
				bool isMendatory() const;
				const std::string getName() const;

				bool isShortcut() const;
				virtual const std::string getDefault() const;
				virtual bool isValid() const =0;

			private:
				const std::string name;
				bool mendatory;
				const std::string defaultValue;
		};

		class BooleanValue: public IValue
		{
			public:
				BooleanValue(const std::string &name, bool defaultValue=true, bool mendatory=true);

				bool isValid() const;
				void setValue(const bool&value);
				virtual bool getValue() const;

			private:
				bool set;
				bool value;
		};

		class StringValue: public IValue
		{
			public:
				StringValue(const std::string &name, const std::string &defaultValue="", bool mendatory=true);

				virtual const std::string getValue() const;
				virtual void setValue(const std::string &);

				bool isValid() const;

			private:
				std::string value;
		};

		ConfigParam &operator<<(IValue*);
		const std::list<IValue *> getItems() const;
		IValue *get(const std::string &name) const;

	private:
		std::list<IValue *> params;
};
}

