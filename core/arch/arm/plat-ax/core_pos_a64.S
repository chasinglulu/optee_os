/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2024 Charley wangkart@aliyun.com
 */

#include <asm.S>
#include <arm.h>

FUNC get_core_pos_mpidr , :
	lsr	x0, x0, #8
	and	x1, x0, #MPIDR_CPU_MASK
	and	x0, x0, #MPIDR_CLUSTER_MASK
	add	x0, x1, x0, lsr #6
	ret
END_FUNC get_core_pos_mpidr