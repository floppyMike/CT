#pragma once

#include "Includes.h"
#include "TrafficLight.h"
#include "Button.h"

class VehicleLight : public TrafficLight
{
public:
	VehicleLight(sdl::Renderer* r, const sdl::Point<int>& pos, int width, std::initializer_list<Light::Color>&& colors)
		: TrafficLight(r, pos, width, std::move(colors))
		, m_button(r)
	{
		const sdl::Dim<int> buttonBox(this->m_box.shape().w >> 1, this->m_box.shape().h >> 2);
		m_button.boxShape({ { pos.x + ((this->m_box.shape().w - buttonBox.w) >> 1),
			m_body.poleShape().y + ((m_body.poleShape().h - buttonBox.h) >> 1) }, buttonBox });
	}

	void event(const SDL_Event& e)
	{
		m_button.event(e);
	}

	void draw()
	{
		TrafficLight::draw();
		m_button.draw();
	}

private:
	Button m_button;
};