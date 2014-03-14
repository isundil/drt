#pragma once

#include <list>
#include <string>
#include "IObject.hh"
#include "AObject.hpp"
#include "camera.hpp"
#include "ray.hpp"
#include "worker/WorkerManager.hpp"
#include "modules/ModuleManager.hpp"
#include "modules/AModule.hpp"

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
      Scene( std::ifstream &, const std::string &path );
      virtual ~Scene();

      unsigned int calc(WorkerManager &, unsigned int x, unsigned int y);
      unsigned int getWidth() const;
      unsigned int getHeight() const;

    private:
      unsigned int height, width;
      Camera	*camera;
      double	d;
      
      std::list<t_Item *>		objects;
      std::list<AObject *>		_objects;

      t_Item				*parseItem( std::ifstream & );
      const std::string scenePath;

      void copy_bufs(unsigned char dest[4], unsigned char src[3]);
    };
  }
}
