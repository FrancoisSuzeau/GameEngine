/******************************************************************************************************************************************/
// File : IComponent.hpp
// Purpose : An interface for the renderers
/******************************************************************************************************************************************/
#ifndef ICOMPONENT_H
#define ICOMPONENT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "IRenderer.hpp"

namespace Enums { enum LightType {NORMALIGHT, DIRECTIONALLIGHT, POINTLIGHT, SPOTLIGHT, NBLIGHTTYPE }; }

namespace Component {

	class IComponent
	{
	public:
		virtual ~IComponent() {}

		virtual void Clean() = 0;

		virtual bool GetHorizontal() { return false; }
		virtual void SetHorizontal(bool const new_val) { }

		virtual unsigned int GetTextureId() const { return 0; };
		virtual std::string GetTextureName() const { return ""; }
		virtual void SetTextureId(unsigned int texture_id) {}
		virtual void SetTextureName(std::string const new_name) {}
		
		virtual bool GetMixeTextureColor() const { return true; }
		virtual void SetMixeTextureColor(const bool new_val) {}

		virtual Enums::RendererType GetType() const
		{
			return m_type;
		}


		virtual glm::mat4 GetModelMat() const
		{
			return m_model_mat;
		}

		virtual void SetModelMat(glm::mat4 model_mat)
		{
			m_model_mat = model_mat;
		}

		virtual glm::vec3 GetPosition() const
		{
			return m_position;
		}

		virtual void SetPosition(glm::vec3 const new_val)
		{
			m_position = new_val;
		}

		virtual glm::vec3 GetSize() const
		{
			return m_size;
		}

		virtual void SetSize(glm::vec3 const new_val)
		{
			m_size = new_val;
		}

		virtual void SetSize(float const new_val)
		{
			m_size = glm::vec3(new_val);
		}

		virtual void SetHovered(bool const new_val)
		{
			m_hovered = new_val;
		}

		virtual void SetSelected(bool const new_val)
		{
			m_selected = new_val;
		}

		virtual bool GetHovered() const
		{
			return m_hovered;
		}

		virtual bool GetSelected() const
		{
			return m_selected;
		}

		virtual void IncrementAngle(float const incr)
		{
			if (m_angle > 360.f)
			{
				m_angle = 0.f;
			}
			else
			{
				m_angle += incr;
			}
		}

		virtual float GetAngle() const
		{
			return m_angle;
		}

		virtual glm::vec4 GetBackgroundColor() const 
		{
			return m_back_ground_color;
		}
		virtual void SetBackgroundColor(glm::vec4 new_bacground_color)
		{
			m_back_ground_color = new_bacground_color;
		}

		virtual void SetIsALigthSource(bool const is_light_source) 
		{
			m_is_light_source = is_light_source; 
		}
		virtual bool GetIsALightSource() const 
		{
			return m_is_light_source; 
		}

		virtual void SetAmbiantOcclusion(float const ambiant_occlusion)
		{
			m_ambiant_occlusion = ambiant_occlusion;
		}
		virtual float GetAmbiantOcclusion() const
		{
			return m_ambiant_occlusion;
		}

		virtual void SetSpecularShininess(int const specular_shininess)
		{
			m_specular_shininess = specular_shininess;
		}

		virtual int GetSpecularShininess() const
		{
			return m_specular_shininess;
		}

		virtual void SetSpecularStrength(float const specular_strength)
		{
			m_specular_strength = specular_strength;
		}

		virtual float GetSpecularStrength() const
 		{
			return m_specular_strength;
		}

		virtual void SetLightType(Enums::LightType light_type)
		{
			m_light_type = light_type;
		}

		Enums::LightType GetLightType() const
		{
			return m_light_type;
		}
 
	protected:
		Enums::RendererType m_type;

		glm::mat4 m_model_mat;
		glm::vec3 m_position;
		glm::vec3 m_size;
		bool m_hovered;
		bool m_selected;
		float m_angle;
		glm::vec4 m_back_ground_color;
		bool m_is_light_source;
		float m_ambiant_occlusion;
		int m_specular_shininess;
		float m_specular_strength;
		
		Enums::LightType m_light_type;
		

	};
}

#endif