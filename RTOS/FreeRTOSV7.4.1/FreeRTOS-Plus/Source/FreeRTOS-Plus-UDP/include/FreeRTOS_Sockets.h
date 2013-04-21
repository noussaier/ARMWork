/*
 * FreeRTOS+UDP V1.0.0 (C) 2013 Real Time Engineers ltd.
 *
 * FreeRTOS+UDP is an add-on component to FreeRTOS.  It is not, in itself, part
 * of the FreeRTOS kernel.  FreeRTOS+UDP is licensed separately from FreeRTOS,
 * and uses a different license to FreeRTOS.  FreeRTOS+UDP uses a dual license
 * model, information on which is provided below:
 *
 * - Open source licensing -
 * FreeRTOS+UDP is a free download and may be used, modified and distributed
 * without charge provided the user adheres to version two of the GNU General
 * Public license (GPL) and does not remove the copyright notice or this text.
 * The GPL V2 text is available on the gnu.org web site, and on the following
 * URL: http://www.FreeRTOS.org/gpl-2.0.txt
 *
 * - Commercial licensing -
 * Businesses and individuals who wish to incorporate FreeRTOS+UDP into
 * proprietary software for redistribution in any form must first obtain a
 * (very) low cost commercial license - and in-so-doing support the maintenance,
 * support and further development of the FreeRTOS+UDP product.  Commercial
 * licenses can be obtained from http://shop.freertos.org and do not require any
 * source files to be changed.
 *
 * FreeRTOS+UDP is distributed in the hope that it will be useful.  You cannot
 * use FreeRTOS+UDP unless you agree that you use the software 'as is'.
 * FreeRTOS+UDP is provided WITHOUT ANY WARRANTY; without even the implied
 * warranties of NON-INFRINGEMENT, MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. Real Time Engineers Ltd. disclaims all conditions and terms, be they
 * implied, expressed, or statutory.
 *
 * 1 tab == 4 spaces!
 *
 * http://www.FreeRTOS.org
 * http://www.FreeRTOS.org/udp
 *
 */

#ifndef FREERTOS_UDP_H
#define FREERTOS_UDP_H

/* Standard includes. */
#include <string.h>

/* Application level configuration options. */
#include "FreeRTOSIPConfig.h"

#ifndef INC_FREERTOS_H
	#error FreeRTOS.h must be included before FreeRTOS_Sockets.h.
#endif

#ifndef TASK_H
	#error The FreeRTOS header file task.h must be included before FreeRTOS_Sockets.h.
#endif

/* Assigned to an xSocket_t variable when the socket is not valid, probably
because it could not be created. */
#define FREERTOS_INVALID_SOCKET	( ( void * ) ~0U )

/* API function error values.  As errno is supported, the FreeRTOS sockets
functions return error codes rather than just a pass or fail indication. */
#define FREERTOS_SOCKET_ERROR	( -1 )
#define FREERTOS_EWOULDBLOCK	( -2 )
#define FREERTOS_EINVAL			( -4 )
#define FREERTOS_EADDRNOTAVAIL	( -5 )
#define FREERTOS_EADDRINUSE		( -6 )
#define FREERTOS_ENOBUFS		( -7 )
#define FREERTOS_ENOPROTOOPT	( -8 )

/* Values for the parameters to FreeRTOS_socket(), inline with the Berkeley
standard.  See the documentation of FreeRTOS_socket() for more information. */
#define FREERTOS_AF_INET		( 2 )
#define FREERTOS_SOCK_DGRAM		( 2 )
#define FREERTOS_IPPROTO_UDP	( 17 )

/* A bit value that can be passed into the FreeRTOS_sendto() function as part of
the flags parameter.  Setting the FREERTOS_ZERO_COPY in the flags parameter
indicates that the zero copy interface is being used.  See the documentation for
FreeRTOS_sockets() for more information. */
#define FREERTOS_ZERO_COPY		( 0x01UL )

/* Values that can be passed in the option name parameter of calls to
FreeRTOS_setsockopt(). */
#define FREERTOS_SO_RCVTIMEO		( 0 )		/* Used to set the receive time out. */
#define FREERTOS_SO_SNDTIMEO		( 1 )		/* Used to set the send time out. */
#define FREERTOS_SO_UDPCKSUM_OUT	( 0x02 ) 	/* Used to turn the use of the UDP checksum by a socket on or off.  This also doubles as part of an 8-bit bitwise socket option. */
#define FREERTOS_NOT_LAST_IN_FRAGMENTED_PACKET 	( 0x80 )  /* For internal use only, but also part of an 8-bit bitwise value. */
#define FREERTOS_FRAGMENTED_PACKET				( 0x40 )  /* For internal use only, but also part of an 8-bit bitwise value. */

/* For compatibility with the expected Berkeley sockets naming. */
#define socklen_t uint32_t

