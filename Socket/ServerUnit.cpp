//---------------------------------------------------------------------------
#include <winsock2.h>
#include <dir.h>
#include <stdio.h>
#include <process.h>
#include "sstsoft_sockets.h"

//---------------------------------------------------------------------------
#pragma argsused

int main(int argc, char* argv[])
{
int i;
char path[MAX_PATH], *argv_s[32];
for (i = 32; --i >= 0;) argv_s[i] = new char[MAX_PATH];
getcwd(path,MAX_PATH);
ts::io32::strcat(path,"\\WWW");
int argc_s   = ts::sockets::http_server(path,"127.0.0.1","80");
//ts::sockets::argv_via_socket_server(argv_s,"127.0.0.1","27014","stasiek","1234567890",300);
if (argc_s==0) ts::sockets::print_s_error();
for (i = 32; --i >= 0;) delete argv_s[i];
return 0;
}
//---------------------------------------------------------------------------

