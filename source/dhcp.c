/*=========================== LIBRARIES & MACROS ============================*/

#include <stdlib.h> /* malloc, free */
#include <stdint.h> /* unit32_max */
#include <stdio.h>  /* sprintf */
#include <assert.h> /* assert */
#include <string.h> /* strlen */

#include "dhcp.h"

#define SERVER 254
#define BROADCAST 255

#define FAIL 1
#define SUCCESS 0
#define TRUE 1
#define FALSE 0
#define BYTE 8
#define LEAF 0
#define FREE (-1)
#define END_OF_MASK 1
#define IP_SIZE 32

/*============================== DECLARATIONS ===============================*/

typedef enum children
{
    ZERO = 0,
    ONE,
    NUM_OF_CHILDREN
} children_t;

struct dhcp
{
    struct dhcp_node *root;
    uint32_t mask;
    size_t mask_len;
};

typedef struct dhcp_node
{
    struct dhcp_node *children[NUM_OF_CHILDREN];
    int is_full;
} dhcp_node_t;

static int InitSubnet(dhcp_t *);
static dhcp_node_t *CreateNode(int);
static children_t GetPos(uint32_t, int);
static void UpdateFullness(dhcp_node_t *);
static void DestroyNodesRec(dhcp_node_t *);
static dhcp_node_t *GoToSubnetRoot(dhcp_t *);
static size_t CountLeavesRec(dhcp_node_t *, int);
static int IsIpFree(uint32_t, dhcp_node_t *, int);
static int IsIpInSubnet(const dhcp_t *, uint32_t);
static dhcp_node_t *FreeIpRec(dhcp_node_t *, uint32_t);
static uint32_t GetNextFreeIp(uint32_t, dhcp_node_t *, int);
static int AllocateIpRec(dhcp_node_t *, uint32_t, uint32_t *, int);

/*======================== FUNCTION DEFINITION ==========================*/

dhcp_t *DHCPCreate(uint32_t mask, size_t subnet_length)
{
    dhcp_t *dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
    if (dhcp != NULL)
    {
        dhcp->mask_len = subnet_length;
        dhcp->mask = mask;
        dhcp->root = CreateNode(FALSE);
        if (NULL == dhcp->root)
        {
            free(dhcp);
            return (NULL);
        }
        if (FAIL == InitSubnet(dhcp))
        {
            DHCPDestroy(dhcp);
            return (NULL);
        }
    }
    return (dhcp);
}

void DHCPDestroy(dhcp_t *dhcp)
{
    assert(NULL != dhcp);
    DestroyNodesRec(dhcp->root);
    free(dhcp);
}

int DHCPAllocateIp(dhcp_t *dhcp, uint32_t requested_ip, uint32_t *result_ip)
{
    dhcp_node_t *subnet_root = NULL;

    assert(NULL != dhcp);
    assert(NULL != result_ip);

    subnet_root = GoToSubnetRoot(dhcp);
    *result_ip = dhcp->mask;
    requested_ip = GetNextFreeIp(requested_ip, subnet_root, (IP_SIZE - dhcp->mask_len));
    if (FAIL == requested_ip || !IsIpInSubnet(dhcp, requested_ip))
    {
        return (FAIL);
    }
    return (AllocateIpRec(subnet_root, requested_ip, result_ip, ((IP_SIZE - 1) - dhcp->mask_len)));
}

void DHCPFreeIp(dhcp_t *dhcp, uint32_t ip)
{
    assert(NULL != dhcp);
    dhcp->root = FreeIpRec(dhcp->root, ip);
}

size_t DHCPCountFree(dhcp_t *dhcp)
{
    assert(NULL != dhcp);
    return ((UINT32_MAX / (1 << dhcp->mask_len)) - CountLeavesRec(dhcp->root, 0) + 1);
}

char *DHCPIpToString(uint32_t ip, char *dest_ip)
{
    int i = 3;
    unsigned char tmp = ' ';
    for (i = 3; 0 <= i; --i)
    {
        tmp = (ip >> (i * 8)) & 0xFF;
        sprintf(dest_ip + strlen(dest_ip), "%d.", tmp);
    }
    dest_ip[strlen(dest_ip) - 1] = '\0';
    return (dest_ip);
}

uint32_t DHCPStringToIp(char *ip)
{
    uint32_t rtn = 0;
    assert(NULL != ip);

    while (*ip != '\0')
    {
        rtn <<= BYTE;
        rtn |= strtol(ip, &ip, 10);
        if ('\0' != *ip)
        {
            ++ip;
        }
    }
    return (rtn);
}

static void DestroyNodesRec(dhcp_node_t *node)
{
    if (NULL != node)
    {
        DestroyNodesRec(node->children[ZERO]);
        node->children[ZERO] = NULL;
        DestroyNodesRec(node->children[ONE]);
        node->children[ONE] = NULL;
        free(node);
    }
}

