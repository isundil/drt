#ifndef  DRT_CONFIG
# define DRT_CONFIG

# include <string> //std::string
# include "ConfigParam.hpp"
# include "ISection.hpp"

namespace drt
{
	namespace parser
	{
		class UnixParser;
	}
class Config
{
	public:
		Config(ConfigParam &usage);
		~Config();

		template<class Parser> void eval(int ac, char **av);
		void printUsage() const;
		bool isValid() const;
		template <class Section> const Section *getSection() const
		{
			for (auto i = infos.cbegin(); i != infos.cend(); i++)
				if (dynamic_cast<Section const *> (*i) != nullptr)
					return (const Section *)(*i);
			return nullptr;
		}

	private:
		template<class Parser>void parseFile(); //throw
		bool parseParam(int ac, char **av);

		int parseParamFull(char **str);

	private:
		const ConfigParam &usage;
		const std::string progName;
		bool valid;

		std::list<const parser::ISection *> infos;
};
}

#endif //DRT_CONFIG
