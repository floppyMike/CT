#pragma once

#include "LightBox.h"
#include "Node.h"

class LightPair
{
public:
	static constexpr int WIDTH = 21;
	static constexpr int TOTAL_WIDTH = (WIDTH << 1) + 5;
	static constexpr int IN_OUT_DIS = 10;

	LightPair() = delete;

	LightPair(sdl::Renderer* r, const sdl::Point<int>& pos)
		: m_veh(r, pos, WIDTH, { Light::RED, Light::YELLOW, Light::GREEN })
		, m_ped(r, { pos.x + WIDTH + 5, pos.y }, WIDTH, { Light::RED, Light::GREEN })
		, m_out(r, { pos.x + (WIDTH >> 1), pos.y + m_veh.shape().h + IN_OUT_DIS })
		, m_in(r, { pos.x + (WIDTH >> 1) + WIDTH, pos.y + m_veh.shape().h + IN_OUT_DIS })
	{
	}

	sdl::Point<int> middle() const noexcept
	{
		return { m_veh.shape().x + (TOTAL_WIDTH >> 1), 
			m_veh.shape().y + (m_veh.shape().h + IN_OUT_DIS + Node::DIM.h >> 1) };
	}

	sdl::Rect<int, int> shape() const noexcept
	{
		return { { m_veh.shape().pos() }, { TOTAL_WIDTH, m_veh.shape().h + IN_OUT_DIS + Node::DIM.h } };
	}

	const auto& outShape() const noexcept
	{
		return m_out.shape();
	}

	const auto& inShape() const noexcept
	{
		return m_in.shape();
	}

	void translate(const sdl::Point<int>& delta)
	{
		m_veh.translate(delta);
		m_ped.translate(delta);

		m_out.translate(delta);
		m_in.translate(delta);
	}

	constexpr auto pos() const noexcept
	{
		return m_veh.shape().pos();
	}

	void draw()
	{
		m_veh.draw();
		m_ped.draw();

		m_out.draw();
		m_in.draw();
	}

private:
	LightBox m_veh;
	LightBox m_ped;

	Node m_out;
	Node m_in;
};
