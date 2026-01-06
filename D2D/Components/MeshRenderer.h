#pragma once
#include "Component.h"
class Mesh;

class MeshRenderer : public Component
{
public:


private:
	shared_ptr<Mesh> mesh;
};