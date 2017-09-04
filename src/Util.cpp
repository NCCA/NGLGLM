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
#include "Types.h"
#include <glm/glm.hpp>
#include <cmath>
#include <iostream>
#include <string>
//----------------------------------------------------------------------------------------------------------------------
/// @file Util.cpp
/// @brief implementation files for Util class
//----------------------------------------------------------------------------------------------------------------------
namespace nglglm
{

//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT glm::vec3 calcNormal(const glm::vec4 &_p1, const glm::vec4 &_p2, const glm::vec4 &_p3 ) noexcept
{

	Real coa, cob, coc ;
	Real px1, py1, pz1 ;
	Real px2, py2, pz2 ;
	Real px3, py3, pz3 ;
	Real absvec;
  glm::vec3 norm;
  px1 = _p1.x; py1 = _p1.y; pz1 = _p1.z;
  px2 = _p2.x; py2 = _p2.y; pz2 = _p2.z;
  px3 = _p3.x; py3 = _p3.y; pz3 = _p3.z;

	// generate cross product

	coa = -(py1 * (pz2-pz3) + py2*(pz3-pz1) + py3*(pz1-pz2)) ;
	cob = -(pz1 * (px2-px3) + pz2*(px3-px1) + pz3*(px1-px2)) ;
	coc = -(px1 * (py2-py3) + px2*(py3-py1) + px3*(py1-py2)) ;

  // normalise the results to get unit length normal
  absvec = sqrtf ( ((coa*coa) + (cob*cob) + (coc*coc))) ;
  norm.x = coa/absvec ;
  norm.y = cob/absvec ;
  norm.z = coc/absvec ;

  return norm;
}


//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT glm::vec3 calcNormal (const glm::vec3 &_p1,  const glm::vec3 &_p2, const glm::vec3 &_p3  ) noexcept
{

  Real coa, cob, coc ;
  Real px1, py1, pz1 ;
  Real px2, py2, pz2 ;
  Real px3, py3, pz3 ;
  Real absvec;
  glm::vec3 norm;
  px1 = _p1.x; py1 = _p1.y; pz1 = _p1.z;
  px2 = _p2.x; py2 = _p2.y; pz2 = _p2.z;
  px3 = _p3.x; py3 = _p3.y; pz3 = _p3.z;

  // generate cross product

  coa = -(py1 * (pz2-pz3) + py2*(pz3-pz1) + py3*(pz1-pz2)) ;
  cob = -(pz1 * (px2-px3) + pz2*(px3-px1) + pz3*(px1-px2)) ;
  coc = -(px1 * (py2-py3) + px2*(py3-py1) + px3*(py1-py2)) ;

  // normalise the results to get unit length normal
  absvec = sqrtf ( ((coa*coa) + (cob*cob) + (coc*coc))) ;
  norm.x = coa/absvec ;
  norm.y = cob/absvec ;
  norm.z = coc/absvec ;

  return norm;
}

NGL_DLLEXPORT Real radians(const Real _deg )
{
  return (_deg/180.0f) * static_cast<Real>(M_PI);
}

//----------------------------------------------------------------------------------------------------------------------
NGL_DLLEXPORT Real degrees( const Real _rad   ) noexcept
{
  return (_rad / static_cast<Real>(M_PI)) * 180.0f;
}


NGL_DLLEXPORT  void NGLCheckGLError( const std::string  &_file, const int _line ) noexcept
{
 //std::cout<<"NGLCheckGLError Called ______________________\n";
 auto errNum = glGetError();
  while (errNum != GL_NO_ERROR)
  {
   // std::cout<<errNum<<"\n";
    std::string str;
    switch(errNum)
    {
      case GL_INVALID_ENUM : str="GL_INVALID_ENUM error"; break;
      case GL_INVALID_VALUE : str="GL_INVALID_VALUE error"; break;
      case GL_INVALID_OPERATION : str="GL_INVALID_OPERATION error"; break;
      case GL_OUT_OF_MEMORY : str="GL_OUT_OF_MEMORY error"; break;
      case GL_INVALID_FRAMEBUFFER_OPERATION : str="GL_INVALID_FRAMEBUFFER_OPERATION error";  break;
      #ifndef USINGIOS_
        case GL_STACK_UNDERFLOW : str= "GL_STACK_UNDERFLOW error"; break;
        case GL_STACK_OVERFLOW : str= "GL_STACK_OVERFLOW error"; break;
      #endif
      // this should be in the spec but it's not on the mac! will check linux
      default : break;
    }
    if(errNum !=GL_NO_ERROR)
    {
      std::cerr<<"GL error "<< str<<" line : "<<_line<<" file : "<<_file<<"\n";
    }
    errNum = glGetError();

   }
}



// for more details see this site some greate stuff here (this code was modified from it)
// http://www.exploringbinary.com/ten-ways-to-check-if-an-integer-is-a-power-of-two-in-c/
NGL_DLLEXPORT bool isPowerOfTwo (unsigned int _x) noexcept
{
 while (((_x % 2) == 0) && _x > 1) /* While x is even and > 1 */
 {
     _x /= 2;
 }
  return (_x == 1);
}

// from http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2

NGL_DLLEXPORT unsigned int nextPow2(unsigned int _x) noexcept
{
	_x -= 1;
	_x |= _x >> 1;
	_x |= _x >> 2;
	_x |= _x >> 4;
	_x |= _x >> 8;
	_x |= _x >> 16;
	return _x + 1;
}


extern NGL_DLLEXPORT glm::mat4 rotateX( const Real _deg ) noexcept
{
  glm::mat4 m;
  Real beta=radians(_deg);
  Real sr = sinf( beta );
  Real cr = cosf( beta );
  m[1][1] =  cr;
  m[2][1] = -sr;
  m[1][2] =  sr;
  m[2][2] =  cr;
  return m;
}

extern NGL_DLLEXPORT glm::mat4 rotateY( const Real _deg ) noexcept
{
  glm::mat4 m;
  Real beta=radians(_deg);
  Real sr = sinf( beta );
  Real cr = cosf( beta );
  m[0][0] =  cr;
  m[2][0] =  sr;
  m[0][2] = -sr;
  m[2][2] =  cr;
  return m;
}

extern NGL_DLLEXPORT glm::mat4 rotateZ( const Real _deg ) noexcept
{
  glm::mat4 m;
  Real beta=radians(_deg);
  Real sr = sinf( beta );
  Real cr = cosf( beta );
  m[0][0] =  cr;
  m[1][0] = -sr;
  m[0][1] =  sr;
  m[1][1] =  cr;
  return m;
}

} // end of namespace






//----------------------------------------------------------------------------------------------------------------------



