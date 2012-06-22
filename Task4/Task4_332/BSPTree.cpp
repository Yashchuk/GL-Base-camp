#include "BSPTree.h"
#include <iostream>

void splitTree(TreeNode *node, Plane *partitionPlanes, unsigned currentPlane, unsigned nPlanes)
{
	
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

	splitTree(root, partitionPlanes, 0, nPartitionPlanes);

	return root;
}