static dhcp_node_t *CreateNode(int is_full)
{
    dhcp_node_t *node = (dhcp_node_t *)malloc(sizeof(dhcp_node_t));
    if (NULL != node)
    {
        node->is_full = is_full;
        node->children[ONE] = NULL;
        node->children[ZERO] = NULL;
    }
    return (node);
}

static size_t CountLeavesRec(dhcp_node_t *node, int index)
{
    if (node != NULL)
    {
        if (node->is_full == TRUE)
        {
            return (1 << (IP_SIZE - index));
        }
        return (CountLeavesRec(node->children[ZERO], index + 1) + CountLeavesRec(node->children[ONE], index + 1));
    }
    return (0);
}

static dhcp_node_t *FreeIpRec(dhcp_node_t *node, uint32_t ip)
{
    children_t side = GetPos(ip, (IP_SIZE - 1));
    if (NULL != node)
    {
        node->children[side] = FreeIpRec(node->children[side], ip << 1);
        if (node->children[ZERO] == NULL && node->children[ONE] == NULL)
        {
            free(node);
            return (NULL);
        }
        UpdateFullness(node);
    }
    return (node);
}

static int AllocateIpRec(dhcp_node_t *node, uint32_t requested_ip, uint32_t *result_ip, int index)
{
    uint32_t side = 0;
    if (index >= 0)
    {
        side = GetPos(requested_ip, index);
        if (NULL == node->children[side])
        {
            node->children[side] = (CreateNode(LEAF == index));
            if (NULL == node->children[side])
            {
                return (FAIL);
            }
        }
        *result_ip |= (side << index);

        if (FAIL == AllocateIpRec(node->children[side], requested_ip, result_ip, index - 1))
        {
            return (FAIL);
        }
    }
    if (NULL != node)
    {
        UpdateFullness(node);
    }
    return (SUCCESS);
}

static void UpdateFullness(dhcp_node_t *node)
{
    if (NULL == node->children[ZERO] && NULL == node->children[ONE])
    {
        node->is_full = TRUE;
        return;
    }
    if (NULL != node->children[ZERO] && TRUE == node->children[ZERO]->is_full &&
        NULL != node->children[ONE] && TRUE == node->children[ONE]->is_full)
    {
        node->is_full = TRUE;
        return;
    }
    node->is_full = FALSE;
}

static int InitSubnet(dhcp_t *dhcp)
{
    dhcp_node_t *node = dhcp->root;
    uint32_t mask = dhcp->mask;
    uint32_t unused = 0;
    size_t mask_len = dhcp->mask_len;
    children_t side;

    while (0 < mask_len)
    {
        side = GetPos(mask, (IP_SIZE - 1));
        node->children[side] = CreateNode(FALSE);
        if (NULL == node->children[side])
        {
            return (FAIL);
        }

        node = node->children[side];
        mask <<= 1;
        --mask_len;
    }

    DHCPAllocateIp(dhcp, dhcp->mask, &unused);
    DHCPAllocateIp(dhcp, dhcp->mask | SERVER, &unused);
    DHCPAllocateIp(dhcp, dhcp->mask | BROADCAST, &unused);

    return (SUCCESS);
}

static dhcp_node_t *GoToSubnetRoot(dhcp_t *dhcp)
{
    dhcp_node_t *node = dhcp->root;
    uint32_t mask = dhcp->mask;
    size_t mask_len = dhcp->mask_len;

    while (0 < mask_len)
    {
        node = node->children[GetPos(mask, (IP_SIZE - 1))];
        mask <<= 1;
        --mask_len;
    }
    return (node);
}

static children_t GetPos(uint32_t ip, int index)
{
    return (!!(ip & (1 << index)));
}

static int IsIpFree(uint32_t requested_ip, dhcp_node_t *node, int index)
{
    while (0 < index--)
    {
        node = node->children[GetPos(requested_ip, index)];
        if (NULL == node)
        {
            return (FREE);
        }
        if (TRUE == node->is_full)
        {
            return (index);
        }
    }
    return (FAIL);
}

static uint32_t GetNextFreeIp(uint32_t requested_ip, dhcp_node_t *node, int index)
{
    int curr_index = 0;
    do
    {
        curr_index = IsIpFree(requested_ip, node, index);
        if (curr_index == index)
        {
            return (FAIL); /*subroot is full*/
        }
        if (FREE != curr_index)
        {
            requested_ip += (1 << curr_index);
        }
    } while (FREE != curr_index);

    return (requested_ip);
}

static int IsIpInSubnet(const dhcp_t *dhcp, uint32_t requested_ip)
{
    return (0 == ((requested_ip ^ dhcp->mask) & (UINT32_MAX << (IP_SIZE - dhcp->mask_len))));
}