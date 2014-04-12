#pragma once

#include <list>
#include <string>
#include <map>
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
		public:
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

					~s_Item();
				}					t_Item;
			private:
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
				Scene( std::ifstream &, const std::string &path);
				Scene(Scene &);
				virtual ~Scene();

				unsigned int calc(WorkerManager &, unsigned int x, unsigned int y);
				unsigned int getWidth() const;
				unsigned int getHeight() const;

		  std::map<unsigned int, t_Item *>	getObjects() const {return objects;};

				const std::string getPath() const;
				unsigned short getId() const;
				void setId(unsigned short id);

		  Camera	*getCamera() const {return camera;}
		  short		getD() const {return d;}
		  Scene	*clone();

			private:
				unsigned int height, width;
				Camera	*camera;
				short	d;
				unsigned short id;

				std::map<unsigned int, t_Item *>		objects;

				t_Item *				parseItem( std::ifstream & , module::ModuleManager *, std::map<unsigned int, char [20]>moduleArray);
				const std::string scenePath;

				void copy_bufs(unsigned char dest[4], unsigned char src[3]);
		};
	}
}
