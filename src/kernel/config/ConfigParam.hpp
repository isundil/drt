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
				virtual ~IValue() { };

				bool isMendatory() const;
				const std::string getName() const;

				bool isShortcut() const;
				virtual const std::string getDefault() const;

				virtual IValue *clone() const =0;
				virtual bool isValid() const =0;

			protected:
				const std::string name;
				bool mendatory;
				const std::string defaultValue;
		};

		class BooleanValue: public IValue
		{
			public:
				BooleanValue(const std::string &name, bool defaultValue=true, bool mendatory=true);
				BooleanValue(const BooleanValue &);

				bool isValid() const;
				void setValue(const bool&value);
				virtual bool getValue() const;
				virtual IValue *clone() const;

			private:
				bool set;
				bool value;
				bool defaultBool;
		};

		class StringValue: public IValue
		{
			public:
				StringValue(const std::string &name, const std::string &defaultValue="", bool mendatory=true);
				StringValue(const StringValue &);

				virtual const std::string getValue() const;
				virtual void setValue(const std::string &);

				bool isValid() const;
				IValue *clone() const;

			private:
				std::string value;
		};

		~ConfigParam();
		ConfigParam &operator<<(const IValue &);
		const std::list<IValue *> getItems() const;
		IValue *get(const std::string &name) const;

	private:
		std::list<IValue *> params;
};
}

