# zndkmq
POSIX Message Queue test (Server/Client)

Getting Started.
---------------

You must be run _zndkmq_server_ first before run _zndkmq_client_.

term1:
```
$ make
$ ./zndkmq_server
```

term2:
```
$ ./zndkmq_client
```

Operation logs:
---------------
term1:
```
$ make clean
rm -rf zndkmq_server.o zndkmq_client.o zndkmq_server zndkmq_client *~

$ make
gcc -I. -c -Wall -Werror zndkmq_server.c
gcc  -o zndkmq_server zndkmq_server.o -lrt
gcc -I. -c -Wall -Werror zndkmq_client.c
gcc  -o zndkmq_client zndkmq_client.o -lrt

$ ./zndkmq_server 
 attr->mq_flags  : 0
 attr->mq_maxmsg : 10
 attr->mq_msgsize: 1024
 attr->mq_curmsgs: 0
===== ZNDKMQ: server start =====
 main():[L 105]: mq_receive(), nbytes=10
 main():[L 110]: mq_receive(), msg=123456789

 main():[L 105]: mq_receive(), nbytes=1
 main():[L 110]: mq_receive(), msg=

 main():[L 105]: mq_receive(), nbytes=4
 main():[L 110]: mq_receive(), msg=foo

 main():[L 105]: mq_receive(), nbytes=7
 main():[L 110]: mq_receive(), msg=foobar

 main():[L 105]: mq_receive(), nbytes=11
 main():[L 110]: mq_receive(), msg=0123456789

 main():[L 105]: mq_receive(), nbytes=2
 main():[L 110]: mq_receive(), msg=q

===== ZNDKMQ: server end   =====
$
```


term2:
```
$ ./zndkmq_client 
===== ZNDKMQ: client start =====
 type q for QUIT
 ZNDKMQ> 123456789
 ZNDKMQ> 
 ZNDKMQ> foo
 ZNDKMQ> foobar
 ZNDKMQ> 0123456789
 ZNDKMQ> q
 quit
===== ZNDKMQ: client end   =====

```
