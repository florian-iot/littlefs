/*
 * Block device emulated in a file
 *
 * Copyright (c) 2022, The littlefs authors.
 * Copyright (c) 2017, Arm Limited. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef LFS2_FILEBD_H
#define LFS2_FILEBD_H

#include "lfs2.h"
#include "lfs2_util.h"

#ifdef __cplusplus
extern "C"
{
#endif


// Block device specific tracing
#ifndef LFS2_FILEBD_TRACE
#ifdef LFS2_FILEBD_YES_TRACE
#define LFS2_FILEBD_TRACE(...) LFS2_TRACE(__VA_ARGS__)
#else
#define LFS2_FILEBD_TRACE(...)
#endif
#endif

// filebd config
struct lfs2_filebd_config {
    // Minimum size of a read operation in bytes.
    lfs2_size_t read_size;

    // Minimum size of a program operation in bytes.
    lfs2_size_t prog_size;

    // Size of an erase operation in bytes.
    lfs2_size_t erase_size;

    // Number of erase blocks on the device.
    lfs2_size_t erase_count;
};

// filebd state
typedef struct lfs2_filebd {
    int fd;
    const struct lfs2_filebd_config *cfg;
} lfs2_filebd_t;


// Create a file block device
int lfs2_filebd_create(const struct lfs2_config *cfg, const char *path,
        const struct lfs2_filebd_config *bdcfg);

// Clean up memory associated with block device
int lfs2_filebd_destroy(const struct lfs2_config *cfg);

// Read a block
int lfs2_filebd_read(const struct lfs2_config *cfg, lfs2_block_t block,
        lfs2_off_t off, void *buffer, lfs2_size_t size);

// Program a block
//
// The block must have previously been erased.
int lfs2_filebd_prog(const struct lfs2_config *cfg, lfs2_block_t block,
        lfs2_off_t off, const void *buffer, lfs2_size_t size);

// Erase a block
//
// A block must be erased before being programmed. The
// state of an erased block is undefined.
int lfs2_filebd_erase(const struct lfs2_config *cfg, lfs2_block_t block);

// Sync the block device
int lfs2_filebd_sync(const struct lfs2_config *cfg);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
