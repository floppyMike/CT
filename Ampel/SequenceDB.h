#pragma once

#include "Includes.h"
#include "Sequence.h"


template<template<typename> class... Func>
class FSequenceDB : public Func<FSequenceDB<Func...>>...
{
public:
	using iterator = std::vector<Sequence>::iterator;
	using const_iterator = std::vector<Sequence>::const_iterator;

	void push(DTrafficNodeDB::iterator node)
	{
		m_seq.back().push(node);
	}

	void pushRow()
	{
		m_seq.resize(m_seq.size() + 1);
	}

	template<typename Iter>
	auto erase(Iter b, Iter e)
	{
		return m_seq.erase(b, e);
	}

	auto& activeRow()
	{
		return m_seq.back();
	}

	auto begin() const { return m_seq.begin(); }
	auto end() const { return m_seq.end(); }

	auto begin() { return m_seq.begin(); }
	auto end() { return m_seq.end(); }

private:
	std::vector<Sequence> m_seq;
};


template<typename T>
class SequenceChecker : public crtp<T, SequenceChecker>
{
public:
	bool checkIfUsed(DTrafficNodeDB::iterator node)
	{
		for (auto& seqIter : this->_().activeRow())
			if (std::find_first_of((*node)->nodes.begin(), (*node)->nodes.end(),
				(*seqIter)->nodes.begin(), (*seqIter)->nodes.end()) != (*node)->nodes.end())
				return true;

		return false;
	}
};

template<typename T>
class SequenceFinisher : public crtp<T, SequenceFinisher>
{
public:
	void makeUnique()
	{
		this->_().erase(std::unique(this->_().begin(), this->_().end(), [](const Sequence& s1, const Sequence& s2) 
			{
				auto summer = [](auto s, auto iter) { return s + reinterpret_cast<uintptr_t>(&*iter); };
				return std::accumulate(s1.begin(), s1.end(), 0ull, summer) == std::accumulate(s2.begin(), s2.end(), uintptr_t(0), summer);
			}), this->_().end());
	}
};


using SequenceDB = FSequenceDB<SequenceChecker, SequenceFinisher>;
