#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <limits>
#include "FileManager.h"
#include "CommonUtils.h"
#include "Mesh.h"

namespace {
	void parseVtxData(std::istringstream& stringStream, std::vector<utils::VertexData>& vertices);
	void parseVerticeIndex(std::istringstream& stringStream, std::vector<std::vector<int>>& verticeIdx);
}

namespace manager {

	FileManager::Status FileManager::readVertex(std::string fp, utils::Mesh &mesh, utils::Color defCol) {
		std::ifstream is{ fp };
		if (!is) {
			return Status::FILE_OPEN_ERR;
		}

		std::vector<utils::VertexData> vertices;
		std::vector<std::vector<int>> verticeIdx{};

		std::string line{};

		while (!is.eof()) {

			std::getline(is, line);

			std::istringstream stringStream{ line };
			std::string type;
			stringStream >> type;
			
			if (type == "v") {
				parseVtxData(stringStream, vertices);
			} else if (type == "f") {
				parseVerticeIndex(stringStream, verticeIdx);
			}

		}

		mesh = utils::Mesh(vertices, verticeIdx, defCol);


		return Status::READ_OK;
	}
}

namespace {
	void parseVtxData(std::istringstream& stringStream, std::vector<utils::VertexData>& vertices) {
		utils::Vector3D vtx;
		stringStream >> vtx.x;
		stringStream >> vtx.y;
		stringStream >> vtx.z;
		vertices.push_back(utils::VertexData {
			vtx,
			utils::Color {}
		});
	}
	void parseVerticeIndex(std::istringstream& stringStream, std::vector<std::vector<int>>& verticeIdx) {
		

		int vtxIdx, textureIdx, normalIdx;
		std::vector<int> idx;

		
		
		while (!stringStream.eof()) {

			stringStream >> vtxIdx;
			stringStream.ignore(1, '/');
			stringStream >> textureIdx;
			stringStream.ignore(1, '/');
			stringStream >> normalIdx;

			vtxIdx--; textureIdx--; normalIdx--;

			idx.push_back(vtxIdx);

		}

		verticeIdx.push_back(idx);
	
	}
}