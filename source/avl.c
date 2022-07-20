/*=========================== LIBRARIES & MACROS ============================*/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include "avl.h"

#define MAX(a,b) (((a)>(b))?(a):(b))
#define FLIP(x) (((RIGHT) == (x)) ? (LEFT):(RIGHT))
#define SUCCESS 0
#define FAIL 1

/*============================== DECLARATIONS ===============================*/

typedef enum child
{
	LEFT = 0,
	RIGHT,
	NUM_CHILDREN
}child_t;

typedef struct avl_node
{
    void *data;
    size_t height;
    struct avl_node *child[NUM_CHILDREN];
}avl_node_t;

struct avl
{
    avl_node_t *root;
    cmp_func_t cmp_func;
};

/* Recursive Funcs */
static avl_node_t *InsertRec(cmp_func_t, avl_node_t*, avl_node_t*);
static avl_node_t *RemoveRec(avl_node_t*, const void*, cmp_func_t);
static int ForEachRecPost(action_func_t, avl_node_t*, void*);
static int ForEachRecPre(action_func_t, avl_node_t*, void*);
static int ForEachRecIn(action_func_t, avl_node_t*, void*);
static void *FindRec(cmp_func_t, avl_node_t*, void*);
static void DestroyNodesRec(avl_node_t*);
static size_t SizeRec(avl_node_t*);
/* Helper Funcs */
static avl_node_t *RotateSubTree(avl_node_t*, child_t);
static long GetChildHeight(avl_node_t*, child_t);
static avl_node_t *FindLeftmost(avl_node_t*);
static avl_node_t *BalanceNode(avl_node_t*);
static size_t UpdateNodeHeight(avl_node_t*);
static long GetHeightDiff(avl_node_t*);
static avl_node_t *CreateNode(void*);

/*====================== FUNCTION DEFINITION =======================*/

avl_t *AVLCreate(cmp_func_t cmp_func)
{
	avl_t *tree = NULL;
	assert(NULL != cmp_func);
	tree = (avl_t*) malloc(sizeof(avl_t));
	if(NULL != tree)
	{
		tree->root = NULL;
		tree->cmp_func = cmp_func;
	}
	return (tree);
}

void AVLDestroy(avl_t *tree)
{
	assert(NULL != tree);
	DestroyNodesRec(tree->root);
	free(tree);
}

int AVLInsert(avl_t *tree, void *data)
{
	avl_node_t *new_node = NULL;
	assert(NULL != tree);
	new_node = CreateNode(data);
	if(NULL == new_node)
	{
		return (1);
	}
	tree->root = InsertRec(tree->cmp_func, tree->root, new_node);
	return (0);
}

void AVLRemove(avl_t *tree, const void *data)
{
	assert(NULL != tree);
	tree->root = RemoveRec(tree->root, data, tree->cmp_func);
}

int AVLIsEmpty(const avl_t *tree)
{
	assert(NULL != tree);
	return (NULL == tree->root);
}

size_t AVLSize(const avl_t *tree)
{
	assert(NULL != tree);
	return (SizeRec(tree->root));
}

size_t AVLHeight(const avl_t *tree)
{
	assert(NULL != tree);
	return ((NULL == tree->root) ? 0 : tree->root->height);
}

void *AVLFind(const avl_t *tree, const void *data)
{
	assert(NULL != tree);
	return (FindRec(tree->cmp_func, tree->root, (void *)data));
}

int AVLForEach(avl_t *tree, action_func_t action_func, void *param, traverse_t type)
{
	int status = -1;
	assert(NULL != tree);
	assert(NULL != action_func);
	switch(type)
	{
		case (PRE_ORDER):
			status = (ForEachRecPre(action_func, tree->root, param));
			break;
		case (IN_ORDER):
			status = (ForEachRecIn(action_func, tree->root, param));
			break;
		case (POST_ORDER):
			status = (ForEachRecPost(action_func, tree->root, param));
			break;
	}
	return (status);
}

static void DestroyNodesRec(avl_node_t *node)
{
	if(NULL == node)
	{
		return;
	}
	DestroyNodesRec(node->child[LEFT]);
	node->child[LEFT] = NULL;
	DestroyNodesRec(node->child[RIGHT]);
	node->child[RIGHT] = NULL;
	free(node);
}

static avl_node_t *InsertRec(cmp_func_t cmp_func, avl_node_t *node, avl_node_t *to_insert)
{
	if(NULL == node)
	{
		return (to_insert);
	}
	if(0 < cmp_func(to_insert->data, node->data))
	{
		node->child[RIGHT] = InsertRec(cmp_func, node->child[RIGHT], to_insert);		
	}
	else
	{
		node->child[LEFT] = InsertRec(cmp_func, node->child[LEFT], to_insert);		
	}
	node->height = UpdateNodeHeight(node);
	return (BalanceNode(node));
}

