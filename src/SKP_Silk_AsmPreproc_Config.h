#ifndef __SKP_SILK_ASM_PREPROC_CONFIG_H__
#define __SKP_SILK_ASM_PREPROC_CONFIG_H__

#if (defined(__arm__) || defined(__arm) || defined(__ARMEL__))
#define SILK_USE_ARM_ASM  1
#else
#define SILK_USE_ARM_ASM  0
#endif

#if !SILK_USE_ARM_ASM
#define NO_ASM
#endif

/* Legacy definition wrapper */
#ifndef NO_ASM
#	if defined (__ARM_ARCH_4__) || defined (__ARM_ARCH_4T__) || defined (__ARM_ARCH_5__) || defined (__ARM_ARCH_5T__)
#		define EMBEDDED_ARM 4
#		define EMBEDDED_ARMv4
#	elif defined (__ARM_ARCH_5TE__) || defined (__ARM_ARCH_5TEJ__)
#		define EMBEDDED_ARM 5
#		define EMBEDDED_ARMv5
#	elif defined (__ARM_ARCH_6__) ||defined (__ARM_ARCH_6J__) || defined (__ARM_ARCH_6Z__) || defined (__ARM_ARCH_6K__) || defined(__ARM_ARCH_6ZK__) || defined(__ARM_ARCH_6T2__)
#		define EMBEDDED_ARM 6
#		define EMBEDDED_ARMv6
#	elif (defined (__ARM_ARCH_7A__) || defined (__ARM_ARCH_7S__)) && defined (__ARM_NEON__)
#		define EMBEDDED_ARM 7
#		define EMBEDDED_ARMv6
#	elif defined (__ARM_ARCH_7A__) || defined (__ARM_ARCH_7S__)
#		define EMBEDDED_ARM 6
#		define EMBEDDED_ARMv6
#	endif
#endif  /* NO_ASM */

#endif  /* __TRAE_SKP_SILK_ASM_PREPROC_H__ */
