/****************************************************************************
**
** This file is part of the LibreCAD project, a 2D CAD program
**
** Copyright (C) 2010 R. van Twisk (librecad@rvt.dds.nl)
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
**
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file gpl-2.0.txt included in the
** packaging of this file.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**
** This copyright notice MUST APPEAR in all copies of the script!
**
**********************************************************************/

#include <iostream>
#include <cmath>
#include <algorithm>
#include "RVector.h"

#ifdef EMU_C99
#include "emu_c99.h" /* remainder() */
#endif

/**
 * Constructor for a point with given coordinates.
 */
RVector::RVector(double vx, double vy, double vz):
    x(vx), y(vy), z(vz), valid(true)
{
}

/**
 * Constructor for a unit vector with given angle
 */
RVector::RVector(double angle):
    x(cos(angle)), y(sin(angle)), valid(true)
{
}

/**
 * Constructor for a point with given valid flag.
 *
 * @param valid true: a valid vector with default coordinates is created.
 *              false: an invalid vector is created
 */
RVector::RVector(bool valid):
	valid(valid)
{
}

RVector::operator bool() const
{
	return valid;
}

///**
// * Sets to a unit vector by the direction angle
// */
//void RVector::set(double angle) {
//    x = cos(angle);
//    y = sin(angle);
//    z = 0.;
//    valid = true;
//}

/**
 * Sets a new position for the vector.
 */
void RVector::set(double vx, double vy, double vz) {
    x = vx;
    y = vy;
    z = vz;
    valid = true;
}

///**
// * Sets a new position for the vector in polar coordinates.
// */
//void RVector::setPolar(double radius, double angle) {
//    x = radius * cos(angle);
//    y = radius * sin(angle);
//    z = 0.0;
//    valid = true;
//}

//RVector RVector::polar(double rho, double theta){
//	return {rho*cos(theta), rho*sin(theta), 0.};
//}

///**
// * @return The angle from zero to this vector (in rad).
// */
//double RVector::angle() const {
//	return RS_Math::correctAngle(atan2(y,x));
//}

///**
// * @return The angle from this and the given coordinate (in rad).
// */
//double RVector::angleTo(const RVector& v) const {
//	if (!valid || !v.valid) return 0.0;
//	return (v-(*this)).angle();
//}

///**
// * @return The angle from between two vectors using the current vector as the center
// * return 0, if the angle is not well defined
// */
//double RVector::angleBetween(const RVector& v1, const RVector& v2) const {
//	if (!valid || !v1.valid || !v2.valid) return 0.0;
//    RVector const vStart(v1 - (*this));
//    RVector const vEnd(v2 - (*this));
//	return RS_Math::correctAngle( atan2( vStart.x*vEnd.y-vStart.y*vEnd.x, vStart.x*vEnd.x+vStart.y*vEnd.y));
//}

///**
// * @return Magnitude (length) of the vector.
// */
//double RVector::magnitude() const {
//    double ret(0.0);
//    // Note that the z coordinate is also needed for 2d
//    //   (due to definition of crossP())
//	if (valid)
//		ret = hypot(hypot(x, y), z);

//    return ret;
//}

/**
  * @return square of vector length
  */
double RVector::squared() const {
    // Note that the z coordinate is also needed for 2d
    //   (due to definition of crossP())
    if (valid)
        return x*x + y*y + z*z;
    return RS_MAXDOUBLE;
}

///**
//  * @return square of vector length
//  */
//double RVector::squaredTo(const RVector& v1) const
//{
//    if (valid && v1.valid) {
//        return  (*this - v1).squared();
//    }
//    return RS_MAXDOUBLE;
//}

///**
// *
// */
//RVector RVector::lerp(const RVector& v, double t) const {
//	return {x+(v.x-x)*t, y+(v.y-y)*t};
//}

///**
// * @return The distance between this and the given coordinate.
// */
//double RVector::distanceTo(const RVector& v) const {
//    if (!valid || !v.valid) {
//        return RS_MAXDOUBLE;
//    }
//    else {
//        return (*this-v).magnitude();
//    }
//}

///**
// * @return true is this vector is within the given range.
// */
//bool RVector::isInWindow(const RVector& firstCorner,
//                           const RVector& secondCorner) const {
//	if (!valid) return false;
//	return LC_Rect{firstCorner, secondCorner}.inArea(*this);
//}

///**
// * @return true is this vector is within the given range
// * of ordered vectors
// */
//bool RVector::isInWindowOrdered(const RVector& vLow,
//                                  const RVector& vHigh) const {
//	if(!valid) return false;
//	return (x>=vLow.x && x<=vHigh.x && y>=vLow.y && y<=vHigh.y);
//}

