/******************************************************************************
 *
 * Copyright (c) 2009 Citrix Systems, Inc. (Grzegorz Milos)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <pthread.h>
#include <inttypes.h>
#include <unistd.h>

#include "bidir-hash.h"
#include "memshr-priv.h"

static struct blockshr_hash *blks_hash;

void* bidir_daemon(void *unused)
{
    uint32_t nr_ent, max_nr_ent, tab_size, max_load, min_load;
    static uint64_t shrhnd = 1;

    while(1)
    {
        blockshr_hash_sizes( blks_hash, 
                            &nr_ent, 
                            &max_nr_ent,
                            &tab_size, 
                            &max_load, 
                            &min_load);
        /* Remove some hints as soon as we get to 90% capacity */ 
        if(10 * nr_ent > 9 * max_nr_ent)
        {
            uint64_t next_remove = shrhnd;
            int to_remove;
            int ret;

            to_remove = 0.1 * max_nr_ent; 
            while(to_remove > 0) 
            {
                ret = blockshr_shrhnd_remove(blks_hash, next_remove, NULL);
                if(ret < 0)
                {
                    /* We failed to remove an entry, because of a serious hash
                     * table error */
                    DPRINTF("Could not remove handle %"PRId64", error: %d\n",
                            next_remove, ret);
                    /* Force to exit the loop early */
                    to_remove = 0;
                } else 
                if(ret > 0)
                {
                    /* Managed to remove the entry. Note next_remove not
                     * incremented, in case there are duplicates */
                    shrhnd = next_remove;
                    to_remove--;
                } else
                {
                    /* Failed to remove, because there is no such handle */
                    next_remove++;
                }
            }
        }

        sleep(1);
    }
}

void bidir_daemon_launch(void)
{
    pthread_t thread; 

    pthread_create(&thread, NULL, bidir_daemon, NULL);
}

void bidir_daemon_initialize(struct blockshr_hash *blks)
{
    blks_hash = blks; 
    bidir_daemon_launch();
}
