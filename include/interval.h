#ifndef INTERVAL_H
#define INTERVAL_H

class Interval {
public:
    Interval() : min(+infinity), max(-infinity) {} // Default interval is empty
    Interval(double _min, double _max) : min(_min), max(_max) {}

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }

    double clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

public:
	double min, max;
	static const Interval empty, universe;
};

const static Interval empty(+infinity, -infinity);
const static Interval universe(-infinity, +infinity);


#endif