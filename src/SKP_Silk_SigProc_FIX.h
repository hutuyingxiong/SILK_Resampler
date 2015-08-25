/***********************************************************************
Copyright (c) 2006-2011, Skype Limited. All rights reserved. 
Redistribution and use in source and binary forms, with or without 
modification, (subject to the limitations in the disclaimer below) 
are permitted provided that the following conditions are met:
- Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright 
notice, this list of conditions and the following disclaimer in the 
documentation and/or other materials provided with the distribution.
- Neither the name of Skype Limited, nor the names of specific 
contributors, may be used to endorse or promote products derived from 
this software without specific prior written permission.
NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED 
BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
CONTRIBUTORS ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF 
USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************/

#ifndef _SKP_SILK_SIGPROC_FIX_H_
#define _SKP_SILK_SIGPROC_FIX_H_

#include "SKP_Silk_AsmPreproc_Config.h"

#ifdef  __cplusplus
extern "C"
{
#endif

#include "SKP_Silk_typedef.h"
#include <string.h>
#include <stdlib.h>                                            /* for abs() */
#include "SKP_Silk_resampler_structs.h"

#ifndef NO_ASM
#include "SKP_Silk_macros_arm.h"
#else
#include "SKP_Silk_macros.h"
#endif

/********************************************************************/
/*                    SIGNAL PROCESSING FUNCTIONS                   */
/********************************************************************/

/*!
 * Initialize/reset the resampler state for a given pair of input/output sampling rates 
*/
SKP_int SKP_Silk_resampler_init( 
	SKP_Silk_resampler_state_struct	*S,		    /* I/O: Resampler state 			*/
	SKP_int32							Fs_Hz_in,	/* I:	Input sampling rate (Hz)	*/
	SKP_int32							Fs_Hz_out	/* I:	Output sampling rate (Hz)	*/
);

/*!
 * Clear the states of all resampling filters, without resetting sampling rate ratio 
 */
SKP_int SKP_Silk_resampler_clear( 
	SKP_Silk_resampler_state_struct	*S		    /* I/O: Resampler state 			*/
);

/*!
 * Resampler: convert from one sampling rate to another
 */
SKP_int SKP_Silk_resampler( 
	SKP_Silk_resampler_state_struct	*S,		    /* I/O: Resampler state 			*/
	SKP_int16							out[],	    /* O:	Output signal 				*/
	const SKP_int16						in[],	    /* I:	Input signal				*/
	SKP_int32							inLen	    /* I:	Number of input samples		*/
);

/*!
 Upsample 2x, low quality 
 */
void SKP_Silk_resampler_up2(
    SKP_int32                           *S,         /* I/O: State vector [ 2 ]                  */
    SKP_int16                           *out,       /* O:   Output signal [ 2 * len ]           */
    const SKP_int16                     *in,        /* I:   Input signal [ len ]                */
    SKP_int32                           len         /* I:   Number of input samples             */
);

/*!
* Downsample 2x, mediocre quality 
*/
void SKP_Silk_resampler_down2(
    SKP_int32                           *S,         /* I/O: State vector [ 2 ]                  */
    SKP_int16                           *out,       /* O:   Output signal [ len ]               */
    const SKP_int16                     *in,        /* I:   Input signal [ floor(len/2) ]       */
    SKP_int32                           inLen       /* I:   Number of input samples             */
);

/*!
 * Downsample by a factor 2/3, low quality
*/
void SKP_Silk_resampler_down2_3(
    SKP_int32                           *S,         /* I/O: State vector [ 6 ]                  */
    SKP_int16                           *out,       /* O:   Output signal [ floor(2*inLen/3) ]  */
    const SKP_int16                     *in,        /* I:   Input signal [ inLen ]              */
    SKP_int32                           inLen       /* I:   Number of input samples             */
);

/*!
 * Downsample by a factor 3, low quality
*/
void SKP_Silk_resampler_down3(
    SKP_int32                           *S,         /* I/O: State vector [ 8 ]                  */
    SKP_int16                           *out,       /* O:   Output signal [ floor(inLen/3) ]    */
    const SKP_int16                     *in,        /* I:   Input signal [ inLen ]              */
    SKP_int32                           inLen       /* I:   Number of input samples             */
);

/********************************************************************/
/*                                MACROS                            */
/********************************************************************/

/* Allocate SKP_int16 alligned to 4-byte memory address */
#ifdef EMBEDDED_ARM
#define SKP_DWORD_ALIGN __attribute__((aligned(4)))
#else
#define SKP_DWORD_ALIGN
#endif

/* Useful Macros that can be adjusted to other platforms */
#define SKP_memcpy(a, b, c)                memcpy((a), (b), (c))    /* Dest, Src, ByteCount */
#define SKP_memset(a, b, c)                memset((a), (b), (c))    /* Dest, value, ByteCount */
#define SKP_memmove(a, b, c)               memmove((a), (b), (c))    /* Dest, Src, ByteCount */
/* fixed point macros */

// (a32 * b32) output have to be 32bit int
#define SKP_MUL(a32, b32)                  ((a32) * (b32))

// (a32 * b32) output have to be 32bit uint
#define SKP_MUL_uint(a32, b32)             SKP_MUL(a32, b32)

// a32 + (b32 * c32) output have to be 32bit int
#define SKP_MLA(a32, b32, c32)             SKP_ADD32((a32),((b32) * (c32)))

// a32 + ((a32 >> 16)  * (b32 >> 16)) output have to be 32bit int
#define SKP_SMLATT(a32, b32, c32)          SKP_ADD32((a32),((b32) >> 16) * ((c32) >> 16))

#define SKP_SMLALBB(a64, b16, c16)         SKP_ADD64((a64),(SKP_int64)((SKP_int32)(b16) * (SKP_int32)(c16)))

// (a32 * b32)
#define SKP_SMULL(a32, b32)                ((SKP_int64)(a32) * /*(SKP_int64)*/(b32))

// multiply-accumulate macros that allow overflow in the addition (ie, no asserts in debug mode)
#define SKP_MLA_ovflw(a32, b32, c32)       SKP_MLA(a32, b32, c32)
#ifndef SKP_SMLABB_ovflw
#    define SKP_SMLABB_ovflw(a32, b32, c32)    SKP_SMLABB(a32, b32, c32)
#endif
#define SKP_SMLATT_ovflw(a32, b32, c32)    SKP_SMLATT(a32, b32, c32)
#define SKP_SMLAWB_ovflw(a32, b32, c32)    SKP_SMLAWB(a32, b32, c32)
#define SKP_SMLAWT_ovflw(a32, b32, c32)    SKP_SMLAWT(a32, b32, c32)

#define SKP_DIV32_16(a32, b16)             ((SKP_int32)((a32) / (b16)))
#define SKP_DIV32(a32, b32)                ((SKP_int32)((a32) / (b32)))

#define SKP_ADD32(a, b)                    ((a) + (b))
#define SKP_ADD64(a, b)                    ((a) + (b))

#define SKP_SUB32(a, b)                    ((a) - (b))

#define SKP_SAT16(a)                       ((a) > SKP_int16_MAX ? SKP_int16_MAX : \
                                           ((a) < SKP_int16_MIN ? SKP_int16_MIN : (a)))
