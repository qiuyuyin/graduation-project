#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sstream>
#include <unistd.h>
#include <termios.h>

#include "common/defs.h"
#include "common/lang/string.h"

#ifdef USE_READLINE
#include "readline/readline.h"
#endif

#define MAX_MEM_BUFFER_SIZE 8192
#define PORT_DEFAULT 6788

using namespace common;

#ifdef USE_READLINE
char *my_readline(const char *prompt)
{
  return readline(prompt);
}
#else   // USE_READLINE
char *my_readline(const char *prompt)
{
  char *buffer = (char *)malloc(MAX_MEM_BUFFER_SIZE);
  if (nullptr == buffer) {
    fprintf(stderr, "failed to alloc line buffer");
    return nullptr;
  }
  fprintf(stdout, prompt);
  char *s = fgets(buffer, MAX_MEM_BUFFER_SIZE, stdin);
  if (nullptr == s) {
    fprintf(stderr, "failed to read message from console");
    free(buffer);
    return nullptr;
  }
  return buffer;
}
#endif  // USE_READLINE

/* this function config a exit-cmd list, strncasecmp func truncate the command from terminal according to the number,
   'strncasecmp("exit", cmd, 4)' means that obclient read command string from terminal, truncate it to 4 chars from
   the beginning, then compare the result with 'exit', if they match, exit the obclient.
*/
bool is_exit_command(const char *cmd)
{
  return 0 == strncasecmp("exit", cmd, 4) || 0 == strncasecmp("bye", cmd, 3) || 0 == strncasecmp("\\q", cmd, 2);
}

int init_unix_sock(const char *unix_sock_path)
{
  int sockfd = socket(PF_UNIX, SOCK_STREAM, 0);
  if (sockfd < 0) {
    fprintf(stderr, "failed to create unix socket. %s", strerror(errno));
    return -1;
  }

  struct sockaddr_un sockaddr;
  memset(&sockaddr, 0, sizeof(sockaddr));
  sockaddr.sun_family = PF_UNIX;
  snprintf(sockaddr.sun_path, sizeof(sockaddr.sun_path), "%s", unix_sock_path);

  if (connect(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0) {
    fprintf(stderr, "failed to connect to server. unix socket path '%s'. error %s", sockaddr.sun_path, strerror(errno));
    close(sockfd);
    return -1;
  }
  return sockfd;
}

int init_tcp_sock(const char *server_host, int server_port)
{
  struct hostent *host;
  struct sockaddr_in serv_addr;

  if ((host = gethostbyname(server_host)) == NULL) {
    fprintf(stderr, "gethostbyname failed. errmsg=%d:%s\n", errno, strerror(errno));
    return -1;
  }

  int sockfd;
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    fprintf(stderr, "create socket error. errmsg=%d:%s\n", errno, strerror(errno));
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(server_port);
  serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
  bzero(&(serv_addr.sin_zero), 8);

  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1) {
    fprintf(stderr, "Failed to connect. errmsg=%d:%s\n", errno, strerror(errno));
    close(sockfd);
    return -1;
  }
  return sockfd;
}

int send_msg(const char *input_command, int sockfd, int send_bytes)
{
  char send_buf[MAX_MEM_BUFFER_SIZE];

  if ((send_bytes = write(sockfd, input_command, strlen(input_command) + 1)) == -1) {
    fprintf(stderr, "send error: %d:%s \n", errno, strerror(errno));
    exit(1);
  }
  memset(send_buf, 0, sizeof(send_buf));

  int len = 0;
  while ((len = recv(sockfd, send_buf, MAX_MEM_BUFFER_SIZE, 0)) > 0) {
    bool msg_end = false;
    for (int i = 0; i < len; i++) {
      if (0 == send_buf[i]) {
        msg_end = true;
        break;
      }
      printf("%c", send_buf[i]);
    }
    if (msg_end) {
      break;
    }
    memset(send_buf, 0, MAX_MEM_BUFFER_SIZE);
  }
  return 0;
}

int main(int argc, char *argv[])
{
  const char *unix_socket_path = nullptr;
  const char *server_host = "127.0.0.1";
  int server_port = PORT_DEFAULT;
  int opt;
  extern char *optarg;
  while ((opt = getopt(argc, argv, "s:h:p:")) > 0) {
    switch (opt) {
      case 's':
        unix_socket_path = optarg;
        break;
      case 'p':
        server_port = atoi(optarg);
        break;
      case 'h':
        server_host = optarg;
        break;
    }
  }

  int sockfd, send_bytes;

  if (unix_socket_path != nullptr) {
    sockfd = init_unix_sock(unix_socket_path);
  } else {
    sockfd = init_tcp_sock(server_host, server_port);
  }
  if (sockfd < 0) {
    return 1;
  }
  for (int i = 1050; i < 2000; i++) {
    char buffer[200];
    std::sprintf(buffer, "insert into student values (%d,'%s-%d','%s',%d);", i, "yili", i - 1000, "2002-07-01", 20);
    std::string sql = buffer;
    send_msg(sql.c_str(), sockfd, send_bytes);
  }
  close(sockfd);

  return 0;
}
