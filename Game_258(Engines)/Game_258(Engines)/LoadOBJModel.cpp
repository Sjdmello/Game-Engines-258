#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel(): vertices(std::vector<glm::vec3>()), normals(std::vector<glm::vec3>()),
textureCoords(std::vector<glm::vec2>()), indices(std::vector<unsigned int>()), normalIndices(std::vector<unsigned int>()),
textureIndices(std::vector<unsigned int>()), meshVertices(std::vector<Vertex>()), submeshes(std::vector<SubMesh>()), 
currentTexture(0)
{
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	submeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	submeshes.clear();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return submeshes;
}

void LoadOBJModel::PostProcessing()
{
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.pos = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.TextCoords = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.textureID = currentTexture;

	submeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentTexture = 0;
}

void LoadOBJModel::LoadModel(const std::string& filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Can't open OBJ file:" + filePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));
		}
		if (line.substr(0, 3) == "vn ") {
			std::stringstream v(line.substr(3));
			float n1, n2, n3;
			v >> n1 >> n2 >> n3;
			normals.push_back(glm::vec3(n1, n2, n3));
		}
		if (line.substr(0, 3) == "vt ") {
			std::stringstream v(line.substr(3));
			float t1, t2;
			v >> t1 >> t2;
			textureCoords.push_back(glm::vec2(t1, t2));

		}
		if (line.substr(0, 2) == "f ") {
			std::stringstream v(line.substr(2));
			char slash;
			unsigned int a, b, c, aT, bT, cT, aN, bN, cN;
			v >> a >> slash >> aT >> slash >> aN >>
				b >> slash >> bT >> slash >> bN >>
				c >> slash >> cT >> slash >> cN;
			a--, b--, c--;
			aT--, bT--,cT--;
			aN--,bN--,cN--;
			indices.push_back(a);
			indices.push_back(b);
			indices.push_back(c);

			normalIndices.push_back(aN);
			normalIndices.push_back(bN);
			normalIndices.push_back(cN);

			textureIndices.push_back(aT);
			textureIndices.push_back(bT);
			textureIndices.push_back(cT);
		}
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	PostProcessing();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_)
{
	currentTexture = Texturehandler::GetInstance()->GetTexture(matName_);
		if (currentTexture == 0) {
			Texturehandler::GetInstance()->createTexture(matName_, "Resources/Textures/" + matName_ + ".png");
			currentTexture = Texturehandler::GetInstance()->GetTexture(matName_);
		}
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	std::ifstream in(matFilePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Can't open MTL file:" + matFilePath_, "LoadOBJModel.cpp", __LINE__);
	}
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			LoadMaterial(line.substr(7));
		}
	}
}
