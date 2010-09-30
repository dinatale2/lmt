/*****************************************************************************
 *  Copyright (C) 2010 Lawrence Livermore National Security, LLC.
 *  This module written by Jim Garlick <garlick@llnl.gov>
 *  UCRL-CODE-232438
 *  All Rights Reserved.
 *
 *  This file is part of Lustre Monitoring Tool, version 2.
 *  Authors: H. Wartens, P. Spencer, N. O'Neill, J. Long, J. Garlick
 *  For details, see http://code.google.com/p/lmt/.
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License (as published by the
 *  Free Software Foundation) version 2, dated June 1991.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the IMPLIED WARRANTY OF MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE. See the terms and conditions of the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA or see
 *  <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#if HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#if HAVE_GETOPT_H
#include <getopt.h>
#endif
#include <libgen.h>

#include "list.h"
#include "hash.h"
#include "error.h"

#include "util.h"

#include "lmtconf.h"

#include "lmtmysql.h"

#define OPTIONS "a:d:lc:s:u:p:"
#if HAVE_GETOPT_LONG
#define GETOPT(ac,av,opt,lopt) getopt_long (ac,av,opt,lopt,NULL)
static const struct option longopts[] = {
    {"add",             required_argument,  0, 'a'},
    {"delete",          required_argument,  0, 'd'},
    {"list",            no_argument,        0, 'l'},
    {"config-file",     required_argument,  0, 'c'},
    {"schema-file",     required_argument,  0, 's'},
    {"user",            required_argument,  0, 'u'},
    {"password",        required_argument,  0, 'p'},
    {0, 0, 0, 0},
};
#else
#define GETOPT(ac,av,opt,lopt) getopt (ac,av,opt)
#endif

static void list (char *user, char *password);
static void del (char *user, char *password, char *fsname);
static void add (char *user, char *password, char *fsname, char *schemafile);


static void
usage(void)
{
    char *u = lmt_conf_get_db_rwuser ();
    char *p = lmt_conf_get_db_rwpasswd ();

    fprintf (stderr, "Usage: lmtinit [OPTIONS]\n"
        "  -a,--add FS            create database for file system\n"
        "  -d,--delete FS         remove database for file system\n"
        "  -l,--list              list file systems in database\n"
        "  -c,--config-file FILE  use an alternate config file\n"
        "  -s,--schema-file FILE  use an alternate schema file\n"
        "  -u,--user=USER         connect to the db with USER (default: %s)\n"
        "  -p,--password=PASS     connect to the db with PASS (default: %s)\n",
        u ? u : "<nil>", p ? p : "<nil>"
    );
    exit (1);
}

int
main (int argc, char *argv[])
{
    int c;
    int aopt = 0;
    int dopt = 0;
    int lopt = 0;
    char *fsname = NULL;
    char *conffile = NULL;
    char *schemafile = NULL;
    char *user = NULL;
    char *pass = NULL;

    err_init (argv[0]);
    optind = 0;
    opterr = 0;
    while ((c = GETOPT (argc, argv, OPTIONS, longopts)) != -1) {
        switch (c) {
            case 'a':   /* --add FS */
                aopt = 1;
                fsname = optarg;
                break;
            case 'd':   /* --delete FS */
                dopt = 1;
                fsname = optarg;
                break;
            case 'l':   /* --list */
                lopt = 1;
                break;
            case 'c':   /* --config-file FILE */
                conffile = optarg;
                break;
            case 's':   /* --schema-file FILE */
                schemafile = optarg;
                break;
            case 'u':   /* --user USER */
                user = optarg;
                break;
            case 'p':   /* --password PASS */
                pass = optarg;
                break;
            default:
                usage ();
        }
    }
    if (lmt_conf_init (1, conffile) < 0)
        exit (1);
    lmt_conf_set_db_debug (1);
    if (optind < argc)
        usage ();
    if (!aopt && !dopt && !lopt)
        usage ();
    if (aopt + dopt + lopt > 1)
        msg_exit ("Use only one of -a, -d, and -l options.");

    if (lopt) {
        if (!user)
            user = lmt_conf_get_db_rouser ();
        if (!pass)
            user = lmt_conf_get_db_rouser ();
    } else {
        if (!user)
            user = lmt_conf_get_db_rwuser ();
        if (!pass)
            user = lmt_conf_get_db_rwuser ();
    }

    if (lopt)
        list (user, pass);
    else if (dopt)
        del (user, pass, fsname);
    else if (aopt)
        add (user, pass, fsname, schemafile);

    exit (0);
}

static void
list (char *user, char *pass)
{
    List l;
    ListIterator itr;
    char *s, *p;

    if (lmt_db_list (user, pass, &l) < 0)
        return;
    itr = list_iterator_create (l);
    while ((s = list_next (itr))) {
        p = strchr (s, '_');
        msg ("%s", p ? p + 1 : s);
    }
    list_iterator_destroy (itr);
}

static void
del (char *user, char *pass, char *fsname)
{
}

static void
add (char *user, char *pass, char *fsname, char *schemafile)
{
}

/*
 * vi:tabstop=4 shiftwidth=4 expandtab
 */
