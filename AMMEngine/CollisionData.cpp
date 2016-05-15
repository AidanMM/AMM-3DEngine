#include "CollisionData.h"
#define DEBUG false

Model* CollisionData::s_boundingBox = nullptr;

void CollisionData::BindToObject(GameObject* object)
{
	m_object = object;
}

CollisionData::~CollisionData()
{
	//delete m_boundingBox;
}

void CollisionData::GenerateBoundingBox(std::vector<glm::vec3> vertices, glm::vec3& min, glm::vec3& max, glm::vec3& size)
{
	if (vertices.size() > 0) {
		max = vertices[0];
		min = vertices[0];
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].x > max.x)
			max.x = vertices[i].x;
		else if (vertices[i].x < min.x)
			min.x = vertices[i].x;

		if (vertices[i].y > max.y)
			max.y = vertices[i].y;
		else if (vertices[i].y < min.y)
			min.y = vertices[i].y;

		if (vertices[i].z > max.z)
			max.z = vertices[i].z;
		else if (vertices[i].z < min.z)
			min.z = vertices[i].z;
	}

	size.x = glm::distance(glm::vec3(min.x, 0.0f, 0.0f), glm::vec3(max.x, 0.0f, 0.0f));
	size.y = glm::distance(glm::vec3(0.0f, min.y, 0.0f), glm::vec3(0.0f, max.y, 0.0f));
	size.z = glm::distance(glm::vec3(0.0f, 0.0f, min.z), glm::vec3(0.0f, 0.0f, max.z));
}

CollisionData::CollisionData()
{
	m_boundingPoints = std::vector<glm::vec3>(8, glm::vec3(0.0f));
	m_reBoundingPoints = std::vector<glm::vec3>(8, glm::vec3(0.0f));
}

void CollisionData::UpdateBoundingBoxes()
{

	/* The axis realigned bounding box */
	for (unsigned int i = 0; i < m_reBoundingPoints.size(); i++)
	{
		m_reBoundingPoints[i] = glm::vec3(m_object->m_transformations * glm::vec4(m_boundingPoints[i], 1.0f));
	}

	GenerateBoundingBox(m_reBoundingPoints, m_reMin, m_reMax, m_reSize);
	m_reBoundingPoints = GenerateBoundingPoints(m_reMin, m_reMax);

	m_center = (m_max + m_min) / 2.0f; // TC: Not sure if needed yet.
}

std::vector<glm::vec3> CollisionData::GenerateBoundingPoints(glm::vec3 min, glm::vec3 max)
{
	std::vector<glm::vec3> points(8, glm::vec3(0.0f));

	// Top Points
	points[0] = glm::vec3(min.x, min.y, max.z);
	points[1] = glm::vec3(max.x, min.y, max.z);
	points[2] = glm::vec3(max.x, max.y, max.z);
	points[3] = glm::vec3(min.x, max.y, max.z);

	// Bottom Points
	points[4] = glm::vec3(min.x, min.y, min.z);
	points[5] = glm::vec3(max.x, min.y, min.z);
	points[6] = glm::vec3(max.x, max.y, min.z);
	points[7] = glm::vec3(min.x, max.y, min.z);

	return points;
}

void CollisionData::SetModel(MyMesh* mesh)
{
	GenerateBoundingBox(mesh->GetVertices(), m_min, m_max, m_size);
	m_boundingPoints = GenerateBoundingPoints(m_min, m_max);
	UpdateBoundingBoxes();
}

void CollisionData::DrawBoundingBox()
{
	//TODO: This currently only draws the REBB. Possibly add code to make it draw different ones
	//Depending on collision mode, or depending on debug mode.
	if (s_boundingBox == nullptr) 
	{
		s_boundingBox = new Model("Cube");
		s_boundingBox->GenCube(1.0f);
	}

	glm::mat4 world = glm::mat4(1.0f);
	world *= glm::translate(m_object->m_translations);
	world *= glm::scale(m_reSize);
	s_boundingBox->Render(world, m_object->m_worldCamera->GetView(), m_object->m_worldCamera->GetProjection());
}

bool CollisionData::AreColliding(CollisionDetectionType type, GameObject* first, GameObject* second)
{
	bool areColliding = false;

	glm::vec3 min1(0.0f);
	glm::vec3 max1(0.0f);
	glm::vec3 min2(0.0f);
	glm::vec3 max2(0.0f);

	switch (type)
	{
	case BoundingBox:
		min1 = glm::vec3(first->m_transformations * glm::vec4(first->m_collisionData->m_min, 1.0f));
		max1 = glm::vec3(first->m_transformations * glm::vec4(first->m_collisionData->m_max, 1.0f));
		min2 = glm::vec3(second->m_transformations * glm::vec4(second->m_collisionData->m_min, 1.0f));
		max2 = glm::vec3(second->m_transformations * glm::vec4(second->m_collisionData->m_max, 1.0f));
		break;
	case AxisRealignedBoundingBox:
		min1 = first->m_collisionData->m_reMin;
		max1 = first->m_collisionData->m_reMax;
		min2 = second->m_collisionData->m_reMin;
		max2 = second->m_collisionData->m_reMax;
		break;
	default:
		assert("Unknown collision detection type.", false);
		break;
	}

	areColliding = Overlaps(min1, max1, min2, max2);
	//Code removed as functionality has slowed down since refactor.
	/*if (areColliding == true) {
		areColliding = SeperatingAxisTest(first, second);
	}*/

	return areColliding;
}

