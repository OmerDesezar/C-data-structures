/*
	team: OL125-126
	version: 1.0

*/

#ifndef _DHCP_H_
#define _DHCP_H_

#include <stddef.h> /* size_t */
#include <stdint.h>

typedef struct dhcp dhcp_t;

/* DESCRIPTION:
 * Function creates an empty dhcp
 *
 * PARAMS:
 * subnet_ID
 * subnet length
 *
 * RETURN:
 * Returns a pointer to the created dhcp
 *
 * COMPLEXITY:
 * time:  O(1)
 * space: O(1)
 */
dhcp_t *DHCPCreate(uint32_t subnet_ID, size_t subnet_length);

/* DESCRIPTION:
 * if requested ip is not avialable returns smallest avialable bigger ip.
 * if requested ip is 0 returns smallest avialable.
 *
 * PARAMS:
 * dhcp - pointer to the required dhcp to allocate IP from
 * requested_ip - preferred ip address
 * result_ip - pointer to memory location to store new ip in
 *
 * RETURN:
 * status
 *
 * COMPLEXITY:
 * time: O(log n)
 * space: O(1)
 */

void DHCPDestroy(dhcp_t *dhcp);

int DHCPAllocateIp(dhcp_t *dhcp, uint32_t requested_ip, uint32_t *result_ip);

/* DESCRIPTION:
 * Function free the given IP from the given dhcp.
 *
 * PARAMS:
 * ip - ip the free.
 * dhcp - dhcp to free ip from.
 *
 * RETURN:
 * void
 *
 * COMPLEXITY:
 * time: O(log n)
 * space: O(1)
 */
void DHCPFreeIp(dhcp_t *dhcp, uint32_t ip);

/* DESCRIPTION:
 * Function counts free IPs available for allocation.
 *
 * PARAMS:
 * dhcp	  - dhcp to count free IPs.
 *
 * RETURN:
 * number of free IPs to allocate.
 *
 * COMPLEXITY:
 * time:  O(n)
 * space: O(1)
 */
size_t DHCPCountFree(dhcp_t *dhcp);

char *DHCPIpToString(uint32_t ip, char *dest_ip);

uint32_t DHCPStringToIp(char *ip);

#endif /* _DHCP_H_ */
