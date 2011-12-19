/****************************************************************************
 * KONOHA COPYRIGHT, LICENSE NOTICE, AND DISCRIMER
 *
 * Copyright (c) 2006-2011, Kimio Kuramitsu <kimio at ynu.ac.jp>
 *           (c) 2008-      Konoha Team konohaken@googlegroups.com
 * All rights reserved.
 *
 * You may choose one of the following two licenses when you use konoha.
 * If you want to use the latter license, please contact us.
 *
 * (1) GNU General Public License 3.0 (with K_UNDER_GPL)
 * (2) Konoha Non-Disclosure License 1.0
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/* ************************************************************************ */

#include"commons.h"

#include<time.h>
#ifdef K_USING_POSIX_
#include<unistd.h>
#endif

/* ************************************************************************ */

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ */
/* [random] */

void init_genrand(unsigned long s);
void init_genrand64(unsigned long long seed);
unsigned long genrand_int31(void);
unsigned long long genrand64_int63(void);
#ifndef K_USING_NOFLOAT
double genrand_real1(void);
double genrand64_real1(void);
#endif

void knh_srand(kuint_t seed)
{
	if(seed == 0) {
		/* You may choose a more secure way of generating the seed */
#ifdef K_USING_POSIX_
		seed = (kuint_t)time(NULL) + getpid();
#else
		seed = (kuint_t)time(NULL);
#endif
	}
#ifdef K_USING_INT32
	init_genrand((unsigned long)seed);
#else
	init_genrand64((unsigned long long int)seed);
#endif
}

kuint_t knh_rand(void)
{
#if defined(K_USING_INT32)
	return (kuint_t)genrand_int31();
#else
	return (kuint_t)genrand64_int63();
#endif
}

kfloat_t kfloat_rand(void)
{
#if defined(K_USING_NOFLOAT)
	return (kfloat_t)knh_rand();
#elif defined(K_USING_INT32)
	return (kfloat_t)genrand_real1();
#else
	return (kfloat_t)genrand64_real1();
#endif
}

/* ------------------------------------------------------------------------ */

kInt* new_Int_(CTX ctx, kclass_t cid, kint_t value)
{
	const knh_ClassTBL_t *ct = ClassTBL(cid);
	if(ct->constPoolMapNULL != NULL) {
		kInt *n = knh_PtrMap_getI(ctx, ct->constPoolMapNULL, (kunbox_t)value);
		if(n == NULL) {
			n = (kInt*)new_hObject_(ctx, ct);
			n->n.ivalue = value;
			knh_PtrMap_addI(ctx, ct->constPoolMapNULL, n);
		}
		return n;
	}
	else {
		kInt *b = (kInt*)new_hObject_(ctx, ct);
		b->n.ivalue = value;
		return b;
	}
}

kFloat* new_Float_(CTX ctx, kclass_t cid, kfloat_t value)
{
	const knh_ClassTBL_t *ct = ClassTBL(cid);
	if(ct->constPoolMapNULL != NULL) {
		ksfp_t lsfp;
		lsfp.fvalue = value;
		kInt *n = knh_PtrMap_getI(ctx, ct->constPoolMapNULL, lsfp.ndata);
		if(n == NULL) {
			n = (kInt*)new_hObject_(ctx, ct);
			n->n.fvalue = value;
			knh_PtrMap_addI(ctx, ct->constPoolMapNULL, n);
		}
		return (kFloat*)n;
	}
	else {
		kFloat *b = (kFloat*)new_hObject_(ctx, ct);
		b->n.fvalue = value;
		return b;
	}
}

KNHAPI2(kInt*) new_Int(CTX ctx, kint_t value)
{
	return new_Int_(ctx, CLASS_Int, value);
}

KNHAPI2(kFloat*) new_Float(CTX ctx, kfloat_t value)
{
	return new_Float_(ctx, CLASS_Float, value);
}

Object* new_Boxing(CTX ctx, ksfp_t *sfp, const knh_ClassTBL_t *ct)
{
	kObject *o = NULL;
	if(ct->constPoolMapNULL != NULL) {
		o = (kObject*)knh_PtrMap_getI(ctx, ct->constPoolMapNULL, sfp[0].ndata);
		if(o == NULL) {
			o = new_hObject_(ctx, ct);
			((kInt*)o)->n.data = sfp[0].ndata;
			knh_PtrMap_addI(ctx, ct->constPoolMapNULL, (kInt*)o);
		}
	}
	else {
		o = new_hObject_(ctx, ct);
		((kInt*)o)->n.data = sfp[0].ndata;
	}
	return o;
}

KNHAPI2(void) knh_boxing(CTX ctx, ksfp_t *sfp, int type)
{
	if(IS_Tunbox(type)) {
		const knh_ClassTBL_t *ct = ClassTBL(type);
		kObject *o;
		if(ct->constPoolMapNULL != NULL) {
			o = (kObject*)knh_PtrMap_getI(ctx, ct->constPoolMapNULL, sfp[0].ndata);
			if(o == NULL) {
				o = new_hObject_(ctx, ct);
				((kInt*)o)->n.data = sfp[0].ndata;
				knh_PtrMap_addI(ctx, ct->constPoolMapNULL, (kInt*)o);
			}
		}
		else {
			o = new_hObject_(ctx, ct);
			((kInt*)o)->n.data = sfp[0].ndata;
		}
		KNH_SETv(ctx, sfp[0].o, o);
	}
}

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
