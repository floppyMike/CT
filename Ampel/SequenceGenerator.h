#pragma once

#include "Includes.h"
#include "TrafficNodeDB.h"

class Sequence
{
public:
	using iterator = std::vector<std::vector<DTrafficNodeDB::iterator>>::iterator;
	using const_iterator = std::vector<std::vector<DTrafficNodeDB::iterator>>::const_iterator;

	Sequence()
		: m_seq(1)
	{
	}

	Sequence(Sequence&&) = default;
	Sequence(const Sequence&) = default;

	Sequence& operator=(Sequence&&) = default;
	Sequence& operator=(const Sequence&) = default;

	void push(DTrafficNodeDB::iterator node)
	{
		m_seq.back().emplace_back(node);
	}

	bool checkIfUsed(DTrafficNodeDB::iterator node)
	{
		for (auto& seqIter : m_seq.back())
			if (std::find_first_of((*node)->nodes.begin(), (*node)->nodes.end(),
				(*seqIter)->nodes.begin(), (*seqIter)->nodes.end()) != (*node)->nodes.end())
				return true;

		return false;
	}

	void pushRow()
	{
		m_seq.resize(m_seq.size() + 1);
	}

	auto begin() const { return m_seq.begin(); }
	auto end() const { return m_seq.end(); }

	auto begin() { return m_seq.begin(); }
	auto end() { return m_seq.end(); }

private:
	std::vector<std::vector<DTrafficNodeDB::iterator>> m_seq;
};
