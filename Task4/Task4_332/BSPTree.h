#ifndef BSP_TREE_H
#define BSP_TREE_H

#define NULL 0

/* Vertex in 2d space */
struct Vertex
{
	int x;
	int z;
};

/* Plane in 2d space */
struct Plane
{
	int x1, z1;	
	int x2, z2;
};

/* Object in 2d space */
struct Object
{
	Vertex *vertices;	// Array of vertices
	unsigned nVertices;	// Array size
	unsigned id;		// Unique identifier
};

struct TreeNode
{
	Object **pObjects;			// Array of pointers to objects	
	unsigned nObjects;			// Array size
	Plane **partitionPlanes;	// Array of pointers to planes
	unsigned nPartitionPlanes;	// Array size
	TreeNode *left;				// Pointer to left tree node	
	TreeNode *right;			// Pointer to right tree node
};

/**
  * @brief	Print tree
  * @param	[in]    pObjects Pointer to an array of objects
  * @param	[in]    nObjects Number of objects in array
  * @param	[in]    partitionPlanes Pointer to an array of planes
  * @param	[in]    nPartitionPlanes Number of planes in array
  * @return	Root node of a new tree
  */
TreeNode *generateTree(Object *pObjects, unsigned nObjects, Plane *partitionPlanes, unsigned nPartitionPlanes);

/**
  * @brief	Print tree
  * @param	[in]    root Pointer to tree root
  * @return	void
  */
void printTree(TreeNode *root);

/**
  * @brief	Delete binary tree from memory
  * @param	[in]    root Pointer to tree root
  * @return	void
  */
void deleteTree(TreeNode *root);

#endif	/* BSP_TREE_H */