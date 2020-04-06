/*
 * helpers.h
 *
 *  Created on: 30 авг. 2018 г.
 *      Author: sadko
 */

#ifndef PRIVATE_UTEST_DSP_3D_HELPERS_H_
#define PRIVATE_UTEST_DSP_3D_HELPERS_H_

#include <lsp-plug.in/test-fw/helpers.h>
#include <lsp-plug.in/dsp/dsp.h>

namespace lsp
{
    namespace test
    {
        bool point3d_ck(const dsp::point3d_t *p1, const dsp::point3d_t *p2);
        bool point3d_sck(const dsp::point3d_t *p1, const dsp::point3d_t *p2);
        bool point3d_ack(const dsp::point3d_t *p1, const dsp::point3d_t *p2, float tolerance);
        bool vector3d_sck(const dsp::vector3d_t *v1, const dsp::vector3d_t *v2);
        bool vector3d_ack(const dsp::vector3d_t *v1, const dsp::vector3d_t *v2);
        bool matrix3d_ck(const dsp::matrix3d_t *m1, const dsp::matrix3d_t *m2);

        void dump_point(const char *text, const dsp::point3d_t *p);
        void dump_vector(const char *text, const dsp::vector3d_t *v);
    }
}

#endif /* PRIVATE_UTEST_DSP_3D_HELPERS_H_ */
