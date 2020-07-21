#pragma once

#include "Includes.h"
#include "RoadsDB.h"
#include "Sequence.h"

class SequenceDB : std::vector<Sequence>
{
	using vec_t = std::vector<Sequence>;

public:
	using iterator		 = std::vector<Sequence>::iterator;
	using const_iterator = std::vector<Sequence>::const_iterator;

	void push(DTrafficNode *node) { m_seq.back().emplace_back(node); }

	void pushRow() { m_seq.resize(m_seq.size() + 1); }

	using vec_t::erase;

	using vec_t::back;

	using vec_t::begin;
	using vec_t::end;

	auto checkIfUsed(DTrafficNode *node) const
	{
		for (const auto &seqIter : m_seq.back())
			if (std::find_first_of(node->nodes.begin(), node->nodes.end(), seqIter->nodes.begin(), seqIter->nodes.end())
				!= node->nodes.end())
				return true;

		return false;
	}

private:
	std::vector<Sequence> m_seq;
};