#include "MeshGenerator.h"

void MeshGenerator::GenerateModel(std::string system, int iterations, std::string modelName, glm::vec3 startingPoint, float radius, int pointsPerLevel)
{
	m_model = new Model(modelName);
	m_model->GetMesh()->m_compileSAT = false;
	system = m_system.ApplyAxioms(system, iterations);
	std::vector< std::pair<glm::vec3, glm::vec3>> pointCollections;
	glm::vec3 radiusVector = glm::vec3(radius, 0, 0);
	std::vector<std::pair<glm::vec3, std::pair<glm::vec3, glm::vec3>>> pointStack;
	std::vector<int> closeOffIndeces;
	glm::vec3 translationVector = glm::vec3(0, translationOffset, 0);
	glm::quat rotationX = glm::quat(glm::vec3(rotationOffset, 0, 0));
	glm::quat negRotationX = glm::quat(glm::vec3(-rotationOffset, 0, 0));
	glm::quat rotationY = glm::quat(glm::vec3(0, rotationOffset, 0));
	glm::quat negRotationY = glm::quat(glm::vec3(0, -rotationOffset, 0));
	glm::quat rotationZ = glm::quat(glm::vec3(0, 0, rotationOffset));
	glm::quat negRotationZ = glm::quat(glm::vec3(0, 0, -rotationOffset));
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
			radiusVector /= scaleOffset;
			break;
		case 'S': //scale larger
			radiusVector *= scaleOffset;
			break;
		case 'x': 
			translationVector = glm::rotate(rotationX, translationVector);
			break;
		case 'X': 
			translationVector = glm::rotate(negRotationX, translationVector);
			break;
		case 'y':
			translationVector = glm::rotate(rotationY, translationVector);
			break;
		case 'Y':
			translationVector = glm::rotate(negRotationY, translationVector);
			break;
		case 'z':
			translationVector = glm::rotate(rotationZ, translationVector);
			break;
		case 'Z':
			translationVector = glm::rotate(negRotationZ, translationVector);
			break;
		case '[': //push point onto the stack
			if (pointCollections.size() > 0)
			{
				std::pair<glm::vec3, glm::vec3> pointCollectionBack = pointCollections.back();
				pointStack.push_back(std::make_pair(pointCollectionBack.first, std::make_pair(pointCollectionBack.second, translationVector)));
			}
			else
				pointStack.push_back(std::make_pair(startingPoint, std::make_pair(radiusVector, translationVector)));
			break;
		case ']': { //pop point from the stack
			std::pair<glm::vec3, std::pair<glm::vec3, glm::vec3>> popped = pointStack.back();
			pointStack.pop_back();
			startingPoint = popped.first;
			radiusVector = popped.second.first;
			translationVector = popped.second.second;
		}
			break;
		case 'c':
		case 'C':
			closeOffIndeces.push_back(pointCollections.size() - 1);
			break;
		case '+': //pushes the current point to be used on the geometry
			pointCollections.push_back(std::make_pair(startingPoint, radiusVector));
			break;
		case 'F':
			startingPoint += translationVector;
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
			if (i - 1 > 0)
				rotAxis = rotAxis - pointCollections[i - 1].first;
			if (glm::length(vertex) > 0)
				rotAxis = glm::normalize(rotAxis);
			else if (i + 1 < pointCollections.size())
				rotAxis = pointCollections[i + 1].first - rotAxis;
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
		bool closedOff = false;
		for (int k = 0; k < currentSize; k++)
		{
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
			//Don't connect points to the next layer of the index is a close off point
			if (closedOff || (closeOffIndeces.size() > 0 && i == closeOffIndeces.front()))
			{
				m_model->AddTri(meshGeometry[i][k], meshGeometry[i][(k + 1) % currentSize], pointCollections[i].first);
				closedOff = true;
				continue;
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
		if(closedOff)
			closeOffIndeces.erase(closeOffIndeces.begin());
	}
	//Call compile shape to do this when this function is called instead of when the object needs to be rendered
	m_model->compileShape();
}
