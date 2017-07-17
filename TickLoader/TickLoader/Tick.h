#pragma once

#include <memory>
#include <string>

struct Tick
{
	using TickPtr = std::shared_ptr<Tick>;

	std::string _instrument;
	double _curr = -1.0;
	double _vol = -1.0;
	double _ask1;
	double _askVol;
	double _bid1;
	double _bidVol;
	double _interest;
	int _typeIndex = -1;
	time_t _time;
	int _msec;
	double _turnover = -1.0;

	bool Valid() const
	{
		if (_typeIndex < 0)
			return false;
		if (_curr<0)
			return false;
		if (_ask1<0)
			return false;
		if (_askVol<0)
			return false;
		if (_bid1<0)
			return false;
		if (_bidVol<0)
			return false;
		else
			return true;
	}

	// TODO: add operator <<

	bool SameTime(const Tick& other) const
	{
		if (_time == other._time && _msec == other._msec)
		{
			return true;
		}

		return false;
	}

	bool operator == (const Tick& other) const
	{
		return (_time == other._time
			&& _msec == other._msec
			&& _typeIndex == other._typeIndex
			&& _vol == other._vol
			&& _turnover == other._turnover);
	}

	bool FillCurr()
	{
		if (_bid1 < 0.1f)
		{
			if (_ask1 < 0.1f)
				return false;
			else
			{
				_curr = _ask1;
				return true;
			}
		}
		else if (_ask1 < 0.1f)
		{
			_curr = _bid1;
			return true;
		}
		else
		{
			_curr = (_bid1 + _ask1) / 2.0f;
			return true;
		}
	}

	double BuyPrice() const
	{
		if (_ask1 < 0.1f)
			return _bid1;
		else
			return _ask1;
	}

	double SellPrice() const
	{
		if (_bid1 < 0.1f)
			return _ask1;
		else
			return _bid1;
	}

	friend bool operator < (const Tick& left, const Tick& right);
};

inline bool operator < (const Tick& left, const Tick& right)
{
	if (left._time != right._time)
	{
		return left._time < right._time;
	}

	if (left._msec != right._msec)
	{
		return left._msec < right._msec;
	}

	if (left._typeIndex != right._typeIndex)
	{
		return left._typeIndex < right._typeIndex;
	}

	if (left._vol != right._vol)
	{
		return left._vol < right._vol;
	}

	return left._turnover < right._turnover;
}

