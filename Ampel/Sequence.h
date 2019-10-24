#pragma once

#include "Includes.h"
#include "TrafficNodeDB.h"

class Sequence
{
public:
	using iterator = std::vector<DTrafficNodeDB::iterator>::iterator;
	using const_iterator = std::vector<DTrafficNodeDB::iterator>::const_iterator;

	void push(DTrafficNodeDB::iterator iter)
	{
		m_seq.emplace_back(iter);
	}

	auto begin() { return m_seq.begin(); }
	auto end() { return m_seq.end(); }

private:
	std::vector<DTrafficNodeDB::iterator> m_seq;
};