/* For this limited implementation, only two members are required in the
Berkeley style sockaddr structure. */
struct freertos_sockaddr
{
	uint16_t sin_port;
	uint32_t sin_addr;
};

#if ipconfigBYTE_ORDER == FREERTOS_LITTLE_ENDIAN

	#define FreeRTOS_inet_addr_quick( ucOctet0, ucOctet1, ucOctet2, ucOctet3 )				\
										( ( ( uint32_t ) ( ucOctet3 ) ) << 24UL ) |			\
										( ( ( uint32_t ) ( ucOctet2 ) ) << 16UL ) |			\
										( ( ( uint32_t ) ( ucOctet1 ) ) <<  8UL ) |			\
										( ( uint32_t ) ( ucOctet0 ) )

	#define FreeRTOS_inet_ntoa( ulIPAddress, pucBuffer )									\
										sprintf( ( char * ) ( pucBuffer ), "%d.%d.%d.%d",	\
											( ( ulIPAddress ) & 0xffUL ),					\
											( ( ( ulIPAddress ) >> 8UL ) & 0xffUL ),		\
											( ( ( ulIPAddress ) >> 16UL ) & 0xffUL ),		\
											( ( ( ulIPAddress ) >> 24UL ) & 0xffUL ) )

#else /* ipconfigBYTE_ORDER */

	#define FreeRTOS_inet_addr_quick( ucOctet0, ucOctet1, ucOctet2, ucOctet3 )				\
										( ( ( uint32_t ) ( ucOctet0 ) ) << 24UL ) |			\
										( ( ( uint32_t ) ( ucOctet1 ) ) << 16UL ) |			\
										( ( ( uint32_t ) ( ucOctet2 ) ) <<  8UL ) |			\
										( ( uint32_t ) ( ucOctet3 ) )

	#define FreeRTOS_inet_ntoa( ulIPAddress, pucBuffer )									\
										sprintf( ( char * ) ( pucBuffer ), "%d.%d.%d.%d",	\
											( ( ( ulIPAddress ) >> 24UL ) & 0xffUL ) ),		\
											( ( ( ulIPAddress ) >> 16UL ) & 0xffUL ),		\
											( ( ( ulIPAddress ) >> 8UL ) & 0xffUL ),		\
											( ( ulIPAddress ) & 0xffUL )

#endif /* ipconfigBYTE_ORDER */

/* The socket type itself. */
typedef void *xSocket_t;

/* The xSocketSet_t type is the equivalent to the fd_set type used by the 
Berkeley API. */
typedef void *xSocketSet_t;

/**
 * FULL, UP-TO-DATE AND MAINTAINED REFERENCE DOCUMENTATION FOR ALL THESE
 * FUNCTIONS IS AVAILABLE ON THE FOLLOWING URL:
 * http://www.FreeRTOS.org/FreeRTOS-Plus/FreeRTOS_Plus_UDP/FreeRTOS_UDP_API_Functions.shtml
 */
xSocket_t FreeRTOS_socket( portBASE_TYPE xDomain, portBASE_TYPE xType, portBASE_TYPE xProtocol );
int32_t FreeRTOS_recvfrom( xSocket_t xSocket, void *pvBuffer, size_t xBufferLength, uint32_t ulFlags, struct freertos_sockaddr *pxSourceAddress, socklen_t *pxSourceAddressLength );
int32_t FreeRTOS_sendto( xSocket_t xSocket, const void *pvBuffer, size_t xTotalDataLength, uint32_t ulFlags, const struct freertos_sockaddr *pxDestinationAddress, socklen_t xDestinationAddressLength );
portBASE_TYPE FreeRTOS_bind( xSocket_t xSocket, struct freertos_sockaddr *pxAddress, socklen_t xAddressLength );
portBASE_TYPE FreeRTOS_setsockopt( xSocket_t xSocket, int32_t lLevel, int32_t lOptionName, const void *pvOptionValue, size_t xOptionLength );
portBASE_TYPE FreeRTOS_closesocket( xSocket_t xSocket );
uint32_t FreeRTOS_gethostbyname( const uint8_t *pcHostName );
uint32_t FreeRTOS_inet_addr( const uint8_t * pucIPAddress );

#if ipconfigSUPPORT_SELECT_FUNCTION == 1
	xSocketSet_t FreeRTOS_CreateSocketSet( unsigned portBASE_TYPE uxEventQueueLength );
	portBASE_TYPE FreeRTOS_FD_SET( xSocket_t xSocket, xSocketSet_t xSocketSet );
	portBASE_TYPE FreeRTOS_FD_CLR( xSocket_t xSocket, xSocketSet_t xSocketSet );
	xSocket_t FreeRTOS_select( xSocketSet_t xSocketSet, portTickType xBlockTimeTicks );
#endif /* ipconfigSUPPORT_SELECT_FUNCTION */

#endif /* FREERTOS_UDP_H */