///**
// * move to the closest integer point
// */
//RVector RVector::toInteger() {
//	x = rint(x);
//	y = rint(y);
//    return *this;
//}

/**
 * Moves this vector by the given offset. Equal to the operator +=.
 */
RVector RVector::move(const RVector& offset) {
    *this+=offset;
    return *this;
}

/**
 * Rotates this vector around 0/0 by the given angle.
 */
RVector RVector::rotate(double ang) {
    rotate(RVector{ang});
    return *this;
}

/**
 * Rotates this vector around 0/0 by the given vector
 * if the vector is a unit, then, it's the same as rotating around
 * 0/0 by the angle of the vector
 */
RVector RVector::rotate(const RVector& angleVector) {
	double x0 = x * angleVector.x - y * angleVector.y;
	y = x * angleVector.y + y * angleVector.x;
	x = x0;

	return *this;
}

/**
 * Rotates this vector around the given center by the given angle.
 */
RVector RVector::rotate(const RVector& center, double ang) {
    *this = center + (*this-center).rotate(ang);
    return *this;
}
RVector RVector::rotate(const RVector& center, const RVector& angleVector) {
    *this = center + (*this-center).rotate(angleVector);
    return *this;
}

/**
 * Scales this vector by the given factors with 0/0 as center.
 */
RVector RVector::scale(double factor) {
    x *= factor;
    y *= factor;
    return *this;
}

/**
 * Scales this vector by the given factors with 0/0 as center.
 */
RVector RVector::scale(const RVector& factor) {
    x *= factor.x;
    y *= factor.y;
    return *this;
}

RVector RVector::scale(const RVector& factor) const{
	return {x*factor.x, y*factor.y};
}

/**
 * Scales this vector by the given factors with the given center.
 */
RVector RVector::scale(const RVector& center, const RVector& factor) {
    *this = center + (*this-center).scale(factor);
    return *this;
}



/**
 * Mirrors this vector at the given axis, defined by two points on axis.
 */
RVector RVector::mirror(const RVector& axisPoint1, const RVector& axisPoint2) {

    RVector direction(axisPoint2-axisPoint1);
    double a= direction.squared();
    RVector ret(false);
    if(a<RS_TOLERANCE2) {
        return ret;
    }
    ret= axisPoint1 + direction* dotP(*this - axisPoint1,direction)/a; //projection point
    *this = ret + ret - *this;

    return *this;
}

/**
 * Streams the vector components to stdout. e.g.: "1/4/0"
 */
std::ostream& operator << (std::ostream& os, const RVector& v) {
    if(v.valid) {
        os << v.x << "/" << v.y << "/" << v.z;
    } else {
        os << "invalid vector";
    }
    return os;
}



/**
 * binary + operator.
 */
RVector RVector::operator + (const RVector& v) const {
	return {x + v.x, y + v.y, z + v.z};
}



/**
 * binary - operator.
 */
RVector RVector::operator - (const RVector& v) const {
	return {x - v.x, y - v.y, z - v.z};
}

RVector RVector::operator + (double d) const {
	return {x + d, y + d, z + d};
}

RVector RVector::operator - (double d) const {
	return {x - d, y - d, z - d};
}

RVector RVector::operator * (const RVector& v) const {
	return {x * v.x, y * v.y, z * v.z};
}

RVector RVector::operator / (const RVector& v) const {
	if(fabs(v.x)> RS_TOLERANCE && fabs(v.y)>RS_TOLERANCE)
		return {x / v.x, y / v.y, std::isnormal(v.z)?z / v.z:z};

	return *this;
}

/**
 * binary * operator.
 */
RVector RVector::operator * (double s) const {
	return {x * s, y * s, z * s};
}

/**
 * binary / operator.
 */
RVector RVector::operator / (double s) const {
	if(fabs(s)> RS_TOLERANCE)
		return {x / s, y / s, z / s};

	return *this;
}

/**
 * unary - operator.
 */
RVector RVector::operator - () const {
	return {-x, -y, -z};
}

/**
 * Scalarproduct (dot product).
 */
double RVector::dotP(const RVector& v1) const
{
    return x*v1.x+y*v1.y;
}

