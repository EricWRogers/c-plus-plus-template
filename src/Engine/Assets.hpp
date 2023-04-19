#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "IOManager.hpp"
#include "Debug.hpp"

namespace Engine
{
    struct Vertex
	{
		// position
        glm::vec3 position;
        // normal
        glm::vec3 normal;
        // texCoords
        glm::vec2 texCoords;
	};

    class Asset
    {
    public:
        Asset() {}
        ~Asset() {}

        Asset(const Asset&) = delete;
        Asset& operator= (const Asset&) = delete;

        virtual bool Load(std::string _path) = 0;
        virtual bool Free() = 0;
    };
    
    class ModelAsset : public Asset
    {
    private:
        std::vector<Vertex> m_vertices;
        unsigned int m_vao;
        unsigned int m_vbo;
        int m_size;
    public:
        bool Load(std::string _path) override;
        bool Free() override;
        unsigned int GetVAO() { return m_vao; }
        unsigned int GetVBO() { return m_vbo; }
        int GetSize() { return m_size; }
        std::vector<Vertex> GetVertices() { return m_vertices; }
    };
}