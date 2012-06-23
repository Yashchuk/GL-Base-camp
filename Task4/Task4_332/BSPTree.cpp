#include "BSPTree.h"
#include <iostream>

bool classifyObject(Object *pObject, Plane *partitionPlane)
{
	int sum = 0;

	for (int j = 0; j < pObject->nVertices; j++)
	{
		int m = (partitionPlane->x2 - partitionPlane->x1) / 
				(partitionPlane->z2 - partitionPlane->z1);

		int res = pObject->vertices[j].x -  m * pObject->vertices[j].z + 
				  m * partitionPlane->z1 - partitionPlane->x1;

		sum += res;
	}

	if (sum < 0)
	{
		return false;
	}

	return true;
}

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

void splitTree(TreeNode *node)
{
	if (node->nPartitionPlanes == 0)
	{
		return;
	}

	Plane *current = node->partitionPlanes[0];

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

	if (kRight > 0)
	{
		node->right = new TreeNode;
		TreeNode *temp = node->right;

		temp->nObjects = kRight;
		temp->pObjects = new Object*[kRight];

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

		for (int i = 1, k = 0; i < node->nPartitionPlanes; i++)
		{
			if (classifyPlane(node->partitionPlanes[i], current))
			{
				temp->partitionPlanes[k] = node->partitionPlanes[i];
				k++;
			}
		}

		splitTree(temp);
	}
	if (kLeft > 0)
	{
		node->left = new TreeNode;
		TreeNode *temp = node->left;

		temp->nObjects = kLeft;
		temp->pObjects = new Object*[kLeft];

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

		for (int i = 1, k = 0; i < node->nPartitionPlanes; i++)
		{
			if (!classifyPlane(node->partitionPlanes[i], current))
			{
				temp->partitionPlanes[k] = node->partitionPlanes[i];
				k++;
			}
		}

		splitTree(temp);
	}
}

TreeNode *generateTree(Object *pObjects, unsigned nObjects, Plane *partitionPlanes, unsigned nPartitionPlanes)
{
	TreeNode *root = new TreeNode;
	root->left = NULL;
	root->right = NULL;

	root->nObjects = nObjects;
	root->pObjects = new Object*[nObjects];
	for (int i = 0; i < nObjects; i++)
	{
		root->pObjects[i] = &pObjects[i];
	}

	root->nPartitionPlanes = nPartitionPlanes;
	root->partitionPlanes = new Plane*[nPartitionPlanes];
	for (int i = 0; i < nPartitionPlanes; i++)
	{
		root->partitionPlanes[i] = &partitionPlanes[i];
	}

	splitTree(root);

	return root;
}

