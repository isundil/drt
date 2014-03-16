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
		class ModuleManager;
	}

	namespace render
	{

		class Scene
		{
			private:
				typedef	struct __attribute__ ((packed))			s_Item
				{
					struct __attribute__ ((packed)) {
						char					moduleID;
						char					subModule;
						short					headerSize;
						unsigned int			nbSubItem;
					} toReceive;
					char					*data;
					std::list<struct s_Item *>	subItems;
					AObject *object;
				}					t_Item;
				typedef struct __attribute__((packed))
				{
					unsigned short width;
					unsigned short height;
					short camera_x;
					short camera_y;
					short camera_z;
					double camera_rx;
					double camera_ry;
					double camera_rz;
					unsigned short d;
					unsigned int		nbObjects;
				} t_metadata;

			public:
				Scene( std::ifstream &, const std::string &path );
				virtual ~Scene();

				unsigned int calc(WorkerManager &, unsigned int x, unsigned int y);
				unsigned int getWidth() const;
				unsigned int getHeight() const;

			private:
				unsigned int height, width;
				Camera	*camera;
				short	d;

				std::map<unsigned int, t_Item *>		objects;

				t_Item *				parseItem( std::ifstream & , module::ModuleManager *, std::map<unsigned int, char [20]>moduleArray);
				const std::string scenePath;

				void copy_bufs(unsigned char dest[4], unsigned char src[3]);
		};
	}
}
