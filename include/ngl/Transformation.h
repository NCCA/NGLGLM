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
#ifndef TRANSFORM_H_
#define TRANSFORM_H_
//----------------------------------------------------------------------------------------------------------------------
/// @file Transformation.h
/// @brief a simple transformation object containing rot / tx / scale and final matrix
//----------------------------------------------------------------------------------------------------------------------
// Library includes
#include "NGLassert.h"
#include <glm/glm.hpp>
namespace nglglm
{
//----------------------------------------------------------------------------------------------------------------------
/// @enum decide which matrix is the current active matrix
//----------------------------------------------------------------------------------------------------------------------
enum  class ActiveMatrix : char{NORMAL,TRANSPOSE,INVERSE};
//----------------------------------------------------------------------------------------------------------------------
/// @class Transformation "include/ngl/Transformation.h"
/// @brief Transformation describes a transformation (translate, scale, rotation)
/// modifed by j macey and included into NGL
/// @author Vincent Bonnet
/// @version 1.5
/// @date 14/03/10 Last Revision 14/03/10
//----------------------------------------------------------------------------------------------------------------------
class NGL_DLLEXPORT Transformation
{

  public:

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Constructor
  //----------------------------------------------------------------------------------------------------------------------
  Transformation() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Copy Constructor
  //----------------------------------------------------------------------------------------------------------------------
  Transformation(const Transformation &_t) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief assignment operator
  //----------------------------------------------------------------------------------------------------------------------
  Transformation & operator =(const Transformation &_t) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to set the scale value in the transform
  /// @param[in] _scale the scale value to set for the transform
  //----------------------------------------------------------------------------------------------------------------------
  void setScale( const glm::vec3& _scale ) noexcept;
  void setScale( const glm::vec4& _scale ) noexcept;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to set the scale value in the transform
  /// @param[in] _x x scale value
  /// @param[in] _y y scale value
  /// @param[in] _z z scale value
  //----------------------------------------------------------------------------------------------------------------------
  void setScale(  Real _x,  Real _y,  Real _z  ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to add to the existing the scale value in the transform
  /// @param[in] _scale the scale value to set for the transform
  //----------------------------------------------------------------------------------------------------------------------
  void addScale( const glm::vec3& _scale ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to add to the existing the scale value in the transform
  /// @param[in] _x x scale value
  /// @param[in] _y y scale value
  /// @param[in] _z z scale value
  //----------------------------------------------------------------------------------------------------------------------
  void addScale(  Real _x,  Real _y, Real _z ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to set the position
  /// @param[in] _position position
  //----------------------------------------------------------------------------------------------------------------------
  void setPosition( const glm::vec4& _position ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to set the position
  /// @param[in] _position position
  //----------------------------------------------------------------------------------------------------------------------
  void setPosition( const glm::vec3& _position ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to set the position value in the transform
  /// @param[in] _x x position value
  /// @param[in] _y y position value
  /// @param[in] _z z position value
  //----------------------------------------------------------------------------------------------------------------------
  void setPosition( Real _x, Real _y, Real _z  ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method add to the existing set the position
  /// @param[in] _position position
  //----------------------------------------------------------------------------------------------------------------------
  void addPosition( const glm::vec4& _position  ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method add to the existing set the position
  /// @param[in] _position position
  //----------------------------------------------------------------------------------------------------------------------
  void addPosition( const glm::vec3& _position ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to add to the existing position value in the transform
  /// @param[in] _x x position value
  /// @param[in] _y y position value
  /// @param[in] _z z position value
  //----------------------------------------------------------------------------------------------------------------------
  void addPosition( Real _x, Real _y,  Real _z  ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @breif method to set the matrix directly
  /// @param[in] _m the matrix to set the m_transform to
  /// need to also re-compute the others
  //----------------------------------------------------------------------------------------------------------------------
  void setMatrix( const glm::mat4 &_m ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to set the rotation
  /// @param[in] _rotation rotation
  /// @note each value is an axis rotation as the values are calculated
  /// mRotationX * mRotationY * mRotationZ;
  //----------------------------------------------------------------------------------------------------------------------
  void setRotation( const glm::vec3& _rotation ) noexcept;
  void setRotation( const glm::vec4& _rotation ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to set the rotation value in the transform
  /// @note each value is an axis rotation as the values are calculated
  /// mRotationX * mRotationY * mRotationZ;
  /// @param[in] _x x rotation value
  /// @param[in] _y y rotation value
  /// @param[in] _z z rotation value
  //----------------------------------------------------------------------------------------------------------------------
  void setRotation( Real _x, Real _y, Real _z ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to add to the existing  rotation
  /// @param[in] _rotation rotation
  /// @note each value is an axis rotation as the values are calculated
  /// mRotationX * mRotationY * mRotationZ;
  //----------------------------------------------------------------------------------------------------------------------
  void addRotation( const glm::vec3& _rotation   ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to add to the existing rotation value in the transform
  /// @note each value is an axis rotation as the values are calculated
  /// mRotationX * mRotationY * mRotationZ;
  /// @param[in] _x x rotation value
  /// @param[in] _y y rotation value
  /// @param[in] _z z rotation value
  //----------------------------------------------------------------------------------------------------------------------
  void addRotation( Real _x, Real _y, Real _z  ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a method to set all the transforms to the identity
  //----------------------------------------------------------------------------------------------------------------------
  void reset() noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function to get the scale
  /// @returns the scale
  //----------------------------------------------------------------------------------------------------------------------
  glm::vec3 getScale()  const  noexcept    { return m_scale;  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function to get the position
  /// @returns the position
  //----------------------------------------------------------------------------------------------------------------------
  glm::vec3 getPosition() const  noexcept  { return m_position;  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function to get the rotation
  /// @returns the rotation
  //----------------------------------------------------------------------------------------------------------------------
  glm::vec3 getRotation() const  noexcept  { return m_rotation;  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function to get the matrix. It computes the matrix if it's dirty
  /// @returns the matrix
  //----------------------------------------------------------------------------------------------------------------------
  glm::mat4 getMatrix() noexcept{ computeMatrices();  return m_matrix;  }
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief *= operator
  /// @param _m the transformation to combine
  //----------------------------------------------------------------------------------------------------------------------
  void operator*=( const Transformation &_m  ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  ///  @brief operator for Transform multiplication will do a matrix
  /// multiplication on each of the matrices
  /// @note this is not const as we need to check that the members are
  /// calculated before we do the multiplication. This is deliberate
  /// @param[in] _m the Transform to multiply the current one by
  /// @returns all the transform matrix members * my _m members
  //----------------------------------------------------------------------------------------------------------------------
  Transformation operator*( const Transformation &_m  ) noexcept;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief load the current transform matrix to the shader
  /// @param[in] _param the name of the parameter to set (varying glm::mat4)
  /// @param[in] _which which matrix mode to use
  //----------------------------------------------------------------------------------------------------------------------
  void loadMatrixToShader(const std::string &_param) noexcept;

protected :

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief position
  //----------------------------------------------------------------------------------------------------------------------
  glm::vec3 m_position;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  scale
  //----------------------------------------------------------------------------------------------------------------------
  glm::vec3 m_scale;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  rotation
  //----------------------------------------------------------------------------------------------------------------------
  glm::vec3 m_rotation;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  boolean defines if the matrix is dirty or not
  //----------------------------------------------------------------------------------------------------------------------
  bool m_isMatrixComputed;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief  matrix transformation
  //----------------------------------------------------------------------------------------------------------------------
  glm::mat4 m_matrix;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to compute the matrix, transpose and inverse matrix. set the m_bIsMatrixComputed variable to true.
  //----------------------------------------------------------------------------------------------------------------------
  void computeMatrices() noexcept;

};

} // end ngl namespace
#endif
//----------------------------------------------------------------------------------------------------------------------
