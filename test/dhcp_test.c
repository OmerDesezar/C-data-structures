#include <stdio.h>  /* printf */
#include <string.h> /* strcmp */
#include "dhcp.h"

static void TestAllFuncs();
static void TestCreate();
static void TestDestroy();
static void TestAllocate();
static void TestFree();
static void TestCount();
static void TestStringIpConversion();

int main()
{
    TestAllFuncs();
    return (0);
}

static void TestAllFuncs()
{
    printf("     ~START OF TEST FUNCTION~ \n");
    TestCreate();
    TestCount();
    TestStringIpConversion();
    TestAllocate();
    TestFree();
    TestDestroy();
    printf("      ~END OF TEST FUNCTION~ \n");
}

static void TestCreate()
{
    dhcp_t *dhcp = DHCPCreate(DHCPStringToIp("192.188.0.0"), 16);

    if (NULL != dhcp)
    {
        printf("DHCPCreate working!                                  V\n");
    }
    else
    {
        printf("DHCPCreate NOT working!                              X\n");
    }

    DHCPDestroy(dhcp);
}

static void TestDestroy()
{
    printf("*Run vlg to test DHCPDestroy*\n");
}

static void TestStringIpConversion()
{
    char str[50] = "192.144.0.0";
    char str2[50] = {0};
    uint32_t ip = DHCPStringToIp(str);
    DHCPIpToString(ip, str2);
    if (0 == strcmp(str, str2))
    {
        printf("DHCPStringToIp & DHCPIpToString working!             V\n");
    }
    else
    {
        printf("DHCPStringToIp & DHCPIpToString NOT working!         X\n");
    }
}

static void TestCount()
{
    dhcp_t *dhcp = DHCPCreate(DHCPStringToIp("192.188.0.0"), 16);
    dhcp_t *dhcp2 = DHCPCreate(DHCPStringToIp("111.222.333.0"), 24);
    if (65533 == DHCPCountFree(dhcp) && 253 == DHCPCountFree(dhcp2))
    {
        printf("DHCPCountFree working!                               V\n");
    }
    else
    {
        printf("DHCPCountFree NOT working!                           X\n");
    }

    DHCPDestroy(dhcp);
    DHCPDestroy(dhcp2);
}

static void TestAllocate()
{
    uint32_t new_ip = 0;
    uint32_t new_ip2 = 0;
    dhcp_t *dhcp = DHCPCreate(DHCPStringToIp("192.188.0.0"), 16);
    DHCPAllocateIp(dhcp, DHCPStringToIp("192.188.1.1"), &new_ip);
    DHCPAllocateIp(dhcp, DHCPStringToIp("192.188.1.1"), &new_ip2);

    if (3233546497 == new_ip && 3233546498 == new_ip2)
    {
        printf("DHCPAllocateIp working!                              V\n");
    }
    else
    {
        printf("DHCPAllocateIp NOT working!                          X\n");
    }
    DHCPDestroy(dhcp);
}

static void TestFree()
{
    uint32_t new_ip = 0;
    uint32_t new_ip2 = 0;
    int size_before = 0;
    int size_after = 0;
    dhcp_t *dhcp = DHCPCreate(DHCPStringToIp("192.188.0.0"), 16);
    DHCPAllocateIp(dhcp, DHCPStringToIp("192.188.1.1"), &new_ip);
    DHCPAllocateIp(dhcp, DHCPStringToIp("192.188.1.1"), &new_ip2);

    size_before = DHCPCountFree(dhcp);

    DHCPFreeIp(dhcp, new_ip);

    size_after = DHCPCountFree(dhcp);

    if (1 == size_after - size_before)
    {
        printf("DHCPFreeIp working!                                  V\n");
    }
    else
    {
        printf("DHCPFreeIp NOT working!                              X\n");
    }
    DHCPDestroy(dhcp);
}