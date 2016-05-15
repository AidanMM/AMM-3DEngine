#include "MeshGenerator.h"

void MeshGenerator::GenerateModel(std::string system, int iterations, std::string modelName, glm::vec3 startingPoint, float radius, int pointsPerLevel)
{
	m_model = new Model(modelName);
	m_model->GetMesh()->m_compileSAT = false;
	system = m_system.ApplyAxioms(system, iterations);
	std::vector< std::pair<glm::vec3, glm::vec3>> pointCollections;
	glm::vec3 radiusVector = glm::vec3(radius, 0, 0);
	std::vector<std::pair<glm::vec3, glm::vec3>> pointStack;
	std::vector<int> closeOffIndeces;
	glm::vec3 translationVector = glm::vec3(0, 1, 0);
	glm::quat rotation = glm::quat(glm::vec3(rotationOffset, 0, 0));
	for (int i = 0; i < system.size(); i++)
	{
		switch (system[i])
		{
		case 't': //translate
			startingPoint -= translationVector;
			break;
		case 'T':
			startingPoint += translationVector;
			break;
		case 's': //scale smaller
			//radius /= scaleOffset;
			radiusVector /= scaleOffset;
			break;
		case 'S': //scale larger
			//radius *= scaleOffset;
			radiusVector *= scaleOffset;
			break;
		case 'r': //rotate counter clockwise
			translationVector = glm::rotate(-rotation, translationVector);
			radiusVector = glm::rotate(-rotation, translationVector);
			break;
		case 'R': //rotate clockwise
			translationVector = glm::rotate(rotation, translationVector);
			radiusVector = glm::rotate(rotation, translationVector);
			break;
		case 'c':
		case 'C':
			radiusVector *= 0.001f;
			closeOffIndeces.push_back(pointStack.size() - 1);
			break;
		case '[': //push point onto the stack
			pointStack.push_back(pointCollections.back());
			break;
		case ']': { //pop point from the stack
			std::pair<glm::vec3, glm::vec3> popped = pointStack.back();
			pointStack.pop_back();
			startingPoint = popped.first;
			radiusVector = popped.second;
		}
			break;
		case '+': //pushes the current point to be used on the geometry
			pointCollections.push_back(std::make_pair(startingPoint, radiusVector));
			break;
		default:
			break;
		}
	}
	//Create the vertices for the mesh
	std::vector<std::vector<glm::vec3>> meshGeometry;
	for (int i = 0; i < pointCollections.size(); i++)
	{
		std::vector<glm::vec3> pointsForIteration;
		for (int n = 0; n < pointsPerLevel; n++)
		{
			glm::vec3 vertex;
			vertex = pointCollections[i].first;
			glm::vec3 radVec = pointCollections[i].second;
			glm::vec3 rotAxis = vertex;
			if (glm::length(vertex) > 0)
				rotAxis = glm::normalize(rotAxis);
			else //Assume 0,1,0
				rotAxis = glm::vec3(0, 1, 0);
			float theta = 2 * PI / pointsPerLevel * n;
			radVec = radVec * cos(theta) + (glm::cross(rotAxis, radVec)) * sin(theta) + rotAxis * (glm::dot(rotAxis, radVec))* (1 - cos(theta));
			pointsForIteration.push_back(vertex + radVec);
		}
		meshGeometry.push_back(pointsForIteration);
	}
	//Create the face geometry for the mesh
	for (int i = 0; i < meshGeometry.size(); i++)
	{
		int currentSize = meshGeometry[i].size();
		int nextRowSize = meshGeometry[(i + 1) % meshGeometry.size()].size();
		for (int k = 0; k < currentSize; k++)
		{
			//Don't connect points to the next layer of the index is a close off point
			if (closeOffIndeces.size() > 0 && i == closeOffIndeces.front())
			{
				closeOffIndeces.erase(closeOffIndeces.begin());
				continue;
			}
			//Draw to the next layer of points, unless this is the first or last layer.
			//In those situations the shape needs to close, so connect those to the center points.
			if (i == 0)
			{
				m_model->AddTri(meshGeometry[i][k], meshGeometry[i][(k + 1) % currentSize], pointCollections[i].first);
			}
			if (i == meshGeometry.size() - 1)
			{
				m_model->AddTri(meshGeometry[i][k], meshGeometry[i][(k + 1) % currentSize], pointCollections[i].first);
				continue; //There are no more points to draw up to
			}
			//Need to draw the face
			// __
			//|\ |
			//|_\|
			//Two triangles per face
			//Draw the first triangle of the face
			m_model->AddTri(meshGeometry[i][k], meshGeometry[i][(k + 1) % currentSize], meshGeometry[i + 1][k]);
			m_model->AddTri(meshGeometry[i + 1][k], meshGeometry[i + 1][(k + 1) % currentSize], meshGeometry[i][(k + 1) % currentSize]);
		}
	}
	//Call compile shape to do this when this function is called instead of when the object needs to be rendered
	m_model->compileShape();
}
