#pragma once

#include <list>
#include <string>
// #include "../modules/includes/IObject.hh"
#include "../../modules/includes/IObject.hh"
// #include "../modules/includes/AObject.hpp"
#include "../../modules/includes/AObject.hpp"
// #include "worker/WorkerManager.hpp"
#include "../worker/WorkerManager.hpp"
// #include "modules/ModuleManager.hpp"
#include "../modules/ModuleManager.hpp"
// #include "modules/AModule.hpp"
#include "../modules/AModule.hpp"

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
      std::list<AObject *>		_objects;

      t_Item				*parseItem( std::ifstream & );
    };
  }
}
