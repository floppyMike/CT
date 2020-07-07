#pragma once

#include "CustomLibrary/SDL/Drawable.h"
#include "CustomLibrary/SDL/Renderer.h"
#include "Includes.h"
#include "LightBox.h"
#include "Node.h"

class TrafficLight
{
	static constexpr int IN_OUT_DIS = 10;

public:
	static constexpr int WIDTH		 = 21;
	static constexpr int DIS		 = 5;
	static constexpr int TOTAL_WIDTH = (WIDTH << 1) + DIS;

	explicit TrafficLight(const mth::Point<int> &pos)
		: m_veh(pos, WIDTH, { sdl::RED, sdl::YELLOW, sdl::GREEN })
		, m_ped({ pos.x + WIDTH + DIS, pos.y }, WIDTH, { sdl::RED, sdl::GREEN })
		, m_out({ pos.x + (WIDTH >> 1), pos.y + m_veh.shape().h + IN_OUT_DIS, NODE_DIM.w, NODE_DIM.h })
		, m_in({ pos.x + (WIDTH >> 1) + WIDTH, pos.y + m_veh.shape().h + IN_OUT_DIS, NODE_DIM.w, NODE_DIM.h })
	{
	}

	[[nodiscard]] auto shape() const noexcept -> mth::Rect<int, int>
	{
		return { m_veh.shape().pos(), { TOTAL_WIDTH, m_veh.shape().h + IN_OUT_DIS + NODE_DIM.h } };
	}

	void translate(const mth::Point<int> &delta)
	{
		m_veh.translate(delta);
		m_ped.translate(delta);
		m_out.shape().translate(delta);
		m_in.shape().translate(delta);
	}

	[[nodiscard]] constexpr auto veh_light() const noexcept -> const auto & { return m_ped; }
	[[nodiscard]] constexpr auto ped_light() const noexcept -> const auto & { return m_ped; }

	[[nodiscard]] constexpr auto node_in() const noexcept -> const auto & { return m_in; }
	[[nodiscard]] constexpr auto node_out() const noexcept -> const auto & { return m_out; }

	auto draw(sdl::ERenderer<sdl::LDelayedRenderer> *r)
	{
		m_veh.draw(r);
		m_ped.draw(r);
		
		sdl::Draw<Node>(&m_in, r).filled_rect();
		sdl::Draw<Node>(&m_out, r).filled_rect();
	}

private:
	LightBox m_veh;
	LightBox m_ped;
	Node	 m_out;
	Node	 m_in;
};
