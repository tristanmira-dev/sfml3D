#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include "Mesh.h"

namespace manager {
	class FileManager {
		public:

			enum Status {
				READ_OK,
				FILE_OPEN_ERR
			};

			static Status readVertex(std::string fp, utils::Mesh& mesh, utils::Color defCol);


	};
}



#endif


