/*
  Copyright (C) 2009 Jon Macey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef UTIL_H_
#define UTIL_H_
// must include types.h first for Real and GLEW if required
#include "Types.h"
#include <glm/glm.hpp>
#include <cmath>
#include <string>
//----------------------------------------------------------------------------------------------------------------------
/// @file Util.h
/// @brief some useful definitions and functions
//----------------------------------------------------------------------------------------------------------------------

namespace nglglm
{
//----------------------------------------------------------------------------------------------------------------------
/// @file Util.h
/// @author Jonathan Macey
/// @version 1.2
/// @date 24/11/04
/// @brief lots of usful functions for ngl
//----------------------------------------------------------------------------------------------------------------------
/// @brief  pre-compute the value for value for 2*PI convert to float to suppress windows warning as well
//----------------------------------------------------------------------------------------------------------------------
constexpr Real TWO_PI= Real(2*M_PI); //6.28318530717958647692   //360
//----------------------------------------------------------------------------------------------------------------------
/// @brief  pre-compute the value for value for PI based on system M_PI
//----------------------------------------------------------------------------------------------------------------------
constexpr Real PI=Real(M_PI); //3.14159265358979323846       //180
//----------------------------------------------------------------------------------------------------------------------
/// @brief  pre-compute the value for value for PI/2.0
//----------------------------------------------------------------------------------------------------------------------
constexpr Real PI2=Real(M_PI/2.0); //1.57079632679489661923      //90
//----------------------------------------------------------------------------------------------------------------------
/// @brief  pre-compute the value for value for PI/4.0
//----------------------------------------------------------------------------------------------------------------------
constexpr Real PI4=Real(M_PI/4.0); //0.785398163397448309615     //45

//----------------------------------------------------------------------------------------------------------------------
/// @brief  convert to degrees as a literal
//----------------------------------------------------------------------------------------------------------------------
constexpr long double operator"" _deg(long double _d)
{
    return (_d * M_PI / 180.0);
}

constexpr long double operator"" _rad(long double _d)
{
    return (_d /  180.0f) * M_PI;
}

//----------------------------------------------------------------------------------------------------------------------
/// @brief calculates the normal from 3 points and return the new normal as a Vector
/// @param[in]  _p1 the first point
/// @param[in]  _p2 the second point
/// @param[in]  _p3 the third point
/// @returns  the normal of the 3 points
//----------------------------------------------------------------------------------------------------------------------
extern NGL_DLLEXPORT glm::vec3 calcNormal( const glm::vec4 &_p1, const glm::vec4 &_p2,   const glm::vec4 &_p3   ) noexcept;
//----------------------------------------------------------------------------------------------------------------------
/// @brief calculates the normal from 3 points and return the new normal as a Vector
/// @param[in]  _p1 the first point
/// @param[in]  _p2 the second point
/// @param[in]  _p3 the third point
/// @returns  the normal of the 3 points
//----------------------------------------------------------------------------------------------------------------------
extern NGL_DLLEXPORT glm::vec3 calcNormal( const glm::vec3 &_p1,  const glm::vec3 &_p2, const glm::vec3 &_p3  ) noexcept;
//----------------------------------------------------------------------------------------------------------------------
/// @brief computer a perspective projection matrix similar to the one from the GLM library
/// this is to help make prorting glm code easier http://glm.g-truc.net/
/// @param[in]  _fovy the fov of the camera frustrum in degrees
/// @param[in] _aspect the aspect ratio of the screen
/// @param[in] _zNear the near plane for projection
/// @param[in] _zFar the far plane for the projection
//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------
/// @brief converts Degrees to Radians
/// @param[in]  _deg the angle to convert
/// @returns the angle in Radians
//----------------------------------------------------------------------------------------------------------------------
extern NGL_DLLEXPORT Real radians(const Real _deg ) noexcept;
//----------------------------------------------------------------------------------------------------------------------
/// @brief converts Radians to Degrees
/// @param[in]  _rad the angle in radians
/// @returns the angle in Degrees
//----------------------------------------------------------------------------------------------------------------------
extern NGL_DLLEXPORT Real degrees( const Real _rad ) noexcept;


//----------------------------------------------------------------------------------------------------------------------
/// @brief return a glm matrix as a rotation in degrees
/// @param[in]  _deg
/// @returns a rotation matrix in a X
//----------------------------------------------------------------------------------------------------------------------
extern NGL_DLLEXPORT glm::mat4 rotateX( const Real _deg ) noexcept;

//----------------------------------------------------------------------------------------------------------------------
/// @brief return a glm matrix as a rotation in degrees
/// @param[in]  _deg
/// @returns a rotation matrix in a X
//----------------------------------------------------------------------------------------------------------------------
extern NGL_DLLEXPORT glm::mat4 rotateY( const Real _deg ) noexcept;

//----------------------------------------------------------------------------------------------------------------------
/// @brief return a glm matrix as a rotation in degrees
/// @param[in]  _deg
/// @returns a rotation matrix in a X
//----------------------------------------------------------------------------------------------------------------------
extern NGL_DLLEXPORT glm::mat4 rotateZ( const Real _deg ) noexcept;

extern NGL_DLLEXPORT glm::mat4 scale( const Real _x, const Real _y, const Real _z ) noexcept;


//----------------------------------------------------------------------------------------------------------------------
/// @brief returns if value is a power of 2
/// @param[in]  _x value to check
/// @returns true if a power of 2
//----------------------------------------------------------------------------------------------------------------------
extern NGL_DLLEXPORT bool isPowerOfTwo (unsigned int _x) noexcept;
//----------------------------------------------------------------------------------------------------------------------
/// @brief rounds up the value to next power of 2
/// @param[in]  _x value to round
/// @returns the next pow 2 value
//----------------------------------------------------------------------------------------------------------------------

extern NGL_DLLEXPORT unsigned int nextPow2(unsigned int _x) noexcept;


//----------------------------------------------------------------------------------------------------------------------
/// @brief check for openGL errors and print out.
/// @param[in]  _file the current file where the error occured
/// @param[in]  _line the line number
//----------------------------------------------------------------------------------------------------------------------
extern NGL_DLLEXPORT void NGLCheckGLError(const std::string  &_file, const int _line ) noexcept;
//----------------------------------------------------------------------------------------------------------------------
/// @brief a simple template function for Linear Interpolation requires that any classes have
///    + - and * scalar (i.e. Real) overloaded operators
///    In the graphics lib this will work  for Vector and Colour
/// @param [in] _a the template value for the first parameter
/// @param [in] _b the template value for the first parameter
/// @param [in] _t the value for the blend between _a and _b must be between 0 - 1
//----------------------------------------------------------------------------------------------------------------------
template <typename T> T lerp(T _a, T _b, Real _t) noexcept
{
	T p;
	p=_a+(_b-_a)*_t;
	return p;
}

template <typename T> T trigInterp(T _a, T _b, Real _t ) noexcept
{
  Real angle=radians(90.0f*_t);
  return _a*cos(angle)*cos(angle)+_b*sin(angle)*sin(angle);
}

template <typename T> T cubic( T _a, T _b,Real _t) noexcept
{
  Real v1=(2.0f*_t*_t*_t)-3.0f*(_t*_t)+1.0f;
  Real v2=-(2.0f*_t*_t*_t)+3.0f*(_t*_t);
  return (_a*v1)+(_b*v2);
}



}
#endif

//----------------------------------------------------------------------------------------------------------------------
