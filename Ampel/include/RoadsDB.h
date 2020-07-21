#pragma once

#include "Includes.h"
#include "Node.h"
#include "RoadLights.h"
#include "Line.h"

class TrafficNode : public RoadLights
{
	static constexpr int IN_OUT_DIS = 10;

public:
	explicit TrafficNode(const mth::Point<int> &pos)
		: RoadLights(pos)
		, m_out({ { pos.x + WIDTH / 2, pos.y + RoadLights::shape().h + IN_OUT_DIS }, NODE_DIM })
		, m_in({ { pos.x + WIDTH / 2 + WIDTH, pos.y + RoadLights::shape().h + IN_OUT_DIS }, NODE_DIM })
	{
	}

	[[nodiscard]] auto out_node() const noexcept -> const auto & { return m_out; }
	[[nodiscard]] auto out_node() noexcept -> auto & { return m_out; }

	[[nodiscard]] auto in_node() const noexcept -> const auto & { return m_in; }
	[[nodiscard]] auto in_node() noexcept -> auto & { return m_in; }

	[[nodiscard]] auto shape() const noexcept -> mth::Rect<int, int>
	{
		const auto &s = RoadLights::shape();
		return { s.pos(), { TOTAL_WIDTH, s.h + IN_OUT_DIS + NODE_DIM.h } };
	}

	void translate(const mth::Point<int> &delta)
	{
		RoadLights::translate(delta);

		m_out.shape().translate(delta);
		m_in.shape().translate(delta);
	}

	auto add_link(Link *l) { m_lines.emplace_back(l); }

	[[nodiscard]] auto links() const noexcept -> const auto & { return m_lines; }

	friend auto operator<<(sdl::Renderer &r, const TrafficNode &tn) -> sdl::Renderer &
	{
		r << static_cast<RoadLights>(tn);

		r.color(sdl::RED);
		r << tn.m_out;

		r.color(sdl::BLACK);
		r << tn.m_in;
		for (const auto *l : tn.m_lines) r << *l;

		return r;
	}

private:
	Node m_out;
	Node m_in;

	std::vector<Link *> m_lines;
};
