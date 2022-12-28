#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include "headers.h"
#include "material.h"
#include "imagetexture.h"

// VertexPTN Declarations.
struct VertexPTN
{
	VertexPTN() {
		position = glm::vec3(0.0f, 0.0f, 0.0f);
		normal = glm::vec3(0.0f, 1.0f, 0.0f);
		texcoord = glm::vec2(0.0f, 0.0f);
	}
	VertexPTN(glm::vec3 p, glm::vec3 n, glm::vec2 uv) {
		position = p;
		normal = n;
		texcoord = uv;
	}
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texcoord;
};

// SubMesh Declarations.
struct SubMesh
{
	SubMesh() {
		material = nullptr;
		iboId = 0;
	}
	PhongMaterial* material;
	GLuint iboId;
	std::vector<unsigned int> vertexIndices;
};


// TriangleMesh Declarations.
class TriangleMesh
{
public:
	// TriangleMesh Public Methods.
	TriangleMesh();
	~TriangleMesh();
	
	// Load the model from an *.OBJ file.
	bool LoadFromFile(const std::string& filePath, const bool normalized = true);
	
	// Show model information.
	void ShowInfo();

	// -------------------------------------------------------
	// Feel free to add your methods or data here.
	glm::vec3 refind_objExtent();
	void get_face_data(map<int, map<int, map<int, int> > >& v_table, vector<vector<int> > fd, vector <glm::vec3> v, vector <glm::vec2> vt, vector <glm::vec3> vn, vector <int> mtl_group_indx, vector <int> mtl_fd);
	void get_material_data(map<string, int> mtl_table, vector <string>_mtl_names, vector <float> _Ns, vector <glm::vec3> _Ka, vector <glm::vec3> _Kd, vector <glm::vec3> _Ks, map <string, string> img_names);
	void LoadBuffer();
	void DrawTriangles(PhongShadingDemoShaderProg* phongShadingShader);
	vector<VertexPTN> getVertices() { return vertices; }
	const glm::vec3 MeshGetKa(int n) const { return subMeshes[n].material->GetKa(); }
	const glm::vec3 MeshGetKd(int n) const { return subMeshes[n].material->GetKd(); }
	const glm::vec3 MeshGetKs(int n) const { return subMeshes[n].material->GetKs(); }
	const float MeshGetNs(int n) const { return subMeshes[n].material->GetNs(); }
	ImageTexture* GetImgT() const { return imgT; }
	// -------------------------------------------------------

	int GetNumVertices() const { return numVertices; }
	int GetNumTriangles() const { return numTriangles; }
	int GetNumSubMeshes() const { return (int)subMeshes.size(); }

	glm::vec3 GetObjCenter() const { return objCenter; }
	glm::vec3 GetObjExtent() const { return objExtent; }

private:
	// -------------------------------------------------------
	// Feel free to add your methods or data here.
	// Texture value.
	ImageTexture* imgT;
	// -------------------------------------------------------

	// TriangleMesh Private Data.
	GLuint vboId;
	
	std::vector<VertexPTN> vertices;
	// For supporting multiple materials per object, move to SubMesh.
	// GLuint iboId;
	// std::vector<unsigned int> vertexIndices;
	std::vector<SubMesh> subMeshes;

	int numVertices;
	int numTriangles;
	glm::vec3 objCenter;
	glm::vec3 objExtent;
};


#endif
