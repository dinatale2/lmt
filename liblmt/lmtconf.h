/*****************************************************************************
 *  Copyright (C) 2007-2010 Lawrence Livermore National Security, LLC.
 *  This module written by Jim Garlick <garlick@llnl.gov>.
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

int lmt_conf_init (int vopt, char *path);

char *lmt_conf_get_ro_dbuser (void);
int   lmt_conf_set_ro_dbuser (char *s);

char *lmt_conf_get_ro_dbpasswd (void);
int   lmt_conf_set_ro_dbpasswd (char *s);

char *lmt_conf_get_rw_dbuser (void);
int   lmt_conf_set_rw_dbuser (char *s);

char *lmt_conf_get_rw_dbpasswd (void);
int   lmt_conf_set_rw_dbpasswd (char *s);

char *lmt_conf_get_dbhost (void);
int   lmt_conf_set_dbhost (char *s);

int   lmt_conf_get_dbport (void);
void  lmt_conf_set_dbport (int i);

int   lmt_conf_get_debug (void);
void  lmt_conf_set_debug (int i);

/*
 * vi:tabstop=4 shiftwidth=4 expandtab
 */
