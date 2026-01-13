#pragma once
#include <vector>
#include <memory>
#include "Objects/Object.h"

using namespace std;

class Scene
{
public:

private:
	vector<shared_ptr<Object>> objects;
};