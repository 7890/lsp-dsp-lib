/*
 * float.h
 *
 *  Created on: 31 мар. 2020 г.
 *      Author: sadko
 */

#ifndef PRIVATE_DSP_ARCH_GENERIC_FLOAT_H_
#define PRIVATE_DSP_ARCH_GENERIC_FLOAT_H_

#ifndef PRIVATE_DSP_ARCH_GENERIC_IMPL
    #error "This header should not be included directly"
#endif /* PRIVATE_DSP_ARCH_GENERIC_IMPL */

namespace lsp
{
    namespace generic
    {
        void copy_saturated(float *dst, const float *src, size_t count)
        {
            while (count--)
            {
                float v = *(src++);
                if (isnan(v))
                    v       =   LSP_DSP_FLOAT_SAT_P_NAN;
                else if (isinf(v))
                    v       =   (v < 0.0f) ? LSP_DSP_FLOAT_SAT_N_INF : LSP_DSP_FLOAT_SAT_P_INF;

                *(dst++)    = v;
            }
        }

        void saturate(float *dst, size_t count)
        {
            while (count--)
            {
                float v = *dst;
                if (isnan(v))
                    *(dst++)    = LSP_DSP_FLOAT_SAT_P_NAN;
                else if (isinf(v))
                    *(dst++)    = (v < 0.0f) ? LSP_DSP_FLOAT_SAT_N_INF : LSP_DSP_FLOAT_SAT_P_INF;
                else
                    dst++;
            }
        }

        void limit_saturate1(float *dst, size_t count)
        {
            while (count--)
            {
                float v     = *dst;
                if (isnan(v))
                    v       =   LSP_DSP_FLOAT_SAT_P_NAN;
                else if (isinf(v))
                    v       =   (v < 0.0f) ? -1.0f : 1.0f;
                else if (v > 1.0f)
                    v       =   1.0f;
                else if (v < -1.0f)
                    v       =  -1.0f;

                *(dst++)    = v;
            }
        }

        void limit_saturate2(float *dst, const float *src, size_t count)
        {
            while (count--)
            {
                float v     = *(src++);
                if (isnan(v))
                    v       =   LSP_DSP_FLOAT_SAT_P_NAN;
                else if (isinf(v))
                    v       =   (v < 0.0f) ? -1.0f : 1.0f;
                else if (v > 1.0f)
                    v       =   1.0f;
                else if (v < -1.0f)
                    v       =  -1.0f;

                *(dst++)    = v;
            }
        }

        void limit1(float *dst, float min, float max, size_t count)
        {
            while (count--)
            {
                float v     = *dst;
                if (isnan(v))
                    v       =   min;
                else if (isinf(v))
                    v       =   (v < 0.0f) ? min : max;
                else if (v > max)
                    v       =   max;
                else if (v < min)
                    v       =  min;

                *(dst++)    = v;
            }
        }

        void limit2(float *dst, const float *src, float min, float max, size_t count)
        {
            while (count--)
            {
                float v     = *(src++);
                if (isnan(v))
                    v       =   min;
                else if (isinf(v))
                    v       =   (v < 0.0f) ? min : max;
                else if (v > max)
                    v       =   max;
                else if (v < min)
                    v       =  min;

                *(dst++)    = v;
            }
        }

        void sanitize1(float *dst, size_t count)
        {
            uint32_t *dptr = reinterpret_cast<uint32_t *>(dst);

            for (size_t i=0; i<count; ++i)
            {
                uint32_t v      = dptr[i];
                uint32_t a      = v & 0x7fffffff;   // Absolute value
                uint32_t s      = v & 0x80000000;   // Sign
                dptr[i]         = ((a > 0x007fffff) && (a <= 0x7f7fffff)) ? v : s;
            }
        }

        void sanitize2(float *dst, const float *src, size_t count)
        {
            uint32_t *dptr          = reinterpret_cast<uint32_t *>(dst);
            const uint32_t *sptr    = reinterpret_cast<const uint32_t *>(src);

            for (size_t i=0; i<count; ++i)
            {
                uint32_t v      = sptr[i];
                uint32_t a      = v & 0x7fffffff;   // Absolute value
                uint32_t s      = v & 0x80000000;   // Sign
                dptr[i]         = ((a > 0x007fffff) && (a <= 0x7f7fffff)) ? v : s;
            }
        }
    }
}

#endif /* PRIVATE_DSP_ARCH_GENERIC_FLOAT_H_ */
