/**
 * src/server.c - wiibrew-js
 * Copyright (C) 2016 Karim Alibhai.
 */

#include "server.h"

static lwp_t server_handle = (lwp_t) NULL;
static char SERVER_IP[16] = {0};

/**
 * Spins off a new thread to handle the server.
 */
void server_init() {
	LWP_CreateThread( &server_handle,   /* thread handle */ 
                      server_run,		/* code */ 
                      SERVER_IP,	    /* arg pointer for thread */
                      NULL,		    	/* stack base */ 
                      16*1024,	    	/* stack size */
                      50        	    /* thread priority */ );
}

/**
 * Prepares and runs the server.
 */
void *server_run(void* arg) {
    int erno;

    double size;
    char sizebuffer[ 8 ];

    s32 _server;
    s32 _socket;

    struct sockaddr_in client;
	struct sockaddr_in server;

    u32	clientlen = sizeof( client );

    char gateway[16] = {0};
	char netmask[16] = {0};

    printf("Hello, world.\n");

    if ( (erno = if_config ( SERVER_IP, netmask, gateway, TRUE)) < 0 ) {
        printf( "Error: failed to initialize network. (%d)\n", erno );
        return NULL;
    }

    printf( "Your IP address is: %s\n", SERVER_IP );

    if ( (_server = net_socket( AF_INET, SOCK_STREAM, IPPROTO_IP )) == INVALID_SOCKET ) {
        printf( "Error: Failed to create socket.\n" );
        return NULL;
    }

    // create socket binding
    memset( &server, 0, sizeof(server) );
	memset( &client, 0, sizeof(client) );

	server.sin_family = AF_INET;
	server.sin_port = htons (1024);
	server.sin_addr.s_addr = INADDR_ANY;

    // bind the socket
	if (( erno = net_bind( _server, (struct sockaddr *) &server, sizeof(server) ) )) {
        printf( "Error: Failed to bind socket (%d).\n", erno );
        return NULL;
    }

    // start listening on port
    if (( erno = net_listen( _server, 5 ) )) {
        printf( "Error: Failed to start socket listening (%d).\n", erno );
        return NULL;
    }

    // await the remote client
    if ( (_socket = net_accept( _server, (struct sockaddr *) &client, &clientlen )) < 0 ) {
        printf( "Error: Failed to receive client connection. (%d)\n", _socket );
        return NULL;
    }

    // converse with the client
    while ( TRUE ) {
        // first we receive the size of the incoming packet
        memset( sizebuffer, 0, 8 );
        if ( net_recv( _socket, sizebuffer, 8, 0 ) != 8 ) {
            printf( "Error: Expected to read 8 bytes." );
            break;
        }
        memcpy( &size, sizebuffer, 8 );

        // ...
        printf("Preparing to read %f bytes ...\n", size);
    }

    return NULL;
}