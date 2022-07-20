/*=========================== LIBRARIES & MACROS ============================*/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <math.h> /* pow, sqrt */
#include <string.h> /* strcmp, strcat */
#include <strings.h> /* strcasecmp */
#include <stdio.h> /* printf */
#include "hasht.h"

#define SUCCESS 0
#define FAIL 1
#define DICT_CAP 26
#define MAX_WORD_LEN 20
#define NUM_OF_WORDS 102401

/*============================== DECLARATIONS ===============================*/

struct hasht
{
	dlist_t **table;
	hash_func_t hash_func;
	hash_is_match_t cmp_func;
	size_t exp_cap;
};

static char **DictCreate();
static int DictFill(char**);
static void DictDestroy(char**);
static void CheckInput(hasht_t*);
static void FillTable(hasht_t*, char **);
static size_t SCHashByFirstChar(const void*);
static void DestroyAllLists(size_t, hasht_t*);
static size_t GetIndexFromKey(hasht_t*, void*);
static int SCCompareStrings(const void*, const void*);

/*============================== DEFINITIONS ===============================*/

hasht_t *HashtCreate(size_t exp_cap, hash_is_match_t cmp_func, hash_func_t hash_func)
{
	int i = 0;
	hasht_t *table = (hasht_t*)malloc(sizeof(hasht_t));
	if(NULL == table)
	{
		return (NULL);
	}
	table->table = (dlist_t**)malloc(sizeof(dlist_t*) * exp_cap);
	if(NULL == table->table)
	{
		free(table);
		return (NULL);
	}
	for(; i < (int)exp_cap; ++i)
	{
		table->table[i] = DoublyListCreate();
		if(NULL == table->table[i])
		{
			break;
		}
	}
	if(i != (int)exp_cap)
	{
		DestroyAllLists(i - 1, table);
		free(table->table);
		free(table);
		return (NULL);
	}
	table->exp_cap = exp_cap;
	table->hash_func = hash_func;
	table->cmp_func = cmp_func;
	return (table);
}

void HashtDestroy(hasht_t *table)
{
	assert(NULL != table);
	DestroyAllLists(table->exp_cap, table);
	free(table->table);
	free(table);
}

int HashtInsert(hasht_t *table, void *data)
{
	dlist_t *insert_into = NULL;
	assert(NULL != table);
	insert_into = table->table[GetIndexFromKey(table, data)];
	if(DoublyListEnd(insert_into) != DoublyListPushBack(insert_into, data))
	{
		return (FAIL);
	}
	return (SUCCESS);
}

void HashtRemove(hasht_t *table, void *key)
{
	dlist_t *remove_from = NULL;
	dlist_iter_t to_remove = NULL;
	assert(NULL != table);
	remove_from = table->table[GetIndexFromKey(table, key)];
	to_remove = DoublyListFind(DoublyListBegin(remove_from), DoublyListEnd(remove_from), table->cmp_func, key);
	if(!DoublyListIsSameIter(to_remove, DoublyListEnd(remove_from)))
	{
		DoublyListRemove(to_remove);
	}
}

int HashtIsEmpty(const hasht_t *table)
{
	size_t i = 0, is_empty = 1;
	assert(NULL != table);
	for(; i < table->exp_cap; ++i)
	{
		if(!DoublyListIsEmpty(table->table[i]))
		{
			is_empty = 0;
			break;
		}
	}
	return (is_empty);
}

size_t HashtSize(const hasht_t *table)
{
	size_t i = 0, counter = 0;
	assert(NULL != table);
	for(; i < table->exp_cap; ++i)
	{
		counter += DoublyListSize(table->table[i]);
	}
	return(counter);
}

void *HashtFind(const hasht_t *table, const void *key)
{
	dlist_t *find_in = NULL;
	dlist_iter_t found = NULL;
	void *data = NULL;
	assert(NULL != table);
	find_in = table->table[GetIndexFromKey((hasht_t*)table, (void*)key)];
	found = DoublyListFind(DoublyListBegin(find_in), DoublyListEnd(find_in), table->cmp_func, key);
	data = DoublyListGetData(found);
	if(!DoublyListIsSameIter(found, DoublyListEnd(find_in)))
	{
		DoublyListRemove(found);
		DoublyListPushFront(find_in, data);
	}
	return (data);
}

