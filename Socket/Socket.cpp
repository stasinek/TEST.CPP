//---------------------------------------------------------------------------

#pragma hdrstop


#include <winsock2.h>
//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{


WSADATA wsaData;

int result = WSAStartup( MAKEWORD( 2, 2 ), & wsaData );
if( result != NO_ERROR )
     printf( "Initialization error.\n" );


     SOCKET mainSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
if( mainSocket == INVALID_SOCKET )
{
    printf( "Error creating socket: %ld\n", WSAGetLastError() );
    WSACleanup();
    return 1;
}

sockaddr_in service;
memset( & service, 0, sizeof( service ) );
service.sin_family = AF_INET;
service.sin_addr.s_addr = inet_addr( "127.0.0.1" );
service.sin_port = htons( 27015 );


if( bind( mainSocket,( SOCKADDR * ) & service, sizeof( service ) ) == SOCKET_ERROR )
{
    printf( "bind() failed.\n" );
    closesocket( mainSocket );
    return 1;
}

if( listen( mainSocket, 1 ) == SOCKET_ERROR )
     printf( "Error listening on socket.\n" );

     SOCKET acceptSocket = SOCKET_ERROR;
printf( "Waiting for a client to connect...\n" );

while( acceptSocket == SOCKET_ERROR )
{
    acceptSocket = accept( mainSocket, NULL, NULL );
}

printf( "Client connected.\n" );
mainSocket = acceptSocket;


int bytesSent;
int bytesRecv = SOCKET_ERROR;
char sendbuf[ 32 ] = "Client says hello!";
char recvbuf[ 32 ] = "";

bytesSent = send( mainSocket, sendbuf, strlen( sendbuf ), 0 );
printf( "Bytes sent: %ld\n", bytesSent );

while( bytesRecv == SOCKET_ERROR )
{
    bytesRecv = recv( mainSocket, recvbuf, 32, 0 );
    
    if( bytesRecv == 0 || bytesRecv == WSAECONNRESET )
    {
        printf( "Connection closed.\n" );
        break;
    }
    
    if( bytesRecv < 0 )
         return 1;
    
    printf( "Bytes received: %ld\n", bytesRecv );
    printf( "Received text: %s\n", recvbuf );
}

system( "pause" );

        return 0;
}
//---------------------------------------------------------------------------


__stdcall con () {

if( connect( mainSocket,( SOCKADDR * ) & service, sizeof( service ) ) == SOCKET_ERROR )
{
    printf( "Failed to connect.\n" );
    WSACleanup();
    return 1;
}

}

__stdcall sen() {
int bytesSent;
int bytesRecv = SOCKET_ERROR;
char sendbuf[ 32 ] = "Server says hello!";
char recvbuf[ 32 ] = "";

bytesRecv = recv( mainSocket, recvbuf, 32, 0 );
printf( "Bytes received: %ld\n", bytesRecv );
printf( "Received text: %s\n", recvbuf );

bytesSent = send( mainSocket, sendbuf, strlen( sendbuf ), 0 );
printf( "Bytes sent: %ld\n", bytesSent );

system( "pause" );

}