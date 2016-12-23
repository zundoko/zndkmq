#
# @file     Makefile
# @brief    Makefile for mq test (POSIX Message Queue)
#
# @note     https://github.com/zundoko/zndkmq
#
# @date     2016-12-23
# @authr    zundoko
#

PRJNAME =   zndkmq

TARGETS = $(PRJNAME)_server $(PRJNAME)_client
SRCS    = $(TARGETS:%=%.c)
OBJS    = $(SRCS:%.c=%.o)
DEPEND  =   Makefile.depend

CC      = $(CROSS_COMPILE)gcc
INC     =  -I.
CFLAGS  = $(INC) -c -Wall -Werror
LDFLAGS = 
LIBS    = -lrt

.PHONY: all
all: $(TARGETS)

.PHONY: $(TARGETS)
$(TARGETS): %:%.o
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $<

.PHONY: clean
clean:
	-rm -rf $(OBJS) $(TARGETS) *~

.PHONY: depend
depend:
	-rm -rf $(DEPEND)
	$(CC) -MM -MG $(CFLAGS) $(SRCS) > $(DEPEND)

-include  $(DEPEND)

# end
