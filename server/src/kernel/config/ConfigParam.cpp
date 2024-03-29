#include "ConfigParam.hpp"

using namespace drt;

ConfigParam::IValue::IValue(const std::string &n, bool m, const std::string &d): name(n), mendatory(m), defaultValue(d)
{ }

bool ConfigParam::IValue::isMendatory() const
{ return mendatory; }

const std::string ConfigParam::IValue::getDefault() const
{ return defaultValue; }

const std::string ConfigParam::IValue::getName() const
{ return name; }

ConfigParam::BooleanValue::BooleanValue(const std::string &n, bool d, bool m): IValue(n, m, d ? "true" : "false"), set(false), value(d), defaultBool(d)
{ }

ConfigParam::StringValue::StringValue(const std::string &n, const std::string &d, bool m): IValue(n, m, d), value(d)
{ }

ConfigParam::BooleanValue::BooleanValue(const BooleanValue &o): BooleanValue(o.name, o.defaultBool, o.mendatory)
{ }

ConfigParam::StringValue::StringValue(const StringValue &o): StringValue(o.name, o.defaultValue, o.mendatory)
{ }

ConfigParam::IValue *ConfigParam::StringValue::clone() const
{ return new ConfigParam::StringValue(*this); }

ConfigParam::IValue *ConfigParam::BooleanValue::clone() const
{ return new ConfigParam::BooleanValue(*this); }

const std::string ConfigParam::StringValue::getValue() const
{ return value; }

void ConfigParam::StringValue::setValue(const std::string &v)
{ value = v; }

bool ConfigParam::BooleanValue::getValue() const
{ return value; }

void ConfigParam::BooleanValue::setValue(const bool &v)
{ value = v; }

bool ConfigParam::IValue::isShortcut() const
{
	return this->name.length() == 1;
}

bool ConfigParam::StringValue::isValid() const
{
	if (!isMendatory()) return true;
	return value == "";
}

bool ConfigParam::BooleanValue::isValid() const
{
	if (!isMendatory()) return true;
	return set == true;
}

ConfigParam::~ConfigParam()
{
	for (auto i = params.cbegin(); i != params.cend(); i++)
		delete (*i);
}

const std::list<ConfigParam::IValue *> ConfigParam::getItems() const
{ return params; }

ConfigParam::IValue *ConfigParam::get(const std::string &name) const
{
	for (auto param = params.cbegin(); param != params.cend(); param++)
		if ((*param)->getName() == name)
			return (*param);
	return nullptr;
}

ConfigParam &ConfigParam::operator<<(const ConfigParam::IValue &item)
{
	params.push_back(item.clone());
	return *this;
}

