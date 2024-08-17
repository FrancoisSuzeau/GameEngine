/******************************************************************************************************************************************/
// File : Mesh.cpp
// Purpose : Implementing the Mesh renderer
/******************************************************************************************************************************************/
#include "Mesh.hpp"

namespace Renderers {
    Mesh::Mesh()
    {
        m_vbo = 0;
        m_vao = 0;
        m_ebo = 0;
    }

    Mesh::~Mesh()
    {
    }
    void Mesh::Construct()
    {
        this->Load();
        this->Attach();
    }
    void Mesh::Clean()
    {
        base::Clean();
    }
   

    void Mesh::Attach()
    {

        if (m_vbo == 0)
        {
            glGenBuffers(1, &m_vbo);
        }

        if (m_vao == 0)
        {
            glGenVertexArrays(1, &m_vao);
        }

        if (m_ebo == 0)
        {
            glGenBuffers(1, &m_ebo);
        }
        
    }
    void Mesh::Load()
    {
        
    }
}