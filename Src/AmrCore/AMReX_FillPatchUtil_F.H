#ifndef AMREX_FILLPATCH_UTIL_F_H_
#define AMREX_FILLPATCH_UTIL_F_H_

#include <AMReX_BLFort.H>

#ifdef __cplusplus
extern "C" {
#endif
    
    void amrex_interp_div_free_bfield (const int* lo, const int* hi
                                       , amrex_real* bx, const int* bxlo, const int* bxhi
#if (BL_SPACEDIM > 1)
                                       , amrex_real* by, const int* bylo, const int* byhi
#endif
#if (BL_SPACEDIM > 2)
                                       , amrex_real* bz, const int* bzlo, const int* bzhi
#endif
                                       , const amrex_real* cx, const int* cxlo, const int* cxhi
#if (BL_SPACEDIM > 1)
                                       , const amrex_real* cy, const int* cylo, const int* cyhi
#endif
#if (BL_SPACEDIM > 2)
                                       , const amrex_real* cz, const int* czlo, const int* czhi
#endif
                                       , const amrex_real* dx, const int* rr);

        void amrex_interp_efield (const int* lo, const int* hi
                                  , amrex_real* bx, const int* bxlo, const int* bxhi
#if (BL_SPACEDIM > 1)
                                  , amrex_real* by, const int* bylo, const int* byhi
#endif
#if (BL_SPACEDIM > 2)
                                  , amrex_real* bz, const int* bzlo, const int* bzhi
#endif
                                  , const amrex_real* cx, const int* cxlo, const int* cxhi
#if (BL_SPACEDIM > 1)
                                  , const amrex_real* cy, const int* cylo, const int* cyhi
#endif
#if (BL_SPACEDIM > 2)
                                  , const amrex_real* cz, const int* czlo, const int* czhi
#endif
                                  , const amrex_real* dx, const int* rr);

#ifdef __cplusplus
}
#endif

#endif
