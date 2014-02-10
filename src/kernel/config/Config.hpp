#ifndef DRT_CONFIG

# ifndef DEFAULT_CONFIG
#  define DEFAULT_CONFIG "server.conf"
# endif
# include <string> //std::string

# include "ConfigParam.hpp"

namespace drt
{
class Config
{
	public:
		Config(ConfigParam &usage, int ac, char **av);

		void printUsage() const;
		bool isValid() const;

	private:
		bool parseFile();
		bool parseParam(int ac, char **av);

		bool parseParamShort(char *str);
		int parseParamFull(char **str);

	private:
		const ConfigParam &usage;
		const std::string progName;
		std::string configFile;
		bool valid;
};
}

#endif //DRT_CONFIG
