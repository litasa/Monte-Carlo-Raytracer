#pragma once
#ifndef KDTREE3Dim_H
#define KDTREE3Dim_H
#include "glm\glm.hpp"

struct Photon
{
	glm::vec3 position;
	float power;
};

struct Node
{

};


template<typename ElemType> 
class KDTree3Dim {
public:
	KDTree3Dim(glm::vec3& key, ElemType data) {};
	~KDTree3Dim() {};

};


#endif //KDTREE3Dim_H