double RVector::dotP(const RVector& v1, const RVector& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/** switch x,y for all vectors */
RVector RVector::flipXY(void) const{
	return {y, x};
}

/**
 * += operator. Assert: both vectors must be valid.
 */
RVector RVector::operator += (const RVector& v) {
    x += v.x;
    y += v.y;
    z += v.z;
	return *this;
}

/**
 * -= operator
 */
RVector RVector::operator -= (const RVector& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
	return *this;
}

RVector RVector::operator *= (const RVector& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

RVector RVector::operator /= (const RVector& v) {
	if (fabs(v.x)> RS_TOLERANCE && fabs(v.y)>RS_TOLERANCE){
		x /= v.x;
		y /= v.y;
		if (std::isnormal(v.z))
			z /= v.z;
	}
	return *this;
}

/**
 * *= operator
 */
RVector RVector::operator *= (double s) {
    x *= s;
    y *= s;
    z *= s;
	return *this;
}
/**
 * /= operator
 */
RVector RVector::operator /= (double s) {
	if(fabs(s)>RS_TOLERANCE) {
		x /= s;
		y /= s;
		z /= s;
	}
	return *this;
}

/**
 * == operator
 */
bool RVector::operator == (const RVector& v) const {
	return (x==v.x && y==v.y && z==v.z && valid && v.valid);
}

bool RVector::operator == (bool valid) const
{
	return this->valid == valid;
}

bool RVector::operator != (bool valid) const
{
	return this->valid != valid;
}

/**
 * @return A vector with the minimum components from the vectors v1 and v2.
 * These might be mixed components from both vectors.
 */
RVector RVector::minimum (const RVector& v1, const RVector& v2) {
	if (!v2) return v1;
	if (!v1) return v2;
	return {std::min(v1.x, v2.x),
				std::min(v1.y, v2.y),
				std::min(v1.z, v2.z)
	};
}

/**
 * @return A vector with the maximum values from the vectors v1 and v2
 */
RVector RVector::maximum (const RVector& v1, const RVector& v2) {
	if (!v2) return v1;
	if (!v1) return v2;
	return {std::max(v1.x, v2.x),
				std::max(v1.y, v2.y),
				std::max(v1.z, v2.z)
	};
}

/**
 * @return Cross product of two vectors.
 *  we don't need cross product for 2D vectors
 */
RVector RVector::crossP(const RVector& v1, const RVector& v2) {
	return {v1.y*v2.z - v1.z*v2.y,
				v1.z*v2.x - v1.x*v2.z,
				v1.x*v2.y - v1.y*v2.x};
}

/**
 * Constructor for no solution.
 */
RVectorSolutions::RVectorSolutions():
    vector(0)
  ,tangent(false)
{
}

RVectorSolutions::RVectorSolutions(const std::vector<RVector>& l):
    vector( l.begin(), l.end())
  ,tangent(false)
{
}

/**
 * Constructor for num solutions.
 */
RVectorSolutions::RVectorSolutions(int num):
    vector(num, RVector(false))
  ,tangent(false)
{
}

RVectorSolutions::RVectorSolutions(std::initializer_list<RVector> const& l):
    vector(l)
  ,tangent(false)
{
}

/**
 * Allocates 'num' vectors.
 */
void RVectorSolutions::alloc(size_t num) {
    if(num<=vector.size()){
        vector.resize(num);
    }else{
        const std::vector<RVector> v(num - vector.size());
        vector.insert(vector.end(), v.begin(), v.end());
    }
}

RVector RVectorSolutions::get(size_t i) const
{
    if(i<vector.size())
        return vector.at(i);
    return {};
}

const RVector&  RVectorSolutions::operator [] (const size_t i) const
{
    return vector[i];
}

RVector&  RVectorSolutions::operator [] (const size_t i)
{
    return vector[i];
}

size_t RVectorSolutions::size() const
{
    return vector.size();
}
/**
 * Deletes vector array and resets everything.
 */
void RVectorSolutions::clear() {
    vector.clear();
    tangent = false;
}

/**
 * @return vector solution number i or an invalid vector if there
 * are less solutions.
 */
const RVector& RVectorSolutions::at(size_t i) const {
        return vector.at(i);
}

/**
 * @return Number of solutions available.
 */
size_t RVectorSolutions::getNumber() const {
    return vector.size();
}

/**
 * @retval true There's at least one valid solution.
 * @retval false There's no valid solution.
 */
bool RVectorSolutions::hasValid() const {
    for(const RVector& v: vector)
        if (v.valid)  return true;

    return false;
}

void RVectorSolutions::resize(size_t n){
    vector.resize(n);
}

const std::vector<RVector>& RVectorSolutions::getVector() const {
    return vector;
}

std::vector<RVector>::const_iterator RVectorSolutions::begin() const
{
    return vector.begin();
}

std::vector<RVector>::const_iterator RVectorSolutions::end() const
{
    return vector.end();
}

std::vector<RVector>::iterator RVectorSolutions::begin()
{
    return vector.begin();
}

std::vector<RVector>::iterator RVectorSolutions::end()
{
    return vector.end();
}

void RVectorSolutions::push_back(const RVector& v) {
        vector.push_back(v);
}

void RVectorSolutions::removeAt(const size_t i){
    if (vector.size()> i)
        vector.erase(vector.begin()+i);
}

RVectorSolutions& RVectorSolutions::push_back(const RVectorSolutions& v) {
    vector.insert(vector.end(), v.begin(), v.end());
    return *this;
}

/**
 * Sets the solution i to the given vector.
 * If i is greater than the current number of solutions available,
 * nothing happens.
 */
void RVectorSolutions::set(size_t i, const RVector& v) {
    if (i<vector.size()) {
        vector[i] = v;
    }else{
//            RS_DEBUG->print(RS_Debug::D_ERROR, "set member in vector in RVectorSolutions: out of range, %d to size of %d", i,vector.size());
        for(size_t j=vector.size();j<=i;++j)
            vector.push_back(v);
    }
}

/**
 * Sets the tangent flag.
 */
void RVectorSolutions::setTangent(bool t) {
    tangent = t;
}

/**
 * @return true if at least one of the solutions is a double solution
 * (tangent).
 */
bool RVectorSolutions::isTangent() const {
    return tangent;
}

/**
 * Rotates all vectors around (0,0) by the given angle.
 */
void RVectorSolutions::rotate(double ang) {
    RVector angleVector(ang);
    for (auto& vp: vector) {
        if (vp.valid) {
            vp.rotate(angleVector);
        }
    }
}

/**
 * Rotates all vectors around (0,0) by the given angleVector.
 */
void RVectorSolutions::rotate(const RVector& angleVector) {
    for (auto& vp: vector) {
        if (vp.valid) {
            vp.rotate(angleVector);
        }
    }
}

/**
 * Rotates all vectors around the given center by the given angle.
 */
void RVectorSolutions::rotate(const RVector& center, double ang) {
    const RVector angleVector(ang);
    for (auto& vp: vector) {
        if (vp.valid) {
            vp.rotate(center,angleVector);
        }
    }
}

void RVectorSolutions::rotate(const RVector& center, const RVector& angleVector) {
    for (auto& vp: vector) {
        if (vp.valid) {
            vp.rotate(center, angleVector);
        }
    }
}

/**
 * Move all vectors around the given center by the given vector.
 */
void RVectorSolutions::move(const RVector& vp) {
    for (RVector& v: vector) {
        if (v.valid) {
            v.move(vp);
        }
    }
}

/**
 * Scales all vectors by the given factors with the given center.
 */
void RVectorSolutions::scale(const RVector& center, const RVector& factor) {
    for (auto& vp: vector) {
        if (vp.valid) {
            vp.scale(center, factor);
        }
    }
}

void RVectorSolutions::scale( const RVector& factor) {
    for (auto& vp: vector) {
        if (vp.valid) {
            vp.scale(factor);
        }
    }
}

/**
 * @return vector solution which is the closest to the given coordinate.
 * dist will contain the distance if it doesn't point to NULL (default).
 */
RVector RVectorSolutions::getClosest(const RVector& coord,
                                         double* dist, size_t* index) const {

    double curDist{0.};
    double minDist = RS_MAXDOUBLE;
    RVector closestPoint{false};
    int pos(0);

    for (size_t i=0; i<vector.size(); i++) {
        if (vector[i].valid) {
            curDist = (coord - vector[i]).squared();

            if (curDist<minDist) {
                closestPoint = vector[i];
                minDist = curDist;
                pos=i;
            }
        }
    }
    if (dist) {
        *dist = sqrt(minDist);
    }
    if (index) {
        *index = pos;
    }
    return closestPoint;
}

/**
  *@ return the closest distance from the first counts RVectors
  *@coord, distance to this point
  *@counts, only consider this many points within solution
  */
double RVectorSolutions::getClosestDistance(const RVector& coord,
                                              int counts)
{
    double ret=RS_MAXDOUBLE*RS_MAXDOUBLE;
    int i=vector.size();
    if (counts < i && counts >= 0) i=counts;
    std::for_each(vector.begin(), vector.begin() + i,
                  [&ret, &coord](RVector const& vp) {
        if(vp.valid) {
            double d=(coord - vp).squared();
            if(d<ret) ret=d;
        }
    }
    );

    return sqrt(ret);
}

/** switch x,y for all vectors */
RVectorSolutions RVectorSolutions::flipXY(void) const
{
        RVectorSolutions ret;
        for(const auto& vp: vector)
            ret.push_back(vp.flipXY());
        return ret;
}

RVectorSolutions RVectorSolutions::operator = (const RVectorSolutions& s) {
    setTangent(s.isTangent());
    vector=s.vector;

    return *this;
}

std::ostream& operator << (std::ostream& os,
                           const RVectorSolutions& s) {
    for (const RVector& vp: s){
        os << "(" << vp << ")\n";
    }
    os << " tangent: " << (int)s.isTangent() << "\n";
    return os;
}
