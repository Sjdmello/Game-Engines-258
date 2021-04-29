#include "CollisionDection.h"
#include "Ray.h"
#include "CoreEngine.h"

CollisionDection::~CollisionDection()
{
}

Ray CollisionDection::MousePosToWorldRay(glm::vec2 mouseCoords_, float screenWidth_, float screenHeight_, Camera* Camera_)
{
	glm::vec4 rayStartNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f, (mouseCoords_.y / screenHeight_ - 0.5f)
		* 2.0f, -1.0f, 1.0f);
	glm::vec4 rayEndNDC((mouseCoords_.x / screenWidth_ - 0.5) * 2.0f, (mouseCoords_.y / screenHeight_ - 0.5) * 2.0f, 0.0f, 1.0f);
	glm::mat4 inverse = glm::inverse(Camera_->GetPerspective() * Camera_->GetView());

	glm::vec4 rayStartWorld = inverse * rayStartNDC;
	rayStartWorld /= rayStartWorld.w;

	glm::vec4 rayEndWorld = inverse * rayEndNDC;
	rayEndWorld /= rayEndWorld.w;

	glm::vec3 rayDirWorld(rayEndWorld - rayStartWorld);
	rayDirWorld = glm::normalize(rayDirWorld);

	glm::vec3 rayDirWorld(rayEndWorld - rayStartWorld);
	rayDirWorld = glm::normalize(rayDirWorld);

	return Ray(glm::vec3(rayStartWorld), rayDirWorld);
}

bool CollisionDection::RayObbIntersection(Ray* ray_, BoundingBox* box_)
{
	glm::mat4 modelMatrix = box_->transform;
	glm::vec3 rayOrigin = ray_->origin;
	glm::vec3 rayDirection = ray_->origin;
	glm::vec3 boxMin = box_->minVert;
	glm::vec3 boxMax = box_->maxVert;
	float tMin = CoreEngine::GetInstance()->GetCamera()->GetNearPlane();
	float tMax = CoreEngine::GetInstance()->GetCamera()->GetFarPlane();
	glm::vec3 worldPos(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
	glm::vec3 delta = worldPos - rayOrigin;

	//xaxis
	glm::vec3 XAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
	float dotDelta = glm::dot(XAxis, delta);
	float dotDir = glm::dot(rayDirection, XAxis);
	if (fabs(dotDir) > 0.001f) {
		float t1 = (dotDelta + boxMin.x) / dotDir;
		float t2 = (dotDelta + boxMax.x) / dotDir;

		if (t1 > t2) {
			float w = t1;
			t1 = t2;
			t2 = w;
		}
		if (t2 < tMax) {
			tMax = t2;
		}
		if (t1 > tMin) {
			tMin = t1;
		}
		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if (-dotDelta + boxMin.x > 0.0f || -dotDelta + boxMax.x < 0.0f) {
			return false;
		}
	}

	//Yaxis
	glm::vec3 YAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
	float dotDelta = glm::dot(YAxis, delta);
	float dotDir = glm::dot(rayDirection, YAxis);
	if (fabs(dotDir) > 0.001f) {
		float t1 = (dotDelta + boxMin.y) / dotDir;
		float t2 = (dotDelta + boxMax.y) / dotDir;

		if (t1 > t2) {
			float w = t1;
			t1 = t2;
			t2 = w;
		}
		if (t2 < tMax) {
			tMax = t2;
		}
		if (t1 > tMin) {
			tMin = t1;
		}
		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if (-dotDelta + boxMin.y > 0.0f || -dotDelta + boxMax.y < 0.0f) {
			return false;
		}
	}

	ray_->intersectionDist = tMin;
	return true;
}
