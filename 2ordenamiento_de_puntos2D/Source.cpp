/**
 * @file ordenamiento_de_puntos2D.cpp
 * @brief Sorts 2D points according to their distance to the origin.
 *
 * @details
 * This example illustrates three different ways of supplying a comparison
 * predicate to `std::sort`:
 * - ordinary function
 * - function object (functor)
 * - lambda expression (C++11)
 *
 * The program also demonstrates:
 * - use of `std::vector`
 * - storage of objects by value
 * - range-based for loops
 * - custom comparison through `operator<`
 *
 * @note
 * The points are stored directly as objects and sorted by value.
 *
 * @author Pablo San Segundo, course Informática Industrial, ETSIDI, UPM
 * @date 2021/04/30
 * @version Last updated: 2026/04/27
 */

#include <iostream>
#include <cmath>				// std::sqrt, std::hypot
#include <vector>
#include <algorithm>			// std::sort

using namespace std;

constexpr int  num_points_in_test = 3;

/**
 * @class point
 * @brief Represents a point in the 2D plane.
 *
 * @details
 * A point is defined by its Cartesian coordinates `x` and `y`.
 * The class provides:
 * - coordinate accessors and mutators
 * - computation of the distance to the origin
 * - comparison based on distance to the origin
 * - formatted output to a stream
 */
class point {

	// public interface
public:

	// constructor
	point(double x, double y) :
		x_(x), y_(y)
	{
	}

	//setters and getters
	double x() const { return x_; }
	double y() const { return y_; }

	void set_x(double x) { x_ = x; }
	void set_y(double y) { y_ = y; }

	// distance to origin
	//double mod() const { return std::sqrt(x_ * x_ + y_ * y_); }
	double mod() const { return std::hypot(x_, y_); }

	// operator <
	friend bool operator <(const point& p1, const point& p2) {
		return(p1.mod() < p2.mod());
	}

	// console output
	std::ostream& print(std::ostream& o = std::cout) const {
		o << "(" << this->x_ << "," << this->y_ << ")";
		return o;
	}

	// internal state
private:
	double x_ = 0.0;
	double y_ = 0.0;
};

/**
 * @brief Comparison predicate for points.
 *
 * @param a first point.
 * @param b second point.
 * @return `true` if the first point is closer to the origin than the second.
 */
bool funcLess(const point& a, const point& b) {
	return (a < b);
}

/**
 * @brief Functor that compares two points.
 *
 * @details
 * The comparison is based on the distance of the points
 * to the origin.
 */
struct functorLess {

	/**
	 * @brief Compares two points.
	 *
	 * @param lhs: first point.
	 * @param rhs: second point.
	 * @return `true` if the first point is closer to the origin than the second.
	 */
	bool operator()(const point& lhs, const point& rhs) const {
		return (lhs < rhs);
	}
};

/**
 * @brief Test program for sorting 2D points.
 *
 * @details
 * Creates a small set of points, sorts them by distance to the origin,
 * and prints the result.
 */
int main() {

	///////////////////////////////////////////////
	//generates a collection of NUM_ELEM points in increasing order of distance to origin

	double x = 5.0;
	double y = 5.0;
	vector<point> psort;
	for (int i = 0; i < num_points_in_test; ++i) {
		psort.emplace_back(x--, y--);
	}

	/////////////////////////////////////////////////////////////
	//A) default operator < 
	//   std::sort requiere relación de orden estricta débil, puede haber empates
	//std::sort(psort.begin(), psort.end());
	////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////
	//B) predicate function
	  //std::sort(psort.begin(), psort.end(), funcLess);				
	/////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////
	//C) predicate functor
	// std::sort(psort.begin(), psort.end(), functorLess());
	/////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////
	//D) lambda expression used as a comparison predicate
	 std::sort( psort.begin(), psort.end(),
			[](const point& a, const point& b) { return a < b; }   );
	/////////////////////////////////////////////////////////////

	// I/O 
	cout << "---------------------------\n";
	for (const auto& p : psort) {
		p.print();
	}
	cout << "\n-------------------------\n";

	return 0;
}

