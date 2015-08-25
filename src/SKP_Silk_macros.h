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

#ifndef _SKP_SILK_API_C_H_
#define _SKP_SILK_API_C_H_

// This is an inline header file for general platform.

// (a32 * (SKP_int32)((SKP_int16)(b32))) >> 16 output have to be 32bit int
#define SKP_SMULWB(a32, b32)            ((((a32) >> 16) * (SKP_int32)((SKP_int16)(b32))) + ((((a32) & 0x0000FFFF) * (SKP_int32)((SKP_int16)(b32))) >> 16))

// a32 + (b32 * (SKP_int32)((SKP_int16)(c32))) >> 16 output have to be 32bit int
#define SKP_SMLAWB(a32, b32, c32)       ((a32) + ((((b32) >> 16) * (SKP_int32)((SKP_int16)(c32))) + ((((b32) & 0x0000FFFF) * (SKP_int32)((SKP_int16)(c32))) >> 16)))

// (a32 * (b32 >> 16)) >> 16
#define SKP_SMULWT(a32, b32)            (((a32) >> 16) * ((b32) >> 16) + ((((a32) & 0x0000FFFF) * ((b32) >> 16)) >> 16))

// a32 + (b32 * (c32 >> 16)) >> 16
#define SKP_SMLAWT(a32, b32, c32)       ((a32) + (((b32) >> 16) * ((c32) >> 16)) + ((((b32) & 0x0000FFFF) * ((c32) >> 16)) >> 16))

// (SKP_int32)((SKP_int16)(a3))) * (SKP_int32)((SKP_int16)(b32)) output have to be 32bit int
#define SKP_SMULBB(a32, b32)            ((SKP_int32)((SKP_int16)(a32)) * (SKP_int32)((SKP_int16)(b32)))

// a32 + (SKP_int32)((SKP_int16)(b32)) * (SKP_int32)((SKP_int16)(c32)) output have to be 32bit int
#define SKP_SMLABB(a32, b32, c32)       ((a32) + ((SKP_int32)((SKP_int16)(b32))) * (SKP_int32)((SKP_int16)(c32)))

// (SKP_int32)((SKP_int16)(a32)) * (b32 >> 16)
#define SKP_SMULBT(a32, b32)            ((SKP_int32)((SKP_int16)(a32)) * ((b32) >> 16))

// a32 + (SKP_int32)((SKP_int16)(b32)) * (c32 >> 16)
#define SKP_SMLABT(a32, b32, c32)       ((a32) + ((SKP_int32)((SKP_int16)(b32))) * ((c32) >> 16))

// a64 + (b32 * c32)
#define SKP_SMLAL(a64, b32, c32)        (SKP_ADD64((a64), ((SKP_int64)(b32) * (SKP_int64)(c32))))

// (a32 * b32) >> 16
#define SKP_SMULWW(a32, b32)            SKP_MLA(SKP_SMULWB((a32), (b32)), (a32), SKP_RSHIFT_ROUND((b32), 16))

// a32 + ((b32 * c32) >> 16)
#define SKP_SMLAWW(a32, b32, c32)       SKP_MLA(SKP_SMLAWB((a32), (b32), (c32)), (b32), SKP_RSHIFT_ROUND((c32), 16))

#endif //_SKP_SILK_API_C_H_

