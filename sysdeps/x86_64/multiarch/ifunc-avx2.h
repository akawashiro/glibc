/* Common definition for ifunc selections optimized with SSE2 and AVX2.
   All versions must be listed in ifunc-impl-list.c.
   Copyright (C) 2017-2022 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <init-arch.h>
#include "/home/akira/sloader/raw_write/raw_write.h"

extern __typeof (REDIRECT_NAME) OPTIMIZE (sse2) attribute_hidden;
extern __typeof (REDIRECT_NAME) OPTIMIZE (avx2) attribute_hidden;
extern __typeof (REDIRECT_NAME) OPTIMIZE (avx2_rtm) attribute_hidden;
extern __typeof (REDIRECT_NAME) OPTIMIZE (evex) attribute_hidden;

static inline void *
IFUNC_SELECTOR (void)
{
    // TODO (akawashiro)
  RAW_DEBUG_MESSAGE();
  const struct cpu_features* cpu_features = __get_cpu_features ();

  RAW_DEBUG_MESSAGE();
  RAW_NOP4();
  // TODO (akawashiro)
  // This dereference causes SEGV.
  unsigned long int shared_cache_size = cpu_features->shared_cache_size;
  RAW_DEBUG_MESSAGE();
  RAW_NOP4();
  RAW_PRINT_INT(shared_cache_size);
  RAW_DEBUG_MESSAGE();
  RAW_NOP4();
  bool cpu_features_AVX2 __attribute__((unused)) = CPU_FEATURE_USABLE_P (cpu_features, AVX2);
  RAW_DEBUG_MESSAGE();
  RAW_NOP4();
  bool cpu_features_BMI2 __attribute__((unused)) = CPU_FEATURE_USABLE_P (cpu_features, BMI2);
  RAW_DEBUG_MESSAGE();
  RAW_NOP4();
  bool cpu_features_AVX_Fast_Unalined_Load __attribute__((unused)) = CPU_FEATURES_ARCH_P(cpu_features, AVX_Fast_Unaligned_Load);
  RAW_NOP4();
  RAW_DEBUG_MESSAGE();

  // if (cpu_features_AVX2 && cpu_features_BMI2 && cpu_features_AVX_Fast_Unalined_Load)
  if (CPU_FEATURE_USABLE_P (cpu_features, AVX2)
      && CPU_FEATURE_USABLE_P (cpu_features, BMI2)
      && CPU_FEATURES_ARCH_P (cpu_features, AVX_Fast_Unaligned_Load))
    {
  RAW_DEBUG_MESSAGE();
      if (CPU_FEATURE_USABLE_P (cpu_features, AVX512VL)
	  && CPU_FEATURE_USABLE_P (cpu_features, AVX512BW))
	return OPTIMIZE (evex);

  RAW_DEBUG_MESSAGE();
      if (CPU_FEATURE_USABLE_P (cpu_features, RTM))
	return OPTIMIZE (avx2_rtm);

  RAW_DEBUG_MESSAGE();
      if (!CPU_FEATURES_ARCH_P (cpu_features, Prefer_No_VZEROUPPER))
	return OPTIMIZE (avx2);
    }

  RAW_DEBUG_MESSAGE();
  return OPTIMIZE (sse2);
}
