#ifndef BSP_TREE_H
#define BSP_TREE_H

#define NULL 0

struct Vertex
{
	int x;
	int z;
};

struct Plane
{
	int x1, z1;
	int x2, z2;
};

struct Object
{
	Vertex *vertices;
	unsigned nVertices;
	unsigned id;
};

struct TreeNode
{
	Object **pObjects;
	unsigned nObjects;
	TreeNode *left;
	TreeNode *right;
};

TreeNode *generateTree(Object *pObjects, unsigned nObjects, Plane *partitionPlanes, unsigned nPartitionPlanes);

#endif	/* BSP_TREE_H */