/*=========================== LIBRARIES & MACROS ============================*/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "bst.h"
#define SUCCESS 0

/*============================== DECLARATIONS ===============================*/

static bst_node_t *CreateNode(const void*);
static bst_iter_t GoDirection(bst_t*, bst_iter_t,const void*);
__inline__ static bst_iter_t GetRootFromTree(const bst_t*);
__inline__ static bst_iter_t NodeToIter(bst_node_t*);
__inline__ static bst_node_t *IterToNode(bst_iter_t);

/*====================== STRUCT & FUNCTION DEFINITION =======================*/

struct bst_node
{
	void *data;
	bst_node_t *left;
	bst_node_t *right;
	bst_node_t *parent;
};

struct bst
{
	bst_node_t dummy;
	cmp_func_t cmp_func;
};

/* Approved by Michal */
bst_t *BSTCreate(cmp_func_t cmp_func)
{
	bst_t *tree = NULL;
	assert(NULL != cmp_func);
	tree = (bst_t*) malloc(sizeof(bst_t));
	
	if(NULL != tree)
	{
		tree->dummy.data = NULL;
		tree->dummy.left = NULL;
		tree->dummy.right = NULL;
		tree->dummy.parent = NULL;
		tree->cmp_func = cmp_func;
	}
	
	return (tree);
}

void BSTDestroy(bst_t *tree)
{
	bst_node_t *curr_node = NULL;
	bst_node_t *next_node = NULL;
	assert(NULL != tree);
	curr_node = BSTBegin(tree);
	
	while(&tree->dummy != curr_node)
	{
		next_node = BSTIterNext(curr_node);
		BSTRemove(curr_node);
		curr_node = next_node;
	}
	
	free(tree);
}

bst_iter_t BSTInsert(bst_t *tree, const void *data)
{
	bst_node_t *parent = NULL;
	bst_node_t *runner = NULL;
	bst_node_t *new_node = CreateNode(data);
	assert(NULL !=tree);
	parent = &tree->dummy;
	runner = GetRootFromTree(tree);
	
	if(NULL == new_node)
	{
		return (BSTEnd(tree));
	}
	
	while (NULL != runner) 
	{
		parent = runner;
		runner = GoDirection(tree, runner, data);
	}
    
	if (&tree->dummy == parent)
	{
		tree->dummy.left = new_node;
	}
	else if (0 > tree->cmp_func(data, BSTGetData(parent)))
	{
		parent->left = new_node;
	}
	else
	{
		parent->right = new_node;
	}
	
	new_node->parent = parent;
	
	return (new_node);
}

void BSTRemove(bst_iter_t where)
{
	bst_node_t *temp = NULL;
	bst_node_t *where_node = NULL;
	where_node = IterToNode(where);
	
	if(NULL != where_node->left && NULL != where_node->right)
	{
		temp = BSTIterNext(where_node);
		where_node->data = BSTGetData(temp);
		where_node = temp;
	}
	
	temp = (NULL == where_node->left) ? where_node->right : where_node->left;
	
	if(where_node == where_node->parent->left)
	{
		where_node->parent->left = temp;
	}
	else
	{
		where_node->parent->right = temp;
	}
	if(NULL != temp)
	{
		temp->parent = where_node->parent;
	}
	
	free(where_node);
}

bst_iter_t BSTFind(bst_t *tree, const void *data)
{
	bst_node_t *curr_node = NULL;
	assert(NULL != tree);
	curr_node = GetRootFromTree(tree);
	
	while(NULL != curr_node && 0 != tree->cmp_func(data, BSTGetData(curr_node)))
	{
		curr_node = GoDirection(tree, curr_node, data);	
	}
	
	return (curr_node != NULL ? curr_node : BSTEnd(tree));
}

int BSTForEach(bst_iter_t from, bst_iter_t to, action_func_t action_func, void *param)
{
	int func_rtn = SUCCESS;
	assert(NULL != action_func);
	
	while(!BSTIsEqual(from, to) && SUCCESS == func_rtn)
	{
		func_rtn = action_func(BSTGetData(from), param);
		from = BSTIterNext(from);
	}
	
	return (func_rtn);
}

bst_iter_t BSTIterNext(bst_iter_t where)
{
	bst_node_t *where_node = NULL;
	where_node = IterToNode(where);
	
	if (NULL != where_node->right)
	{
		where_node = where_node->right;
		while(NULL != where_node->left)
		{
			where_node = where_node->left;
		}
		return (where_node);
	}
    
	while (NULL != where_node->parent->parent && where_node == where_node->parent->right)
	{
		where_node = where_node->parent;
	}
    
	return (NodeToIter(where_node->parent));
}

bst_iter_t BSTIterPrev(bst_iter_t where)
{
	bst_node_t *where_node = NULL;
	where_node = IterToNode(where);
	
	if (NULL != where_node->left)
	{
		where_node = where_node->left;
		while(NULL != where_node->right)
		{
			where_node = where_node->right;
		}
		return (where_node);
	}
    
	while (NULL != where_node->parent->parent && where_node == where_node->parent->left)
	{
		where_node = where_node->parent;
	}
    
	return (NodeToIter(where_node->parent));
}

bst_iter_t BSTBegin(const bst_t *tree)
{
	bst_iter_t rtn_node = NULL;
	assert(NULL != tree);
	rtn_node = &((bst_t *)tree)->dummy;
	
	while(NULL != rtn_node->left)
	{
		rtn_node = rtn_node->left;
	}
	
	return (rtn_node);
}

bst_iter_t BSTEnd(const bst_t *tree)
{
	assert(NULL != tree);
	return ((bst_iter_t)&tree->dummy);
}

int BSTIsEmpty(const bst_t *tree)
{
	assert(NULL != tree);
	return(NULL == GetRootFromTree(tree));
}

size_t BSTSize(const bst_t *tree)
{
	size_t counter = 0;
	bst_iter_t runner = NULL;
	assert(NULL != tree);
	runner = BSTBegin(tree);
	
	while(&tree->dummy != runner)
	{
		++counter;
		runner = BSTIterNext(runner);
	}
	
	return (counter);
}

void *BSTGetData(bst_iter_t iter)
{
	return (iter->data);
}

int BSTIsEqual(bst_iter_t iter_one, bst_iter_t iter_two)
{
	return (IterToNode(iter_one) == IterToNode(iter_two));
}

static bst_iter_t GoDirection(bst_t *tree, bst_iter_t runner,const void* data)
{
	if (0 > tree->cmp_func(data, BSTGetData(runner)))
	{
		return runner->left;
	}
	return runner->right;
}

__inline__ static bst_iter_t NodeToIter(bst_node_t *node)
{
	return (node);
}

__inline__ static bst_node_t *IterToNode(bst_iter_t iter)
{
	return ((bst_node_t*)iter);
}

static bst_node_t *CreateNode(const void *data)
{
	bst_node_t *new_node = (bst_node_t*) malloc(sizeof(bst_node_t));
	
	if(NULL != new_node)
	{
		new_node->data = (void*)data;
		new_node->left = NULL;
		new_node->right = NULL;
	}
	
	return (new_node);
}

__inline__ static bst_iter_t GetRootFromTree(const bst_t *tree)
{
	return (tree->dummy.left);
}


