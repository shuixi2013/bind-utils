/*
 * Copyright (C) 2004-2007, 2009, 2014  Internet Systems Consortium, Inc. ("ISC")
 * Copyright (C) 1999-2001  Internet Software Consortium.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/* $Id: random.h,v 1.20 2009/01/17 23:47:43 tbox Exp $ */

#ifndef ISC_RANDOM_H
#define ISC_RANDOM_H 1

#include <isc/lang.h>
#include <isc/types.h>
#include <isc/entropy.h>
#include <isc/mem.h>
#include <isc/mutex.h>

/*! \file isc/random.h
 * \brief Implements a random state pool which will let the caller return a
 * series of possibly non-reproducible random values.
 *
 * Note that the
 * strength of these numbers is not all that high, and should not be
 * used in cryptography functions.  It is useful for jittering values
 * a bit here and there, such as timeouts, etc.
 */

ISC_LANG_BEGINDECLS

typedef struct isc_rng isc_rng_t;
/*%<
 * Opaque type
 */

void
isc_random_seed(isc_uint32_t seed);
/*%<
 * Set the initial seed of the random state.
 */

void
isc_random_get(isc_uint32_t *val);
/*%<
 * Get a random value.
 *
 * Requires:
 *	val != NULL.
 */

isc_uint32_t
isc_random_jitter(isc_uint32_t max, isc_uint32_t jitter);
/*%<
 * Get a random value between (max - jitter) and (max).
 * This is useful for jittering timer values.
 */

isc_result_t
isc_rng_create(isc_mem_t *mctx, isc_entropy_t *entropy, isc_rng_t **rngp);
/*%<
 * Creates and initializes a pseudo random number generator. The
 * returned RNG can be used to generate pseudo random numbers.
 *
 * The reference count of the returned RNG is set to 1.
 *
 * Requires:
 * \li mctx is a pointer to a valid memory context.
 * \li entropy is an optional entopy source (can be NULL)
 * \li rngp != NULL && *rngp == NULL is where a pointer to the RNG is
 *     returned.
 *
 * Ensures:
 *\li	If result is ISC_R_SUCCESS:
 *		*rngp points to a valid RNG.
 *
 *\li	If result is failure:
 *		*rngp does not point to a valid RNG.
 *
 * Returns:
 *\li	#ISC_R_SUCCESS	Success
 *\li	#ISC_R_NOMEMORY Resource limit: Out of Memory
 */

void
isc_rng_attach(isc_rng_t *source, isc_rng_t **targetp);
/*%<
 * Increments a reference count on the passed RNG.
 *
 * Requires:
 * \li source the RNG struct to attach to (is refcount is incremented)
 * \li targetp != NULL && *targetp == NULL where a pointer to the
 *     reference incremented RNG is returned.
 */

void
isc_rng_detach(isc_rng_t **rngp);
/*%<
 * Decrements a reference count on the passed RNG. If the reference
 * count reaches 0, the RNG is destroyed.
 *
 * Requires:
 * \li rngp != NULL the RNG struct to decrement reference for
 */

isc_uint16_t
isc_rng_random(isc_rng_t *rngctx);
/*%<
 * Returns a pseudo random 16-bit unsigned integer.
 */

isc_uint16_t
isc_rng_uniformrandom(isc_rng_t *rngctx, isc_uint16_t upper_bound);
/*%<
 * Returns a uniformly distributed pseudo random 16-bit unsigned
 * integer.
 */

ISC_LANG_ENDDECLS

#endif /* ISC_RANDOM_H */
