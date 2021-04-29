#ifndef COLLISIONDECTION_H
#define COLLISIONDECTION_H

#include "Camera.h"

struct Ray;
struct BoundingBox;
class CollisionDection

{
public:
	CollisionDection(const CollisionDection&) = delete;
	CollisionDection(CollisionDection&&) = delete;
	CollisionDection& operator=(const CollisionDection&) = delete;
	CollisionDection& operator=(CollisionDection&&) = delete;

	CollisionDection() = delete;
	~CollisionDection();

	static Ray MousePosToWorldRay(glm::vec2 mouseCoords_, float screenWidth_, float screenHeight_, Camera* camera_);
	static bool RayObbIntersection(Ray* ray_, BoundingBox* box_);
};

#endif