#define SKP_SAT32(a)                       ((a) > SKP_int32_MAX ? SKP_int32_MAX : \
                                           ((a) < SKP_int32_MIN ? SKP_int32_MIN : (a)))

#define SKP_CHECK_FIT16(a)                 (a)
#define SKP_CHECK_FIT32(a)                 (a)

#define SKP_ADD_SAT16(a, b)                (SKP_int16)SKP_SAT16( SKP_ADD32( (SKP_int32)(a), (b) ) )

/* Add with saturation for positive input values */ 
#define SKP_ADD_POS_SAT32(a, b)            ((((a)+(b)) & 0x80000000)           ? SKP_int32_MAX : ((a)+(b)))

#define SKP_LSHIFT32(a, shift)             ((a)<<(shift))                // shift >= 0, shift < 32
#define SKP_LSHIFT64(a, shift)             ((a)<<(shift))                // shift >= 0, shift < 64
#define SKP_LSHIFT(a, shift)               SKP_LSHIFT32(a, shift)        // shift >= 0, shift < 32

#define SKP_RSHIFT32(a, shift)             ((a)>>(shift))                // shift >= 0, shift < 32
#define SKP_RSHIFT64(a, shift)             ((a)>>(shift))                // shift >= 0, shift < 64
#define SKP_RSHIFT(a, shift)               SKP_RSHIFT32(a, shift)        // shift >= 0, shift < 32

/* saturates before shifting */
#define SKP_LSHIFT_SAT32(a, shift)         (SKP_LSHIFT32( SKP_LIMIT( (a), SKP_RSHIFT32( SKP_int32_MIN, (shift) ),    \
                                                                          SKP_RSHIFT32( SKP_int32_MAX, (shift) ) ), (shift) ))

#define SKP_LSHIFT_ovflw(a, shift)        ((a)<<(shift))        // shift >= 0, allowed to overflow
#define SKP_LSHIFT_uint(a, shift)         ((a)<<(shift))        // shift >= 0
#define SKP_RSHIFT_uint(a, shift)         ((a)>>(shift))        // shift >= 0

#define SKP_ADD_LSHIFT(a, b, shift)       ((a) + SKP_LSHIFT((b), (shift)))            // shift >= 0
#define SKP_ADD_LSHIFT32(a, b, shift)     SKP_ADD32((a), SKP_LSHIFT32((b), (shift)))    // shift >= 0
#define SKP_ADD_RSHIFT(a, b, shift)       ((a) + SKP_RSHIFT((b), (shift)))            // shift >= 0
#define SKP_ADD_RSHIFT32(a, b, shift)     SKP_ADD32((a), SKP_RSHIFT32((b), (shift)))    // shift >= 0
#define SKP_ADD_RSHIFT_uint(a, b, shift)  ((a) + SKP_RSHIFT_uint((b), (shift)))        // shift >= 0
#define SKP_SUB_LSHIFT32(a, b, shift)     SKP_SUB32((a), SKP_LSHIFT32((b), (shift)))    // shift >= 0
#define SKP_SUB_RSHIFT32(a, b, shift)     SKP_SUB32((a), SKP_RSHIFT32((b), (shift)))    // shift >= 0

/* Requires that shift > 0 */
#define SKP_RSHIFT_ROUND(a, shift)        ((shift) == 1 ? ((a) >> 1) + ((a) & 1) : (((a) >> ((shift) - 1)) + 1) >> 1)
#define SKP_RSHIFT_ROUND64(a, shift)      ((shift) == 1 ? ((a) >> 1) + ((a) & 1) : (((a) >> ((shift) - 1)) + 1) >> 1)

#define SKP_min(a, b)                     (((a) < (b)) ? (a) : (b))
#define SKP_max(a, b)                     (((a) > (b)) ? (a) : (b))

#ifdef  __cplusplus
}
#endif

#endif
