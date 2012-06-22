#ifndef BSP_TREE_H
#define BSP_TREE_H

struct Vertex
{
	int x;
	int z;
};

struct Plane
{
	int x1, y1;
	int x2, y2;
};

struct Object
{
	Vertex *vertices;
	unsigned nVertices;
	unsigned id;
};

struct TreeNode
{
	Plane partitionPlane[2];
	Object *pObjects;
	unsigned nObjects;
	TreeNode *left;
	TreeNode *right;
};

TreeNode *generateTree(Object *pObjects, unsigned nObjects, Plane *partitionPlanes, unsigned nPartitionPlanes);

#endif	/* BSP_TREE_H */