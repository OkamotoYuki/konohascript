///****************************************************************************
// * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
// *
// * Copyright (c)  2010-      Konoha Team konohaken@googlegroups.com
// * All rights reserved.
// *
// * You may choose one of the following two licenses when you use konoha.
// * See www.konohaware.org/license.html for further information.
// *
// * (1) GNU Lesser General Public License 3.0 (with KONOHA_UNDER_LGPL3)
// * (2) Konoha Software Foundation License 1.0
// *
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
// * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// *
// ****************************************************************************/
//
//// **************************************************************************
//// LIST OF CONTRIBUTERS
////  goccy -
////  kimio - Kimio Kuramitsu, Yokohama National University, Japan
////
//// **************************************************************************
//
//#include <konoha1.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
//#include "../third-party/ext/md5.h"
//
//#define MD5_DIGEST_LENGTH 16
//
//static knh_bool_t md5digest(Ctx *ctx, knh_conv_t *conv, knh_bytes_t from, knh_Bytes_t *tobuf)
//{
//	MD5_CTX md5_ctx;
//	unsigned char md5buf[MD5_DIGEST_LENGTH] = {0};
//	MD5_Init(&md5_ctx);
//	MD5_Update(&md5_ctx, from.str, from.len);
//	MD5_Final(md5buf, &md5_ctx);
//	knh_write(ctx, tobuf, (char*)md5buf, MD5_DIGEST_LENGTH);
//	return 1;
//}
//
//static knh_bool_t md5string(Ctx *ctx, knh_conv_t *conv, knh_bytes_t from, knh_Bytes_t *tobuf)
//{
//	MD5_CTX md5_ctx;
//	unsigned char md5buf[MD5_DIGEST_LENGTH] = {0};
//	MD5_Init(&md5_ctx);
//	MD5_Update(&md5_ctx, from.str, from.len);
//	MD5_Final(md5buf, &md5_ctx);
//	{
//		char buf[4];
//		size_t i;
//		for (i = 0; i< MD5_DIGEST_LENGTH; i++) {
//			knh_snprintf(buf, sizeof(buf), "%02x", md5buf[i]);
//			knh_write(ctx, tobuf, buf, 2);
//		}
//	}
//	return 1;
//}
//
//static void md5_close(Ctx *ctx, knh_conv_t *conv)
//{
//}
//
//static knh_ConverterDSPI_t md5Converter = {
//	K_CONVTO_DSPI, "md5",
//	NULL, //md5_open,
//	md5digest,  // byte->byte     :conv
//	md5digest,  // String->byte   :enc
//	md5string,   // byte->String   :dec
//	md5string,  // String->String :sconv
//	md5_close,
//	NULL
//};
//
//void string_addDigest(Ctx *ctx, knh_LoaderAPI_t *kapi, char *dname, int isOVERRIDE)
//{
//	if(knh_isSelectedDSPI(dname, "md5")) {
//		kapi->addConverterDSPI(ctx, "md5", &md5Converter, isOVERRIDE);
//	}
//}
//
//
