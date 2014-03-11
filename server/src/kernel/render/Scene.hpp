#pragma once

#include <list>
#include <string>

namespace drt
{
	namespace network
	{
		class Socket;
	}

	namespace render
	{
	  typedef	struct			s_Item {
	    char				moduleID;
	    char				subModule;
	    short				headerSize;
	    int					nbSubItem;
	    std::list<struct s_Item *>		*subItems;
	  }					t_Item;
	  

		class Scene
		{
			public:
				Scene( std::ifstream & );

			private:
		  std::list<t_Item *> objects;
		  t_Item	*parseItem( std::ifstream & );
		};
	}
}
