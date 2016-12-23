/**
 * @file     zndkmq_tx.c
 * @brief    POSIX Message Queue test programme (tx)
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

#include "zndkmq.h"             /* zndkmq header */

/**
 * main()
 * @brief    main routine for mq tx
 *
 * @param    [in]   argc        int ::= # of args
 * @param    [in]  *argv[]     char ::= entity of args
 * @return          stat            ::= process termination (EXIT_)
 */
int
main(int argc, char *argv[])
{
    int     stat   = EXIT_SUCCESS;
    mqd_t   mq;
    int     is_run = TRUE;
    char    wbuf[LEN_ZNDKMQ_BUF];

    mq   =  mq_open(NAME_ZNDKMQ, O_WRONLY);
    if (mq == (mqd_t)-1) {
        perror(" mq_open() error " NAME_ZNDKMQ);
        printf(" %s():[L%4d]: mq_open() error (%d)\n", __func__, __LINE__, (int)mq);
        stat = EXIT_FAILURE;
        goto  err_main;
    }

    /* starts client function */
    printf("===== ZNDKMQ: client start =====\n");
    printf(" type q for QUIT\n");
    while (is_run == TRUE) {
        printf(" ZNDKMQ> ");    /* prompt */

        /* wait for stdin */
        fflush(stdout);
        memset(wbuf, 0, sizeof(wbuf));
        fgets(wbuf, LEN_ZNDKMQ_BUF, stdin);

        stat = mq_send(mq, wbuf, strlen(wbuf), 0);
        if (stat < 0) {
            perror(" mq_send() error " NAME_ZNDKMQ);
            printf(" %s():[L%4d]: mq_send() error (%d)\n", __func__, __LINE__, stat);
            stat = EXIT_FAILURE;
            goto   err_main;
        }

        if (strncmp(wbuf, "q", 1) == 0) { /* cmd: q ? */
            is_run = FALSE;               /*  QUIT    */
            printf(" quit\n");
        }
    }
    printf("===== ZNDKMQ: client end   =====\n");

    mq   =  mq_close(mq);
    if (mq == (mqd_t)-1) {
        perror(" mq_close() error " NAME_ZNDKMQ);
        printf(" %s():[L%4d]: mq_close() error (%d)\n", __func__, __LINE__, (int)mq);
        stat = EXIT_FAILURE;
        goto  err_main;
    }

 err_main:

    return  stat;
}

/* end */
