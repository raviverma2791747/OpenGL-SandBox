#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;
	int m_count;
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(const void* data, unsigned int size,int count);
	~VertexBuffer();

	int GetCount() const;
	void Bind() const;
	void UnBind() const;
};