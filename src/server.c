/**
 * src/server.c - wiibrewjs
 * Copyright (C) 2016 Karim Alibhai.
 */

#include "app.h"
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

    int method, size;
    char methodbuffer[ 4 ];
    char sizebuffer[ 4 ];

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

    printf("%d\n", sizeof(int));
    // converse with the client
    while ( TRUE ) {
        // first we receive the method of the incoming packet
        memset( methodbuffer, 0, 4 );
        if ( net_recv( _socket, methodbuffer, 4, 0 ) != 4 ) {
            printf( "Error: Expected to read 4 bytes." );
            break;
        }
        memcpy( &method, methodbuffer, 4 );

        printf("Method: %d\n", method);

        // first we receive the size of the incoming packet
        memset( sizebuffer, 0, 4 );
        if ( net_recv( _socket, sizebuffer, 4, 0 ) != 4 ) {
            printf( "Error: Expected to read 4 bytes." );
            break;
        }
        memcpy( &size, sizebuffer, 4 );

        // ...
        printf("Payload size: %d bytes\n", size);
        char data[size];

        memset( data, 0, size );
        if ( net_recv( _socket, data, size, 0 ) != size ) {
            printf( "Error: Expected to read %d bytes.", size );
            break;
        }

        // ...
        printf("Data: %s\n", data);
        app_data_recv(method, size, &data);
    }

    return NULL;
}