static avl_node_t *RemoveRec(avl_node_t *node, const void *data, cmp_func_t cmp_func)
{
	int func_rtn = 0;
	if (NULL == node)
	{
		return (node);
	}
	func_rtn = cmp_func(data, node->data);
	if (0 > func_rtn)
	{    
		node->child[LEFT] = RemoveRec(node->child[LEFT], data, cmp_func);
	}
	else if (0 < func_rtn)
	{
		node->child[RIGHT] = RemoveRec(node->child[RIGHT], data, cmp_func);
	} 
	else 
	{
		avl_node_t *temp = NULL;
		if(NULL == node->child[LEFT] || NULL == node->child[RIGHT])
		{
			temp = ((NULL == node->child[LEFT]) ? node->child[RIGHT] : node->child[LEFT]);
			free(node);
			return (temp);
		}
		temp = FindLeftmost(node->child[RIGHT]);
		node->data = temp->data;
		node->child[RIGHT] = RemoveRec(node->child[RIGHT], temp->data, cmp_func);
	}
	node->height = UpdateNodeHeight(node);
	return (BalanceNode(node));
}

static size_t SizeRec(avl_node_t *node)
{
	return ((NULL == node) ? 0 : (1 + SizeRec(node->child[RIGHT]) + SizeRec(node->child[LEFT])));
}

static void *FindRec(cmp_func_t cmp_func, avl_node_t *node, void *data)
{
	int func_rtn = 0;
	if(NULL == node)
	{
		return (node);
	}
	func_rtn = cmp_func(data, node->data);
	if(0 == func_rtn)
	{
		return (node->data);
	}
	if(0 < func_rtn)
	{
		return FindRec(cmp_func, node->child[RIGHT], data);
	}
	return (FindRec(cmp_func, node->child[LEFT], data));
}

static int ForEachRecPre(action_func_t action_func, avl_node_t *node, void *param)
{
	return (
	(NULL == node) ? (SUCCESS) :
	(SUCCESS != action_func(node->data, param)) ? (FAIL) :
	(SUCCESS != ForEachRecPre(action_func, node->child[LEFT], param)) ? (FAIL) :
	(SUCCESS != ForEachRecPre(action_func, node->child[RIGHT], param)) ? (FAIL) :
	(SUCCESS));
}

static int ForEachRecIn(action_func_t action_func, avl_node_t *node, void *param)
{
	return (
	(NULL == node) ? (SUCCESS) :
	(SUCCESS != ForEachRecPre(action_func, node->child[LEFT], param)) ? (FAIL) :
	(SUCCESS != action_func(node->data, param)) ? (FAIL) :
	(SUCCESS != ForEachRecPre(action_func, node->child[RIGHT], param)) ? (FAIL) :
	(SUCCESS));
}

static int ForEachRecPost(action_func_t action_func, avl_node_t *node, void *param)
{
	return (
	(NULL == node) ? (SUCCESS) :
	(SUCCESS != ForEachRecPre(action_func, node->child[LEFT], param)) ? (FAIL) :
	(SUCCESS != ForEachRecPre(action_func, node->child[RIGHT], param)) ? (FAIL) :
	(SUCCESS != action_func(node->data, param)) ? (FAIL) :
	(SUCCESS));
}

static avl_node_t *BalanceNode(avl_node_t *node)
{
	long height_diff = GetHeightDiff(node);
	if(height_diff > 1)
	{
		if(GetHeightDiff(node->child[LEFT]) < 0)
		{
			node->child[LEFT] = RotateSubTree(node->child[LEFT], LEFT);
		}
		return (RotateSubTree(node, RIGHT));
	}
	if(height_diff < -1)
	{
		if(GetHeightDiff(node->child[RIGHT]) > 0)
		{
			node->child[RIGHT] = RotateSubTree(node->child[RIGHT], RIGHT);
		}
		return (RotateSubTree(node, LEFT));
	}
	return (node);
}

static avl_node_t *RotateSubTree(avl_node_t *node, child_t direction)
{
	avl_node_t *new_root = node->child[FLIP(direction)];
	node->child[FLIP(direction)] = new_root->child[direction];
	new_root->child[direction] = node;
	node->height = UpdateNodeHeight(node);
	new_root->height = UpdateNodeHeight(new_root);
	return (new_root);
}

static long GetHeightDiff(avl_node_t *node)
{
	return (GetChildHeight(node, LEFT) - GetChildHeight(node, RIGHT));
}

static size_t UpdateNodeHeight(avl_node_t *node)
{
	return (MAX(GetChildHeight(node, LEFT), GetChildHeight(node, RIGHT)) + 1);
}

static long GetChildHeight(avl_node_t *node, child_t direction)
{
	return ((NULL == node->child[direction]) ? 0 : node->child[direction]->height);
}

static avl_node_t *FindLeftmost(avl_node_t *node)
{
	return ((NULL == node->child[LEFT]) ? node : FindLeftmost(node->child[LEFT]));
}

static avl_node_t *CreateNode(void *data)
{
	avl_node_t *new_node = (avl_node_t*) malloc(sizeof(avl_node_t));
	if(NULL != new_node)
	{
		new_node->data = data;
		new_node->height = 1;
		new_node->child[LEFT] = NULL;
		new_node->child[RIGHT] = NULL;
	}
	return (new_node);
}


