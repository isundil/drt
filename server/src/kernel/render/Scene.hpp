#pragma once

#include <list>
#include <string>
#include "../modules/includes/IObject.hh"

namespace drt
{
  namespace network
  {
    class Socket;
  }

  namespace render
  {
     typedef	struct __attribute__ ((packed))			s_Item {
      char				moduleID;
      char				subModule;
      short				headerSize;
      unsigned int			nbSubItem;
      char				*data;
      std::list<struct s_Item *>	*subItems;
    }					t_Item;

    class Scene
    {
    public:
      Scene( std::ifstream & );

    private:
      std::list<t_Item *>		objects;
      std::list<IObject *>		_objects;

      t_Item				*parseItem( std::ifstream & );
    };
  }
}
