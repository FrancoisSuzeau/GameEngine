/******************************************************************************************************************************************/
// File : Model.cpp
// Purpose : Implementing the Model renderer
/******************************************************************************************************************************************/
#include "Model.hpp"

namespace Renderers {
    Model::Model()
    {

    }

    Model::~Model()
    {
    }
    void Model::Construct()
    {
        this->Load();
        this->Attach();
    }
    void Model::Clean()
    {
        base::Clean();
    }


    void Model::Attach()
    {

    }
    void Model::Load()
    {

    }
}