int HashtForEach(hasht_t *table, action_func_t action_func, void *param)
{
	size_t i = 0;
	int status = SUCCESS;
	assert(NULL != table);
	assert(NULL != action_func);
	for(; i < table->exp_cap && FAIL != status; ++i)
	{
		status = DoublyListForEach(DoublyListBegin(table->table[i]), DoublyListEnd(table->table[i]), action_func, param);
	}
	return (status);
}

double HashtLoad(const hasht_t *table)
{
	assert(NULL != table);
	return (HashtSize(table) / (double)table->exp_cap);
}

double HashtStandardDeviation(const hasht_t *table)
{
	double load = 0, counter = 0;
	size_t i = 0;
	assert(NULL != table);
	load = HashtLoad(table);
	for(; i < table->exp_cap; ++i)
	{
		counter += pow((DoublyListSize(table->table[i]) - load), 2);
	}
	counter /= table->exp_cap;
	return (sqrt(counter));
}

void SpellChecker()
{
	hasht_t *table = HashtCreate(DICT_CAP, SCCompareStrings, SCHashByFirstChar);  
	char **dict = DictCreate();

	if(NULL == dict)
	{
		HashtDestroy(table);
		return;
	}

	if(SUCCESS != DictFill(dict))
	{
		DictDestroy(dict);
		HashtDestroy(table);
		return;
	}

	FillTable(table, dict);
	CheckInput(table);
	
	DictDestroy(dict);
	HashtDestroy(table);
}

static void DestroyAllLists(size_t to, hasht_t *table)
{
	size_t from = 0;
	for(; from < to; ++from)
	{
		DoublyListDestroy(table->table[from]);
	}
}

static void CheckInput(hasht_t *table)
{
	char input[MAX_WORD_LEN]= "";
	while(1)
	{
		printf("Enter a word (or '-quit' to quit):\n");
		scanf("%s", input);
		if(strcmp(input, "-quit") == 0)
		{
		    break;
		}
		strcat(input, "\n");
		if(NULL != HashtFind(table, input))
		{
		    printf("This word exists\n");
		    continue;
		}
		printf("This word doesn't exist\n");
	}
}

static void FillTable(hasht_t *table, char **dict)
{
	int i = 0;
	for (; i < NUM_OF_WORDS; ++i)
	{
		HashtInsert(table, dict[i]);
	}
}

static char **DictCreate()
{
	int i = 0;
	char **dict = (char**)malloc(sizeof(char*) * NUM_OF_WORDS);

	for (i = 0; i < NUM_OF_WORDS; ++i)
	{
		dict[i] = (char*)malloc(MAX_WORD_LEN);
		if(NULL == dict[i])
		{
		    break;
		}
	}
	if(i != NUM_OF_WORDS)
	{
		for (i -= 1; i >= 0; --i)
		{
		    free(dict[i]);
		}
		free(dict);
		return (NULL);
	}
	return (dict);
}

static void DictDestroy(char **dict)
{
	int i = 0;
	for (; i < NUM_OF_WORDS; ++i)
	{
		free(dict[i]);
	}
	free(dict);
}

static int DictFill(char **dict)
{
	int i = 0;
	FILE *fp = fopen("./test/american-english.txt","r");

	if(NULL == fp)
	{
		return (FAIL);
	}
	for(; i < NUM_OF_WORDS; ++i) 
	{
		fgets(dict[i],MAX_WORD_LEN,fp);
	}

	if(0 != fclose(fp))
	{
		return (FAIL);
	}
	return (SUCCESS);
}

static size_t GetIndexFromKey(hasht_t *table, void *data)
{
	return (table->hash_func(data) % table->exp_cap);
}

static size_t SCHashByFirstChar(const void *data)
{
	return (*(char*)data % DICT_CAP);
}

static int SCCompareStrings(const void *data1, const void *data2)
{
	return (0 == strcasecmp((char*)data1, (char*)data2));
}


