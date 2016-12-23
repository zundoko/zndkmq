/**
 * @file     zndkmq_rx.c
 * @brief    POSIX Message Queue test programme (rx)
 *
 * @note
 *
 * @date     2016-12-23
 * @author   zundoko
 */

#include <stdio.h>              /* printf()      */
#include <stdlib.h>             /* EXIT_SUCCESS  */
#include <string.h>             /* memset()      */
#include <mqueue.h>             /* mq_<foo>      */
#include <errno.h>              /* errno         */

#include "zndkmq.h"             /* zndkmq header */

/**
 * @struct TZndkMqInfo
 * @brief  POSIX Message Queue Info
 */
typedef struct {
    mqd_t           mq;                   /* MQ descriptor */
    struct mq_attr  attr;                 /* MQ attributes */
    char            rbuf[LEN_ZNDKMQ_BUF]; /* MQ rx buffer  */
} TZndkMqInfo;
static       TZndkMqInfo       ZndkMq;
#define _get_zndkmq_info()   (&ZndkMq)

/**
 * main()
 * @brief    main routine for mq rx
 *
 * @param    [in]   argc        int ::= # of args
 * @param    [in]  *argv[]     char ::= entity of args
 * @return          stat            ::= process termination (EXIT_)
 */
int
_init_zndkmq_info(TZndkMqInfo *info)
{
    int             stat = 0;
    struct mq_attr *attr = &info->attr;

    memset(info, 0, sizeof(TZndkMqInfo));

    /* MQ attributes */
    attr->mq_flags   = 0;       /* 0:blocking mode */
    attr->mq_maxmsg  = N_ZNDKMQ_MSGS;
    attr->mq_msgsize = LEN_ZNDKMQ_BUF;
    attr->mq_curmsgs = 0;       /* 0:reset msg cnt */

    return  stat;
}

/**
 * main()
 * @brief    main routine for mq rx
 *
 * @param    [in]   argc        int ::= # of args
 * @param    [in]  *argv[]     char ::= entity of args
 * @return          stat            ::= process termination (EXIT_)
 */
int
main(int argc, char *argv[])
{
    int             stat   =  EXIT_SUCCESS;
    TZndkMqInfo    *info   = _get_zndkmq_info();
    struct mq_attr *attr;
    mqd_t           mq;
    int             is_run =  TRUE;
    int             nbytes;
    char           *rbuf;

    _init_zndkmq_info(info);
    attr     = &info->attr;

    printf(" attr->mq_flags  : %ld\n", attr->mq_flags  );
    printf(" attr->mq_maxmsg : %ld\n", attr->mq_maxmsg );
    printf(" attr->mq_msgsize: %ld\n", attr->mq_msgsize);
    printf(" attr->mq_curmsgs: %ld\n", attr->mq_curmsgs);

    mq       =  mq_open(NAME_ZNDKMQ, O_RDWR | O_CREAT | O_EXCL, 0644, attr);
    if (mq  == (mqd_t)-1) {
        perror(" mq_open() error " NAME_ZNDKMQ);
        printf(" %s():[L%4d]: mq_open() error (%d)\n", __func__, __LINE__, (int)mq);
        stat = EXIT_FAILURE;
        goto   err_main;
    }
    info->mq = mq;

    /* starts server function */
    printf("===== ZNDKMQ: server start =====\n");
    rbuf     = info->rbuf;
    while (is_run == TRUE) {
        nbytes = mq_receive(mq, rbuf, attr->mq_msgsize, NULL);
        if (nbytes < 0) {
            perror(" mq_receive() error " NAME_ZNDKMQ);
            printf(" %s():[L%4d]: mq_receive() error (%d)\n", __func__, __LINE__, errno);
            stat = EXIT_FAILURE;
            goto   err_main;
        }

        rbuf[nbytes] = '\0';    /* NULL termination */
        printf(" %s():[L%4d]: mq_receive(), nbytes=%d\n", __func__, __LINE__, nbytes);

        if (strncmp(rbuf, "q", 1) == 0) { /* cmd: q ? */
            is_run = FALSE;               /*  QUIT    */
        } else {
            printf(" %s():[L%4d]: mq_receive(), msg=%s\n", __func__, __LINE__, rbuf);
        }
    }
    printf("===== ZNDKMQ: server end   =====\n");

    mq   =  mq_close(mq);
    if (mq == (mqd_t)-1) {
        perror(" mq_close() error " NAME_ZNDKMQ);
        printf(" %s():[L%4d]: mq_close() error (%d)\n", __func__, __LINE__, (int)mq);
        stat = EXIT_FAILURE;
        goto  err_main;
    }

 err_main:
    mq_unlink(NAME_ZNDKMQ);

    return  stat;
}

/* end */
