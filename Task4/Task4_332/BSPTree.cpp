#include "BSPTree.h"
#include <iostream>

/**
  * @brief	Get objects position towards given plane
  * @param	[in]    pObject Pointer to an object
  * @param	[in]	partitionPlane Pointer to a partition plane
  * @return	Boolean value
  */
bool classifyObject(Object *pObject, Plane *partitionPlane)
{
	int sum = 0;

	for (int j = 0; j < pObject->nVertices; j++)
	{
		// Get position of each vertex towards plane
		int m = (partitionPlane->x2 - partitionPlane->x1) / 
				(partitionPlane->z2 - partitionPlane->z1);

		int res = pObject->vertices[j].x -  m * pObject->vertices[j].z + 
				  m * partitionPlane->z1 - partitionPlane->x1;

		// Sum values to get avarage rating
		sum += res;
	}

	if (sum < 0)
	{
		return false;
	}

	return true;
}

/**
  * @brief	Get plane position towards another plane
  * @param	[in]    plane Pointer to a plane
  * @param	[in]	partitionPlane Pointer to a partition plane
  * @return	Boolean value
  */
bool classifyPlane(Plane *plane, Plane *partitionPlane)
{

	int m = (partitionPlane->x2 - partitionPlane->x1) / 
			(partitionPlane->z2 - partitionPlane->z1);

	int res = plane->x1 -  m * plane->z1 + m * partitionPlane->z1 - partitionPlane->x1;
	res += plane->x2 -  m * plane->z2 + m * partitionPlane->z1 - partitionPlane->x1;

	if (res < 0)
	{
		return false;
	}

	return true;
}

/**
  * @brief	Split tree node to left or (and) right
  * @param	[in]	node Pointer to tree node
  * @return	void
  */
void splitTree(TreeNode *node)
{
	// No planes - no more splitting
	if (node->nPartitionPlanes == 0)
	{
		return;
	}

	// Get first plane from array in given node
	Plane *current = node->partitionPlanes[0];

	// Count number of objects to both sides of the plane
	int kLeft = 0, kRight = 0;
	for (int i = 0; i < node->nObjects; i++)
	{
		bool f = classifyObject(node->pObjects[i], current);
		if (!f)
		{
			kLeft++;
		}
		else
		{
			kRight++;
		}
	}

	// Count number of planes to both sides of the plane
	int kpLeft = 0, kpRight = 0;
	for (int i = 1; i < node->nPartitionPlanes; i++)
	{
		bool f = classifyPlane(node->partitionPlanes[i], current);
		if (!f)
		{
			kpLeft++;
		}
		else
		{
			kpRight++;
		}
	}

	// There are objects to the "right" side
	if (kRight > 0)
	{
		// Create new node
		node->right = new TreeNode;
		TreeNode *temp = node->right;

		temp->nObjects = kRight;
		temp->pObjects = new Object*[kRight];

		// Copy object pointers to new node
		for (int i = 0, k = 0; i < node->nObjects; i++)
		{
			if (classifyObject(node->pObjects[i], current))
			{
				temp->pObjects[k] = node->pObjects[i];
				k++;
			}
		}

		temp->left = NULL;
		temp->right = NULL;

		temp->nPartitionPlanes = kpRight;
		temp->partitionPlanes = new Plane*[kpRight];

		// Copy plane pointers to new node
		for (int i = 1, k = 0; i < node->nPartitionPlanes; i++)
		{
			if (classifyPlane(node->partitionPlanes[i], current))
			{
				temp->partitionPlanes[k] = node->partitionPlanes[i];
				k++;
			}
		}

		// Recursive call for created node
		splitTree(temp);
	}

	// There are objects to the "left" side
	if (kLeft > 0)
	{
		// Create new node
		node->left = new TreeNode;
		TreeNode *temp = node->left;

		temp->nObjects = kLeft;
		temp->pObjects = new Object*[kLeft];

		// Copy object pointers to new node
		for (int i = 0, k = 0; i < node->nObjects; i++)
		{
			if (!classifyObject(node->pObjects[i], current))
			{
				temp->pObjects[k] = node->pObjects[i];
				k++;
			}
		}

		temp->left = NULL;
		temp->right = NULL;

		temp->nPartitionPlanes = kpLeft;
		temp->partitionPlanes = new Plane*[kpLeft];

		// Copy plane pointers to new node
		for (int i = 1, k = 0; i < node->nPartitionPlanes; i++)
		{
			if (!classifyPlane(node->partitionPlanes[i], current))
			{
				temp->partitionPlanes[k] = node->partitionPlanes[i];
				k++;
			}
		}

		// Recursive call for created node
		splitTree(temp);
	}
}

TreeNode *generateTree(Object *pObjects, unsigned nObjects, Plane *partitionPlanes, unsigned nPartitionPlanes)
{
	if (!pObjects || !partitionPlanes)
	{
		return NULL;
	}

	// Create root
	TreeNode *root = new TreeNode;
	root->left = NULL;
	root->right = NULL;

	// Copy pointers to initial array of objects
	root->nObjects = nObjects;
	root->pObjects = new Object*[nObjects];
	for (int i = 0; i < nObjects; i++)
	{
		root->pObjects[i] = &pObjects[i];
	}

	// Copy pointers to initial array of planes
	root->nPartitionPlanes = nPartitionPlanes;
	root->partitionPlanes = new Plane*[nPartitionPlanes];
	for (int i = 0; i < nPartitionPlanes; i++)
	{
		root->partitionPlanes[i] = &partitionPlanes[i];
	}

	// Start splitting tree
	splitTree(root);

	return root;
}

void printTree(TreeNode *root)
{
	if (root)
	{
		for (int i = 0; i < root->nObjects; i++)
		{
			std::cout << (char)root->pObjects[i]->id;
		}
		std::cout << std::endl;

		if (root->right)
		{
			std::cout << "Right" << std::endl;
			printTree(root->right);
		}

		if (root->left)
		{
			std::cout << "Left" << std::endl;
			printTree(root->left);
		}
	}
}

void deleteTree(TreeNode *root)
{
	if (root)
	{
		deleteTree(root->right);
		deleteTree(root->left);
		delete root;
	}
}