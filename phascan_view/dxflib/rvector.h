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


#ifndef RVector_H
#define RVector_H

#include <vector>
#include <iosfwd>
//#include "rs.h"

#define RS_MAXDOUBLE 1.0E+10
#define RS_MINDOUBLE -1.0E+10
#define RS_TOLERANCE 1.0e-10
#define RS_TOLERANCE15 1.5e-15
#define RS_TOLERANCE2 1.0e-20
#define RS_TOLERANCE_ANGLE 1.0e-8

/**
 * Represents a 3d vector (x/y/z)
 *
 * @author Andrew Mustun
 */
class RVector {
public:
    RVector()=default;
    RVector(double vx, double vy, double vz=0.0);
    explicit RVector(double angle);
    //RVector(double v[]);
    explicit RVector(bool valid);
    ~RVector()=default;

	//!
	//! \brief operator bool explicit and implicit conversion to bool
	//!
	explicit operator bool() const;

//	void set(double angle); // set to unit vector by the direction of angle
    void set(double vx, double vy, double vz=0.0);
//    void setPolar(double radius, double angle);
//	//! \{
//	//! construct by cartesian, or polar coordinates
//	static RVector polar(double rho, double theta);
//	//! \}

//    double distanceTo(const RVector& v) const;
//    double angle() const;
//    double angleTo(const RVector& v) const;
//    double angleBetween(const RVector& v1, const RVector& v2) const;
//    double magnitude() const;
    double squared() const; //return square of length
//    double squaredTo(const RVector& v1) const; //return square of length
//    RVector lerp(const RVector& v, double t) const;

//    bool isInWindow(const RVector& firstCorner, const RVector& secondCorner) const;
//    bool isInWindowOrdered(const RVector& vLow, const RVector& vHigh) const;

//    RVector toInteger();

    RVector move(const RVector& offset);
    RVector rotate(double ang);
    RVector rotate(const RVector& angleVector);
    RVector rotate(const RVector& center, double ang);
    RVector rotate(const RVector& center, const RVector& angleVector);
    RVector scale(double factor);
    RVector scale(const RVector& factor);
    RVector scale(const RVector& factor) const;
    RVector scale(const RVector& center, const RVector& factor);
    RVector mirror(const RVector& axisPoint1, const RVector& axisPoint2);
    double dotP(const RVector& v1) const;

    RVector operator + (const RVector& v) const;
    RVector operator + (double d) const;
    RVector operator - (const RVector& v) const;
    RVector operator - (double d) const;
    RVector operator * (const RVector& v) const;
    RVector operator / (const RVector& v) const;
    RVector operator * (double s) const;
    RVector operator / (double s) const;
    RVector operator - () const;

    RVector operator += (const RVector& v);
    RVector operator -= (const RVector& v);
    RVector operator *= (const RVector& v);
    RVector operator /= (const RVector& v);
    RVector operator *= (double s);
    RVector operator /= (double s);

    bool operator == (const RVector& v) const;
    bool operator != (const RVector& v) const {
        return !operator==(v);
    }
	//!
	//! \brief operator == comparison of validity with bool
	//! \param valid boolean parameter
	//! \return true is the parameter valid is the same as validity
	//!
	bool operator == (bool valid) const;
	bool operator != (bool valid) const;

    static RVector minimum(const RVector& v1, const RVector& v2);
    static RVector maximum(const RVector& v1, const RVector& v2);
//    crossP only defined for 3D
    static RVector crossP(const RVector& v1, const RVector& v2);
    static double dotP(const RVector& v1, const RVector& v2);

    /** switch x,y for all vectors */
    RVector flipXY(void) const;

    friend std::ostream& operator << (std::ostream&, const RVector& v);

#ifdef RS_TEST

    static bool test();
#endif

public:
	double x=0.;
	double y=0.;
	double z=0.;
	bool valid=false;
};

/**
 * Represents one to 4 vectors. Typically used to return multiple
 * solutions from a function.
 */
class RVectorSolutions {
public:
    typedef RVector value_type;
    RVectorSolutions();
    RVectorSolutions(const std::vector<RVector>& s);
    RVectorSolutions(std::initializer_list<RVector> const& l);
    RVectorSolutions(int num);

    ~RVectorSolutions()=default;

    void alloc(size_t num);
    void clear();
    /**
     * @brief get range safe method of member access
     * @param i member index
     * @return indexed member, or invalid vector, if out of range
     */
    RVector get(size_t i) const;
    const RVector& at(size_t i) const;
    const RVector&  operator [] (const size_t i) const;
    RVector&  operator [] (const size_t i);
    size_t getNumber() const;
    size_t size() const;
    void resize(size_t n);
    bool hasValid() const;
void set(size_t i, const RVector& v);
    void push_back(const RVector& v);
    void removeAt(const size_t i);
    RVectorSolutions& push_back(const RVectorSolutions& v);
    void setTangent(bool t);
    bool isTangent() const;
    RVector getClosest(const RVector& coord,
                         double* dist=nullptr, size_t* index=nullptr) const;
    double getClosestDistance(const RVector& coord,
                              int counts = -1); //default to search all
    const std::vector<RVector>& getVector() const;
    std::vector<RVector>::const_iterator begin() const;
    std::vector<RVector>::const_iterator end() const;
    std::vector<RVector>::iterator begin();
    std::vector<RVector>::iterator end();
    void rotate(double ang);
    void rotate(const RVector& angleVector);
    void rotate(const RVector& center, double ang);
    void rotate(const RVector& center, const RVector& angleVector);
    void move(const RVector& vp);
    void scale(const RVector& center, const RVector& factor);
    void scale(const RVector& factor);

    /** switch x,y for all vectors */
    RVectorSolutions flipXY(void) const;

    RVectorSolutions operator = (const RVectorSolutions& s);

    friend std::ostream& operator << (std::ostream& os,
                                      const RVectorSolutions& s);

private:
    std::vector<RVector> vector;
    bool tangent;
};


#endif

// EOF
