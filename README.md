# Simple communication with Sockets

Simple communication with socket, using the c programming language, following the model client-server.

## Sockets in C

### Stages for server

#### Socket creation

```
int sockfd = socket(domain, type, protocol);
```

*sockfd:* socket descriptor, an integer (like a le-handle)
*domain:* integer, communication domain e.g., AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol)
*type:* communication type
        SOCK_STREAM: TCP(reliable, connection oriented)
        SOCK_DGRAM: UDP(unreliable, connectionless)
*protocol:* Protocol value for Internet Protocol(IP), which is 0. This is the same number which appears on protocol eld in
the IP header of a packet.(man protocols for more details)

#### Setsockopt

```
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
```

This helps in manipulating options for the socket referred by the le descriptor sockfd.
This is completely optional, but it helps in reuse of address and port. Prevents error such as: “address already in use”.

#### Bind

```
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

After creation of the socket, bind function binds the socket to the address and port number speci ed in addr(custom datastructure).
In the example code, we bind the server to the localhost, hence we use INADDR_ANY to specify the IP address.

#### Listen

```
int listen(int sockfd, int backlog);
```

It puts the server socket in a passive mode, where it waits for the client to approach the server to make a connection.
The backlog, de nes the maximum length to which the queue of pending connections for sockfd may grow.
If a connection request arrives when the queue is full, the client may receive an error with an indication of ECONNREFUSED.

#### Accept

```
int new_socket= accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

It extracts the rst connection request on the queue of pending connections for the listening socket, sockfd, creates a
new connected socket, and returns a new le descriptor referring to that socket. At this point, connection is established
between client and server, and they are ready to transfer data.

### Stages for client

### Socket connection

Exactly same as that of server’s socket creation.


### Connect

```
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

The connect() system call connects the socket referred to by the le descriptor sockfd to the address speci ed by addr.
Server’s address and port is speci ed in addr.
