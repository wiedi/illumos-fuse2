/*
 * This file and its contents are supplied under the terms of the
 * Common Development and Distribution License ("CDDL"), version 1.0.
 * You may only use this file in accordance with the terms of version
 * 1.0 of the CDDL.
 *
 * A full copy of the text of the CDDL should have accompanied this
 * source.  A copy of the CDDL is also available via the Internet at
 * http://www.illumos.org/license/CDDL.
 */

/*
 * Copyright 2011 Nexenta Systems, Inc.  All rights reserved.
 */

#ifndef _FS_FUSEFS_FUSE_DOOR_H_
#define	_FS_FUSEFS_FUSE_DOOR_H_

#include <sys/param.h>
#include "fuse_ktypes.h"

/*
 * Door calls implemented by fuse-dmn
 */

/* Maximum I/O size per FUSE read/write call. */
#define	FUSE_MAX_IOSIZE	MAXBSIZE	/* 8K for now */

/* Op. codes. */
typedef enum {
	FUSE_OP_INIT = 1,
	FUSE_OP_DESTROY,
	FUSE_OP_STATVFS,

	FUSE_OP_FGETATTR,
	FUSE_OP_GETATTR,

	FUSE_OP_OPENDIR,
	FUSE_OP_CLOSEDIR,
	FUSE_OP_READDIR,

	FUSE_OP_OPEN,
	FUSE_OP_CLOSE,
	FUSE_OP_READ,
	FUSE_OP_WRITE,
	FUSE_OP_FLUSH,
	/* modify */
	FUSE_OP_CREATE,
	FUSE_OP_FTRUNCATE,
	FUSE_OP_TRUNCATE,
	FUSE_OP_UTIMES,
	FUSE_OP_CHMOD,
	FUSE_OP_CHOWN,
	FUSE_OP_DELETE,
	FUSE_OP_RENAME,
	FUSE_OP_MKDIR,
	FUSE_OP_RMDIR,
} fuse_opcode_t;

/* For ops that don't send data. */
struct fuse_generic_arg {
	int32_t arg_opcode;
	uint32_t arg_flags;
};

/* For ops that don't return data. */
struct fuse_generic_ret {
	int32_t ret_err;
	uint32_t ret_flags;
};

/* XXX fuse_init_ret? */

/* Calls with a FID (fstat, read, write) */
struct fuse_fid_arg {
	uint32_t arg_opcode;
	uint32_t arg_flags;
	uint64_t arg_fid;
};

/* Calls the return a FID (open, opendir) */
struct fuse_fid_ret {
	uint32_t ret_err;
	uint32_t ret_flags;
	uint64_t ret_fid;
};


struct fuse_statvfs_ret {
	uint32_t ret_err;
	uint32_t ret_flags;
	struct fuse_statvfs ret_stvfs;
};

struct fuse_getattr_ret {
	uint32_t ret_err;
	uint32_t ret_flags;
	struct fuse_stat ret_st;
};

/* For ops that send one path name. */
struct fuse_path_arg {
	uint32_t arg_opcode;
	uint32_t arg_flags;
	uint32_t arg_pathlen;
	char arg_path[MAXPATHLEN];
};

/* For ops that send two path names. */
struct fuse_path2_arg {
	uint32_t arg_opcode;
	uint32_t arg_flags;

	uint32_t arg_p1len;
	uint32_t arg_p2len;
	char arg_path1[MAXPATHLEN];
	char arg_path2[MAXPATHLEN];
};

struct fuse_readdir_arg {
	uint32_t arg_opcode;
	uint32_t arg_flags;

	uint64_t arg_fid;
	off64_t arg_offset;
	/* FUSE wants the path here too. */
	uint32_t arg_pathlen;
	char arg_path[MAXPATHLEN];
};

struct fuse_readdir_ret {
	uint32_t ret_err;
	uint32_t ret_flags;	/* EOF flag */

	struct fuse_stat ret_st;
	struct fuse_dirent ret_de;
	char ret_path[MAXNAMELEN]; /* ret_de.d_name */
};

struct fuse_read_arg {
	uint32_t arg_opcode;
	uint32_t arg_flags;

	uint64_t arg_fid;
	off64_t arg_offset;
	uint32_t arg_length;
	/* FUSE wants the path here too. */
	uint32_t arg_pathlen;
	char arg_path[MAXPATHLEN];
};

struct fuse_read_ret {
	uint32_t ret_err;
	uint32_t ret_length;
	char ret_data[FUSE_MAX_IOSIZE];
};

struct fuse_write_arg {
	uint32_t arg_opcode;
	uint32_t arg_flags;

	uint64_t arg_fid;
	off64_t arg_offset;
	uint32_t arg_length;
	/* FUSE wants the path here too. */
	uint32_t arg_pathlen;
	char arg_path[MAXPATHLEN];
	char arg_data[FUSE_MAX_IOSIZE];
};

struct fuse_write_ret {
	uint32_t ret_err;
	uint32_t ret_length;
};

#endif /* !_FS_FUSEFS_FUSE_DOOR_H_ */
