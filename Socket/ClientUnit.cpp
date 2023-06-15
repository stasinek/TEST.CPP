//---------------------------------------------------------------------------

#pragma hdrstop


#include <conio.h>
#include <stdio.h>
#include <winsock2.h>
#include <stk_sockets.h>
//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
WSADATA wsaData;
SOCKET mainSocket;
SOCKET acceptSocket;
sockaddr_in service;
int bytesSent;
int bytesRecv = SOCKET_ERROR;
char sendbuf[ 128 ];
char recvbuf[ 128 ];

int result = WSAStartup( MAKEWORD( 2, 2 ), & wsaData );
if( result != NO_ERROR )
{
    stk::socket::print_socket_error();
    WSACleanup();
   goto GOTO_EXIT;
}

mainSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
if( mainSocket == INVALID_SOCKET )
{
    stk::socket::print_socket_error();
    WSACleanup();
   goto GOTO_EXIT;
}

memset( & service, 0, sizeof( service ) );
service.sin_family = AF_INET;
service.sin_addr.s_addr = inet_addr( "127.0.0.1" );
service.sin_port = htons( 27014 );

//----------------------------------------------------

if (connect( mainSocket,( SOCKADDR * ) & service, sizeof( service ) ) == SOCKET_ERROR )
{
    stk::socket::print_socket_error();
    WSACleanup();
    return 1;
}
struct timeval tv;
tv.tv_sec = 300;  /* 30 Secs Timeout */
tv.tv_usec = 0;  // Not init'ing this can cause strange errors
setsockopt(mainSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));


bytesRecv = SOCKET_ERROR;
strcpy(sendbuf,"HELLO");
strcpy(recvbuf,"");
bytesRecv = recv( mainSocket, recvbuf, 128, 0 );
printf( "Server is connected:\n%s\n", recvbuf );
strcpy(sendbuf,"LOGIN:stasiek");
bytesSent = send( mainSocket, sendbuf, strlen( sendbuf ) + 1, 0 );
bytesRecv = recv( mainSocket, recvbuf, 128, 0 );
printf( "Server respond:\n%s\n", recvbuf );
strcpy(sendbuf,"PASSWORD:1234567890");
bytesSent = send( mainSocket, sendbuf, strlen( sendbuf ) + 1, 0 );
bytesRecv = recv( mainSocket, recvbuf, 128, 0 );
printf( "Server respond:\n%s\n", recvbuf );

while(true) {
gets(sendbuf);
bytesSent = send( mainSocket, sendbuf, strlen( sendbuf ) + 1, 0 );
printf( "Sent: %s\n", sendbuf );
bytesRecv = recv( mainSocket, recvbuf, 128, 0 );
printf( "Server respond:\n%s\n", recvbuf );
if (strcmp(sendbuf,"EXIT")==0)
break;
}

getch();
WSACleanup();
return 0;
GOTO_EXIT:
getch();
return 1;
}
//---------------------------------------------------------------------------
