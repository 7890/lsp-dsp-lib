/*
 * smath.h
 *
 *  Created on: 31 мар. 2020 г.
 *      Author: sadko
 */

#ifndef LSP_PLUG_IN_DSP_ARCH_GENERIC_SMATH_H_
#define LSP_PLUG_IN_DSP_ARCH_GENERIC_SMATH_H_

#ifndef LSP_PLUG_IN_DSP_ARCH_GENERIC_IMPL
    #error "This header should not be included directly"
#endif /* LSP_PLUG_IN_DSP_ARCH_GENERIC_IMPL */

namespace lsp
{
    namespace generic
    {
        float ipowf(float x, int deg)
        {
            float res = 1.0f;
            if (!deg)
                return res;

            if (deg < 0)
            {
                deg = -deg;

                do
                {
                    if (deg & 1)
                    {
                        --deg;
                        res *= x;
                    }
                    else
                    {
                        deg >>= 1;
                        x *= x;
                    }
                }
                while (deg);

                res = 1.0f / res;
            }
            else
            {
                do
                {
                    if (deg & 1)
                    {
                        --deg;
                        res *= x;
                    }
                    else
                    {
                        deg >>= 1;
                        x *= x;
                    }
                }
                while (deg);
            }

            return res;
        }

        float ipospowf(float x, int deg)
        {
            if (deg <= 1)
                return x;

            float res = 1.0f;

            do
            {
                if (deg & 1)
                {
                    --deg;
                    res *= x;
                }
                else
                {
                    deg >>= 1;
                    x *= x;
                }
            }
            while (deg);

            return res;
        }

        float irootf(float x, int deg)
        {
            // Check validity of arguments
            if (deg <= 1)
                return x;

            // While root is odd, simple calc square root
            if (!(deg & 1))
            {
                do
                {
                    x = sqrtf(x);
                    deg >>= 1;
                } while (!(deg & 1));

                if (deg <= 1)
                    return x;
            }

            // Newton method
            float xp;
            float a = 1.0f / float(deg);
            float k = float(--deg) * a;
            a *= x;

            do
            {
                xp      = x;
                x       = k*x + a / ipospowf(x, deg);
            } while (fabs(x - xp) > fabs(1e-5 * x));

            return x;
        }
    }
}

#endif /* LSP_PLUG_IN_DSP_ARCH_GENERIC_SMATH_H_ */
