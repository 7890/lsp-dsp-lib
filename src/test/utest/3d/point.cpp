/*
 * point.cpp
 *
 *  Created on: 30 авг. 2018 г.
 *      Author: sadko
 */

#include <lsp-plug.in/dsp/dsp.h>
#include <lsp-plug.in/test-fw/utest.h>
#include <private/utest/dsp/3d/helpers.h>

namespace lsp
{
    namespace generic
    {
        void init_point_xyz(dsp::point3d_t *p, float x, float y, float z);
        void init_point(dsp::point3d_t *p, const dsp::point3d_t *s);
        void normalize_point(dsp::point3d_t *p);
    }

    IF_ARCH_X86(
        namespace sse
        {
            void init_point_xyz(dsp::point3d_t *p, float x, float y, float z);
            void init_point(dsp::point3d_t *p, const dsp::point3d_t *s);
            void normalize_point(dsp::point3d_t *p);
        }
    )

    typedef void (* init_point_xyz_t)(dsp::point3d_t *p, float x, float y, float z);
    typedef void (* init_point_t)(dsp::point3d_t *p, const dsp::point3d_t *s);
    typedef void (* normalize_point_t)(dsp::point3d_t *p);
}

UTEST_BEGIN("dsp.3d", point)

    void call(
            const char *label,
            init_point_xyz_t init_xyz,
            init_point_t init,
            normalize_point_t norm
        )
    {
        if ((!UTEST_SUPPORTED(init_xyz)) || (!UTEST_SUPPORTED(init)) || (!UTEST_SUPPORTED(norm)))
            return;

        printf("Testing %s\n", label);

        dsp::point3d_t   p1, p2, p3;

        generic::init_point_xyz(&p1, 1.0f, 2.0f, 3.0f);
        init_xyz(&p2, 1.0f, 2.0f, 3.0f);
        UTEST_ASSERT_MSG(point3d_sck(&p1, &p2), "Failed init_point_xyz");

        generic::init_point(&p2, &p1);
        init(&p3, &p1);
        UTEST_ASSERT_MSG(point3d_sck(&p1, &p2), "Failed generic init_point");
        UTEST_ASSERT_MSG(point3d_sck(&p1, &p3), "Failed optimized init_point");

        generic::normalize_point(&p2);
        norm(&p3);

        UTEST_ASSERT_MSG(point3d_sck(&p2, &p3), "Failed normalize point");
    }

    UTEST_MAIN
    {
        IF_ARCH_X86(call("sse_point", sse::init_point_xyz, sse::init_point, sse::normalize_point));
    }
UTEST_END;



