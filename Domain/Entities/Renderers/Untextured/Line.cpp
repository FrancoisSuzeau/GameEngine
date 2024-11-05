/******************************************************************************************************************************************/
// File : Line.cpp
// Purpose : Implementing the Line renderer
/******************************************************************************************************************************************/
#include "Line.hpp"

namespace Renderers {

    Line::Line() : m_bytes_colors_size(0)
    {
        m_vbo = 0;
        m_vao = 0;
        m_ebo = 0;
        m_bytes_vertices_size = 0;
        m_bytes_indices_size = 0;
        m_bytes_normals_size = 0;
    }

    Line::~Line()
    {
    }

    void Line::Construct()
    {
        this->Load();
        this->Attach();
    }

    void Line::Draw()
    {
        if (m_vao != 0)
        {
            glBindVertexArray(m_vao);
            if (glIsVertexArray(m_vao) == GL_TRUE)
            {
                glDrawElements(GL_LINES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);

                glBindVertexArray(0);
            }
        }
    }

    void Line::Clean()
    {
        base::Clean();
        m_colors.clear();
    }

    void Line::Attach()
    {
        if (m_vbo == 0)
        {
            glGenBuffers(1, &m_vbo);
        }

        if (m_ebo == 0)
        {
            glGenBuffers(1, &m_ebo);
        }

        if (m_vao == 0)
        {
            glGenVertexArrays(1, &m_vao);
        }


        if (m_vbo != 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            if (glIsBuffer(m_vbo) == GL_TRUE)
            {
                glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size + m_bytes_normals_size + m_bytes_colors_size, 0, GL_STATIC_DRAW);

                glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, m_vertices.data());
                glBufferSubData(GL_ARRAY_BUFFER, m_bytes_vertices_size, m_bytes_normals_size, m_normals.data());
                glBufferSubData(GL_ARRAY_BUFFER, m_bytes_vertices_size + m_bytes_normals_size, m_bytes_colors_size, m_colors.data());

                glBindBuffer(GL_ARRAY_BUFFER, 0);

            }
        }

        if (m_ebo != 0)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
            if (glIsBuffer(m_ebo) == GL_TRUE)
            {
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_bytes_indices_size, 0, GL_STATIC_DRAW);
                glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_bytes_indices_size, m_indices.data());
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }
        }

        if (m_vao != 0)
        {
            glBindVertexArray(m_vao);

            if (glIsVertexArray(m_vao) == GL_TRUE)
            {
                if (m_vbo != 0)
                {
                    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
                    if (glIsBuffer(m_vbo) == GL_TRUE)
                    {
                        if (m_ebo != 0)
                        {
                            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
                            if (glIsBuffer(m_ebo) == GL_TRUE)
                            {
                                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
                                glEnableVertexAttribArray(0);

                                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_bytes_vertices_size));
                                glEnableVertexAttribArray(1);

                                glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_bytes_vertices_size + m_bytes_normals_size));
                                glEnableVertexAttribArray(3);
                            }
                        }

                        glBindBuffer(GL_ARRAY_BUFFER, 0);
                    }
                }

                glBindVertexArray(0);
            }
        }
    }
    void Line::Load()
    {
        m_vertices = {
        -1.f, -1.f, -1.f, // Back face
         1.f, -1.f, -1.f,
         1.f,  1.f, -1.f,
        -1.f,  1.f, -1.f,

        -1.f, -1.f,  1.f, // Front face
         1.f, -1.f,  1.f,
         1.f,  1.f,  1.f,
        -1.f,  1.f,  1.f,

        -1.f,  1.f,  1.f, // Left face
        -1.f,  1.f, -1.f,
        -1.f, -1.f, -1.f,
        -1.f, -1.f,  1.f,

         1.f,  1.f,  1.f, // Right face
         1.f,  1.f, -1.f,
         1.f, -1.f, -1.f,
         1.f, -1.f,  1.f,

        -1.f, -1.f, -1.f, // Bottom face
         1.f, -1.f, -1.f,
         1.f, -1.f,  1.f,
        -1.f, -1.f,  1.f,

        -1.f,  1.f, -1.f, // Top face
         1.f,  1.f, -1.f,
         1.f,  1.f,  1.f,
        -1.f,  1.f,  1.f

        };

        m_normals =
        {
        0.0f,  0.0f, -1.0f, // Back face
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,
        0.0f,  0.0f, -1.0f,

        0.0f,  0.0f,  1.0f, // Front face
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,
        0.0f,  0.0f,  1.0f,

        -1.0f,  0.0f,  0.0f, // Left face
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,

        1.0f,  0.0f,  0.0f, // Right face
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,
        1.0f,  0.0f,  0.0f,

         0.0f, -1.0f,  0.0f, // Bottom face
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,

        0.0f,  1.0f,  0.0f, // Top face
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  1.0f,  0.0f
        };


        m_colors = {
             // Back face 
             1.f, 0.f, 0.f, 1.f, //RED
             0.f, 1.f, 0.f, 1.f, //GREEN
             0.f, 0.f, 0.f, 0.f, 
             0.f, 0.f, 0.f, 0.f,

             // Front face
             0.f, 0.f, 0.f, 0.f,
             0.f, 0.f, 0.f, 0.f,
             0.f, 0.f, 0.f, 0.f,
             0.f, 0.f, 0.f, 0.f,

             // Left face
             0.f, 0.f, 0.f, 0.f,
             0.f, 0.f, 0.f, 0.f,
             0.f, 0.f, 0.f, 0.f,
             0.f, 0.f, 0.f, 0.f,

             // Right face
             0.f, 0.f, 0.f, 0.f,
             0.f, 0.f, 0.f, 0.f,
             0.f, 0.f, 0.f, 0.f,
             0.f, 0.f, 0.f, 0.f,

             // Bottom face
             0.f, 0.f, 1.f, 1.f, //BLUE
             0.f, 0.f, 0.f, 0.f,
             0.f, 0.f, 0.f, 0.f,
             0.f, 0.f, 0.f, 0.f,

             // Top face
             0.f, 0.f, 0.f, 0.f,
             0.f, 0.f, 0.f, 0.f,
             0.f, 0.f, 0.f, 0.f,
             0.f, 0.f, 0.f, 0.f
        };
        
        m_indices = {

            0, 1, 2, 2, 3, 0,        // Back face
            4, 5, 6, 6, 7, 4,        // Front face
            8, 9, 10, 10, 11, 8,     // Left face
            12, 13, 14, 14, 15, 12,  // Right face
            16, 17, 18, 18, 19, 16,  // Bottom face
            20, 21, 22, 22, 23, 20   // Top face
        };

        m_bytes_indices_size = (unsigned int)(m_indices.size() * sizeof(unsigned int));
        m_bytes_normals_size = m_normals.size() * sizeof(GLfloat);
        m_bytes_vertices_size = m_vertices.size() * sizeof(GLfloat);
        m_bytes_colors_size = m_colors.size() * sizeof(GLfloat);
    }

}