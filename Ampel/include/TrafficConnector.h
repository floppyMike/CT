#pragma once

#include "Includes.h"
#include "RoadLights.h"

class TrafficConnector : RoadLights
{
	static constexpr int IN_OUT_DIS = 10;

public:
	TrafficConnector(sdl::Renderer* r, const mth::Point<int>& pos)
		: RoadLights(r, pos)
		, m_r(r)
		, m_out(r, { pos.x + (RoadLights::WIDTH >> 1), pos.y + m_veh.shape().h + IN_OUT_DIS })
		, m_in(r, { pos.x + (RoadLights::WIDTH >> 1) + WIDTH, pos.y + m_veh.shape().h + IN_OUT_DIS })
	{
	}

	auto& outNode() noexcept { return m_out; }
	const auto& outNode() const noexcept { return m_out; }

	auto& inNode() noexcept { return m_in; }
	const auto& inNode() const noexcept { return m_in; }

	mth::Rect<int, int> shape() const noexcept
	{
		return { m_veh.shape().pos(), { TOTAL_WIDTH, m_veh.shape().h + IN_OUT_DIS + DNode::DIM.h } };
	}

	void translate(const mth::Point<int>& delta)
	{
		RoadLights::translate(delta);
		m_out.translate(delta);
		m_in.translate(delta);
	}

	void draw()
	{
		RoadLights::draw();

		m_r->color(sdl::RED);
		m_out.draw();
		m_r->color(sdl::BLACK);
		m_in.draw();
	}

	using RoadLights::pos;
	using RoadLights::update;
	using RoadLights::flipTo;
	using RoadLights::state;
	using RoadLights::flip;

private:
	sdl::Renderer* m_r;

	DNode m_out;
	DNode m_in;
};