std::vector<glm::vec3> CollisionData::GetEdgeAxes(GameObject* first, GameObject* second)
{
	std::vector<glm::vec3> firstEdges = first->m_collisionData->m_SATEdges;
	std::vector<glm::vec3> secondEdges = second->m_collisionData->m_SATEdges;
	std::vector<glm::vec3> axes;
	//Loop through the faces of the first object
	for (int i = 0; i < firstEdges.size(); i++)
	{
		//loop through the second object
		for (int k = 0; k < secondEdges.size(); k++)
		{
			axes.push_back(glm::normalize(glm::cross(glm::vec3(first->m_transformations * glm::vec4(firstEdges[i], 1)), glm::vec3(second->m_transformations * glm::vec4(secondEdges[k], 1)))));
		}
	}
	return axes;
}

bool CollisionData::SeperatingAxisTest(GameObject * first, GameObject * second)
{
	//The first step is to obtain the seperating Axes between the two shapes, this is done through getting
	//Every Edge combiniation between the two of them.  
	std::vector<glm::vec3> axes = GetEdgeAxes(first, second);

	//Now add each face normal to the Axes so that all seperating axes are accounted for
	std::vector<glm::vec3> firstFaces = first->m_collisionData->m_SATNormals;
	for (int i = 0; i < firstFaces.size(); i++)
	{
		axes.push_back(glm::normalize(glm::vec3(first->m_transformations * glm::vec4(firstFaces[i], 1.0))));
	}
	//Add those of the other object as well
	std::vector<glm::vec3> secondFaces = second->m_collisionData->m_SATNormals;
	for (int i = 0; i < secondFaces.size(); i++)
	{
		axes.push_back(glm::normalize(glm::vec3(second->m_transformations * glm::vec4(secondFaces[i], 1.0))));
	}
	//Determine the plane points
	glm::vec3 planePoint = glm::vec3(0,0,0);

	//Now project each vertice, onto the plane created by the axes to see if there is a collision.
	std::vector<glm::vec3> firstVertices = first->m_model->GetVertices();
	std::vector<glm::vec3> secondVertices = second->m_model->GetVertices();
	//Transform the vertices to world coordinates
	for (int i = 0; i < firstVertices.size(); i++)
	{
		firstVertices[i] = glm::vec3(first->m_transformations * glm::vec4(firstVertices[i], 1.0f));
	}
	for (int i = 0; i < firstVertices.size(); i++)
	{
		secondVertices[i] = glm::vec3(second->m_transformations * glm::vec4(secondVertices[i], 1.0f));
	}
	for (int a = 0; a < axes.size(); a++)
	{
		//Do the calculations in the for loop once so that we have accurate starting points for the min and maxes
		glm::vec3 firstMin = firstVertices[0] - glm::dot(firstVertices[0] - planePoint, axes[a]) * axes[a];
		glm::vec3 firstMax = firstMin;
		glm::vec3 secondMin = secondVertices[0] - glm::dot(secondVertices[0] - planePoint, axes[a]) * axes[a];
		glm::vec3 secondMax = secondMin;
		glm::vec3 minOverlap = firstMin - secondMin;
		for (int i = 1; i < firstVertices.size(); i++)
		{
			//Find the projection onto the plane
			glm::vec3 projectedPoint = firstVertices[i] - glm::dot(firstVertices[i] - planePoint, axes[a]) * axes[a];
			//check to see if there needs to be new min max x points
			projectedPoint.x < firstMin.x ? firstMin.x = projectedPoint.x : (projectedPoint.x > firstMax.x ? firstMax.x = projectedPoint.x : 0);
			projectedPoint.y < firstMin.y ? firstMin.y = projectedPoint.y : (projectedPoint.y > firstMax.y ? firstMax.y = projectedPoint.y : 0);
			projectedPoint.z < firstMin.z ? firstMin.z = projectedPoint.z : (projectedPoint.z > firstMax.z ? firstMax.z = projectedPoint.z : 0);
		}
		for (int i = 1; i < secondVertices.size(); i++)
		{
			glm::vec3 projectedPoint = secondVertices[i] - glm::dot(secondVertices[i] - planePoint, axes[a]) * axes[a];
			projectedPoint.x < secondMin.x ? secondMin.x = projectedPoint.x : (projectedPoint.x > secondMax.x ? secondMax.x = projectedPoint.x : 0);
			projectedPoint.y < secondMin.y ? secondMin.y = projectedPoint.y : (projectedPoint.y > secondMax.y ? secondMax.y = projectedPoint.y : 0);
			projectedPoint.z < secondMin.z ? secondMin.z = projectedPoint.z : (projectedPoint.z > secondMax.z ? secondMax.z = projectedPoint.z : 0);
		}

		//Lastly check to see if there is overlap between the min and max for this axis and set minimum overlap.
		if (!Overlaps(firstMin, firstMax, secondMin, secondMax))
		{
			// minimum overlap checks
			if (minOverlap.x > abs(firstMin.x - secondMin.x)) { minOverlap.x = abs(firstMin.x - secondMin.x); } //x
			if (minOverlap.y > abs(firstMin.y - secondMin.y)) { minOverlap.y = abs(firstMin.y - secondMin.y); } //y
			if (minOverlap.z > abs(firstMin.z - secondMin.z)) { minOverlap.z = abs(firstMin.z - secondMin.z); } //z
			return false;
		}
	}

	return true;
}

bool CollisionData::Overlaps(glm::vec3 min1, glm::vec3 max1, glm::vec3 min2, glm::vec3 max2)
{
	bool areColliding = true;
	
	if (max1.x < min2.x)
		areColliding = false;
	if (min1.x > max2.x)
		areColliding = false;

	if (max1.y < min2.y)
		areColliding = false;
	if (min1.y > max2.y)
		areColliding = false;

	if (max1.z < min2.z)
		areColliding = false;
	if (min1.z > max2.z)
		areColliding = false;

	return areColliding;
}