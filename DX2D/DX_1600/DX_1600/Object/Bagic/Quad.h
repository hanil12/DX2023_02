#pragma once
class Quad
{
public:
	Quad();
	Quad(wstring srvFile);
	Quad(wstring srvFile, Vector2 size);
	virtual ~Quad();

	virtual void Render();

	void CreateVertices();
	Vector2 GetImageSize() { return _halfSize; }

protected:
	// Á¤Á¡(pos, color, uv) 6°³
	Vector2 _halfSize;

	// Mesh
	vector<Vertex_Texture> _vertices;
	vector<UINT> _indices;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	// Material
	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;
	shared_ptr<SRV> _srv;
};

