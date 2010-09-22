#include <ParmParse.H>
#include <MGT_Solver.H>

bool  MGT_Solver::initialized;
int   MGT_Solver::def_nu_1;
int   MGT_Solver::def_nu_2;
int   MGT_Solver::def_nu_b;
int   MGT_Solver::def_nu_f;
int   MGT_Solver::def_gamma;
Real  MGT_Solver::def_omega;
int   MGT_Solver::def_maxiter;
int   MGT_Solver::def_maxiter_b;
int   MGT_Solver::def_verbose;
int   MGT_Solver::def_cg_verbose;
int   MGT_Solver::def_max_nlevel;
int   MGT_Solver::def_min_width;
int   MGT_Solver::def_smoother;
int   MGT_Solver::def_cycle;
int   MGT_Solver::def_usecg;
int   MGT_Solver::def_cg_solver;
int   MGT_Solver::def_bottom_solver;
Real  MGT_Solver::def_bottom_solver_eps;
int   MGT_Solver::stencil_type;

typedef void (*mgt_get)(const int* lev, const int* n, double* uu, 
			const int* plo, const int* phi, 
			const int* lo, const int* hi);
typedef void (*mgt_get_ng)(const int* lev, const int* n, double* uu, 
			   const int* plo, const int* phi, 
   			   const int* lo, const int* hi, const int* ng);
typedef void (*mgt_get_dir)(const int* lev, const int* dir, const int* n, 
			    double* uu,
			    const int* plo, const int* phi, 
   			    const int* lo, const int* hi);
typedef void (*mgt_set)(const int* lev, const int* n, const double* uu, 
			const int* plo, const int* phi, 
			const int* lo, const int* hi);
typedef void (*mgt_setn)(const int* lev, const int* n, const double* uu, 
		 	 const int* plo, const int* phi, 
			 const int* lo, const int* hi, const int& nc);
typedef void (*mgt_set_cf)(const int* lev, const int* n, const double* uu, 
                           const double* b, 
                           const int* plo, const int* phi, 
                           const int* lo, const int* hi);
typedef void (*mgt_set_cfn)(const int* lev, const int* n, const double* uu, 
                            const double* b, 
                            const int* plo, const int* phi, 
                            const int* lo, const int* hi, const int& nc);
typedef void (*mgt_set_c)(const int* lev, const int* n, 
		          const int* lo, const int* hi, const Real* value);
#if BL_SPACEDIM == 1
mgt_get_ng  mgt_get_uu         = mgt_get_uu_1d;
mgt_set     mgt_set_uu         = mgt_set_uu_1d;
mgt_get     mgt_get_pr         = mgt_get_pr_1d;
mgt_get     mgt_get_res        = mgt_get_res_1d;
mgt_get_dir mgt_get_gp         = mgt_get_gp_1d;
mgt_set     mgt_set_pr         = mgt_set_pr_1d;
mgt_set     mgt_set_rh         = mgt_set_rh_1d;
mgt_set     mgt_set_cfa        = mgt_set_cfa_1d;
mgt_setn    mgt_set_cfa2       = mgt_set_cfa2_1d;
mgt_set_cf  mgt_set_cfbx       = mgt_set_cfbx_1d;
mgt_set_cfn mgt_set_cfbnx      = mgt_set_cfbnx_1d;
mgt_set_c   mgt_set_cfa_const  = mgt_set_cfa_1d_const;
mgt_set_c   mgt_set_cfbx_const = mgt_set_cfbx_1d_const;
mgt_set mgt_set_cfs            = mgt_set_cfs_1d;
mgt_get mgt_get_vel            = mgt_get_vel_1d;
mgt_set mgt_set_vel            = mgt_set_vel_1d;
#elif BL_SPACEDIM == 2
mgt_get_ng  mgt_get_uu         = mgt_get_uu_2d;
mgt_set     mgt_set_uu         = mgt_set_uu_2d;
mgt_get     mgt_get_pr         = mgt_get_pr_2d;
mgt_get     mgt_get_res        = mgt_get_res_2d;
mgt_get_dir mgt_get_gp         = mgt_get_gp_2d;
mgt_set     mgt_set_pr         = mgt_set_pr_2d;
mgt_set     mgt_set_rh         = mgt_set_rh_2d;
mgt_set     mgt_set_cfa        = mgt_set_cfa_2d;
mgt_setn    mgt_set_cfa2       = mgt_set_cfa2_2d;
mgt_set_c   mgt_set_cfa_const  = mgt_set_cfa_2d_const;
mgt_set_cf  mgt_set_cfbx       = mgt_set_cfbx_2d;
mgt_set_cfn mgt_set_cfbnx      = mgt_set_cfbnx_2d;
mgt_set_c   mgt_set_cfbx_const = mgt_set_cfbx_2d_const;
mgt_set_cf  mgt_set_cfby       = mgt_set_cfby_2d;
mgt_set_cfn mgt_set_cfbny      = mgt_set_cfbny_2d;
mgt_set_c   mgt_set_cfby_const = mgt_set_cfby_2d_const;
mgt_set mgt_set_cfs            = mgt_set_cfs_2d;
mgt_get mgt_get_vel            = mgt_get_vel_2d;
mgt_set mgt_set_vel            = mgt_set_vel_2d;
#elif BL_SPACEDIM == 3
mgt_get_ng  mgt_get_uu         = mgt_get_uu_3d;
mgt_set     mgt_set_uu         = mgt_set_uu_3d;
mgt_get     mgt_get_pr         = mgt_get_pr_3d;
mgt_get     mgt_get_res        = mgt_get_res_3d;
mgt_get_dir mgt_get_gp         = mgt_get_gp_3d;
mgt_set     mgt_set_pr         = mgt_set_pr_3d;
mgt_set     mgt_set_rh         = mgt_set_rh_3d;
mgt_set     mgt_set_cfa        = mgt_set_cfa_3d;
mgt_setn    mgt_set_cfa2       = mgt_set_cfa2_3d;
mgt_set_c   mgt_set_cfa_const  = mgt_set_cfa_3d_const;
mgt_set_cf  mgt_set_cfbx       = mgt_set_cfbx_3d;
mgt_set_cfn mgt_set_cfbnx      = mgt_set_cfbnx_3d;
mgt_set_c   mgt_set_cfbx_const = mgt_set_cfbx_3d_const;
mgt_set_cf  mgt_set_cfby       = mgt_set_cfby_3d;
mgt_set_cfn mgt_set_cfbny      = mgt_set_cfbny_3d;
mgt_set_c   mgt_set_cfby_const = mgt_set_cfby_3d_const;
mgt_set_cf  mgt_set_cfbz       = mgt_set_cfbz_3d;
mgt_set_cfn mgt_set_cfbnz      = mgt_set_cfbnz_3d;
mgt_set_c   mgt_set_cfbz_const = mgt_set_cfbz_3d_const;
mgt_set mgt_set_cfs            = mgt_set_cfs_3d;
mgt_get mgt_get_vel            = mgt_get_vel_3d;
mgt_set mgt_set_vel            = mgt_set_vel_3d;
#endif

MGT_Solver::MGT_Solver(const std::vector<Geometry>& geom, 
                       int* bc, 
		       const std::vector<BoxArray>& grids,
		       const std::vector<DistributionMapping>& dmap,
		       bool nodal)
  :
  m_dmap(dmap), m_grids(grids), m_nodal(nodal)
{

   if (!initialized)
        initialize(nodal);

  BL_ASSERT( m_grids.size() == dmap.size() );
  m_nlevel = grids.size();
  int dm = BL_SPACEDIM;
  int i_nodal = (m_nodal)?1:0;

  if (nodal) {
    mgt_nodal_alloc(&dm, &m_nlevel, &i_nodal, &stencil_type);
    mgt_set_nodal_defaults(&def_nu_1,&def_nu_2,&def_nu_b,&def_nu_f,&def_gamma,&def_omega,
                           &def_maxiter,&def_maxiter_b,&def_bottom_solver,&def_bottom_solver_eps,
                           &def_verbose,&def_cg_verbose,&def_max_nlevel,
                           &def_min_width,&def_cycle,&def_smoother,&stencil_type);
  } else {
    mgt_alloc(&dm, &m_nlevel, &i_nodal);
    mgt_set_defaults(&def_nu_1,&def_nu_2,&def_nu_b,&def_nu_f,&def_gamma,&def_omega,
                     &def_maxiter,&def_maxiter_b,&def_bottom_solver,&def_bottom_solver_eps,
                     &def_verbose,&def_cg_verbose,&def_max_nlevel,
                     &def_min_width,&def_cycle,&def_smoother,&stencil_type);
  }

  Array<int> pm(dm);
  for ( int i = 0; i < dm; ++i ) 
    {
      pm[i] = geom[0].isPeriodic(i)? 1 : 0;
    }

  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      const Array<int>& pmap = dmap[lev].ProcessorMap();
      Box domain = geom[lev].Domain();

      int nb = grids[lev].size();
      std::vector<int> lo(nb*dm);
      std::vector<int> hi(nb*dm);

      for ( int i = 0; i < nb; ++i )
      {
        for ( int j = 0; j < dm; ++j )
	{
	  lo[i + j*nb] = m_grids[lev][i].smallEnd(j);
	  hi[i + j*nb] = m_grids[lev][i].bigEnd(j);
	}
      }

      if (nodal) {
        mgt_set_nodal_level(&lev, &nb, &dm, &lo[0], &hi[0], 
  		            domain.loVect(), domain.hiVect(), pm.dataPtr(), &pmap[0]);
      } else {
        mgt_set_level(&lev, &nb, &dm, &lo[0], &hi[0], 
  		      domain.loVect(), domain.hiVect(), pm.dataPtr(), &pmap[0]);
      }
    }

  std::vector<Real> dx(m_nlevel*dm);
  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      for ( int j = 0; j < dm; ++j )
	{
	  dx[lev + j*m_nlevel] = geom[lev].CellSize()[j];
	}
    }

  if (nodal) {
    mgt_nodal_finalize(&dx[0],&bc[0]);
  } else {
    mgt_finalize(&dx[0],&bc[0]);
  }
}


//
// Constructing a solver for the following operator: 
//    (\alpha I - \beta \sum_i (1/b_i) \nabla a_i \nabla) \phi
//

MGT_Solver::MGT_Solver(const std::vector<Geometry>& geom, 
                       int* bc, 
		       const std::vector<BoxArray>& grids,
		       const std::vector<DistributionMapping>& dmap,
		       bool nodal,
		       int nc, 
		       int ncomp)
  :
  m_dmap(dmap), m_grids(grids), m_nodal(nodal)
{

   if (!initialized)
        initialize(nodal);

  BL_ASSERT( m_grids.size() == dmap.size() );
  m_nlevel = grids.size();
  int dm = BL_SPACEDIM;
  int i_nodal = (m_nodal)?1:0;

  if (nodal) {
    mgt_nodal_alloc(&dm, &m_nlevel, &i_nodal, &stencil_type);
    mgt_set_nodal_defaults(&def_nu_1,&def_nu_2,&def_nu_b,&def_nu_f,&def_gamma,&def_omega,
                           &def_maxiter,&def_maxiter_b,&def_bottom_solver,&def_bottom_solver_eps,
                           &def_verbose,&def_cg_verbose,&def_max_nlevel,
                           &def_min_width,&def_cycle,&def_smoother,&stencil_type);
  } else {
    mgt_alloc(&dm, &m_nlevel, &i_nodal);
    mgt_set_defaults(&def_nu_1,&def_nu_2,&def_nu_b,&def_nu_f,&def_gamma,&def_omega,
                     &def_maxiter,&def_maxiter_b,&def_bottom_solver,&def_bottom_solver_eps,
                     &def_verbose,&def_cg_verbose,&def_max_nlevel,
                     &def_min_width,&def_cycle,&def_smoother,&stencil_type);
  }

  Array<int> pm(dm);
  for ( int i = 0; i < dm; ++i ) 
    {
      pm[i] = geom[0].isPeriodic(i)? 1 : 0;
    }

  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      const Array<int>& pmap = dmap[lev].ProcessorMap();
      Box domain = geom[lev].Domain();

      int nb = grids[lev].size();
      std::vector<int> lo(nb*dm);
      std::vector<int> hi(nb*dm);

      for ( int i = 0; i < nb; ++i )
      {
        for ( int j = 0; j < dm; ++j )
	{
	  lo[i + j*nb] = m_grids[lev][i].smallEnd(j);
	  hi[i + j*nb] = m_grids[lev][i].bigEnd(j);
	}
      }

      if (nodal) {
        mgt_set_nodal_level(&lev, &nb, &dm, &lo[0], &hi[0], 
  		            domain.loVect(), domain.hiVect(), pm.dataPtr(), &pmap[0]);
      } else {
        mgt_set_level(&lev, &nb, &dm, &lo[0], &hi[0], 
  		      domain.loVect(), domain.hiVect(), pm.dataPtr(), &pmap[0]);
      }
    }

  std::vector<Real> dx(m_nlevel*dm);
  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      for ( int j = 0; j < dm; ++j )
	{
	  dx[lev + j*m_nlevel] = geom[lev].CellSize()[j];
	}
    }

  if (nodal) {
    mgt_nodal_finalize(&dx[0],&bc[0]);
  } else {
    //mgt_finalize_n(&dx[0],&bc[0],&nc,&ncomp);
    mgt_finalize(&dx[0],&bc[0]);
  }
}


void
MGT_Solver::initialize(bool nodal)
{
    initialized = true;

    mgt_init();

    if (nodal) {
      mgt_get_nodal_defaults(&def_nu_1,&def_nu_2,&def_nu_b,&def_nu_f,&def_gamma,&def_omega,
                             &def_maxiter,&def_maxiter_b,&def_bottom_solver,
                             &def_verbose,&def_cg_verbose,&def_max_nlevel,&def_min_width,&def_cycle,&def_smoother);
      def_nu_b = 2;
    } else {
      mgt_get_defaults(&def_nu_1,&def_nu_2,&def_nu_b,&def_nu_f,&def_gamma,&def_omega,
                       &def_maxiter,&def_maxiter_b,&def_bottom_solver,
                       &def_verbose,&def_cg_verbose,&def_max_nlevel,&def_min_width,&def_cycle,&def_smoother);
    }

    /* SET TO AGREE WITH MULTIGRID DEFAULT */
    def_min_width = 2;
    def_usecg = 1;
    def_cg_solver = 1;
    def_bottom_solver_eps = 0.0001;
    def_nu_f = 2;

    /* SET TO AGREE WITH MULTIGRID DEFAULT */
    stencil_type = 1;  /* 1: ST_CROSS */

    ParmParse pp("mg");

    pp.query("maxiter", def_maxiter);
    pp.query("maxiter_b", def_maxiter_b);
    pp.query("nu_1", def_nu_1);
    pp.query("nu_2", def_nu_2);
    pp.query("nu_b", def_nu_b);
    pp.query("nu_f", def_nu_f);
    pp.query("v"   , def_verbose);
    pp.query("usecg", def_usecg);
    pp.query("cg_solver", def_cg_solver);
    pp.query("rtol_b", def_bottom_solver_eps);
    pp.query("numLevelsMAX", def_max_nlevel);

    pp.query("stencil_type", stencil_type);

/*
    pp.query("nu_0", def_nu_0);
    pp.query("bot_atol", def_atol_b);
    pp.query("smooth_on_cg_unstable", def_smooth_on_cg_unstable);
*/

    {
    ParmParse pp("cg");
    pp.query("v"   , def_cg_verbose);
    }

    if (def_usecg == 1) {
      if (def_cg_solver == 1) {
        def_bottom_solver = 1;
      } else if (def_cg_solver == 0) {
        def_bottom_solver = 2;
      }
    } else {
      def_bottom_solver = 3;
    }

    pp.query("bottom_solver", def_bottom_solver);
}


void
MGT_Solver::set_mac_coefficients(const MultiFab* aa[], 
                                 const MultiFab* bb[][BL_SPACEDIM], 
                                 Array< Array<Real> >& xa,
                                 Array< Array<Real> >& xb)
{
  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      mgt_init_coeffs_lev(&lev);
      double pxa[BL_SPACEDIM], pxb[BL_SPACEDIM];

      for ( int i = 0; i < BL_SPACEDIM; ++i ) 
	{
	  pxa[i] = pxb[i] = 0;
	}

      Real beta = 1.0;

//    NOTE: we only pass in aa here in order to get the validbox.
      for (MFIter amfi(*(aa[lev])); amfi.isValid(); ++amfi)
	{
	  const FArrayBox* b[BL_SPACEDIM];

	  int n = amfi.index();

	  for ( int i = 0; i < BL_SPACEDIM; ++i )
	    {
	      b[i] = &((*(bb[lev][i]))[amfi]);
	    }

 	   const int* lo = amfi.validbox().loVect();
	   const int* hi = amfi.validbox().hiVect();

	   const int* bxlo = b[0]->box().loVect();
	   const int* bxhi = b[0]->box().hiVect();
	   mgt_set_cfbx(&lev, &n, b[0]->dataPtr(), &beta, bxlo, bxhi, lo, hi);

#if (BL_SPACEDIM >= 2)
	   const int* bylo = b[1]->box().loVect();
	   const int* byhi = b[1]->box().hiVect();
	   mgt_set_cfby(&lev, &n, b[1]->dataPtr(), &beta, bylo, byhi, lo, hi);
#endif

#if (BL_SPACEDIM == 3)
           const int* bzlo = b[2]->box().loVect();
  	   const int* bzhi = b[2]->box().hiVect();
  	   mgt_set_cfbz(&lev, &n, b[2]->dataPtr(), &beta, bzlo, bzhi, lo, hi);
#endif
	}
      int dm = BL_SPACEDIM;
      mgt_finalize_stencil_lev(&lev, xa[lev].dataPtr(), xb[lev].dataPtr(), pxa, pxb, &dm);
    }
  mgt_finalize_stencil();
}

void
MGT_Solver::set_gravity_coefficients(Array< PArray<MultiFab> >& coeffs,
                                     Array< Array<Real> >& xa,
                                     Array< Array<Real> >& xb,
                                     int is_constant)
{
  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      mgt_init_coeffs_lev(&lev);
      double pxa[BL_SPACEDIM], pxb[BL_SPACEDIM];

      for ( int i = 0; i < BL_SPACEDIM; ++i ) 
	{
	  pxa[i] = pxb[i] = 0;
	}

//    NOTE: the sign convention is because the elliptic solver solves
//           (alpha MINUS del dot beta grad) phi = RHS
//           Here alpha is zero and we want to solve del dot grad phi = RHS,
//             which is equivalent to MINUS del dot (MINUS ONE) grad phi = RHS.
      Real value_zero =  0.0;
      Real value_one  = -1.0;

      for (MFIter mfi((coeffs[lev][0])); mfi.isValid(); ++mfi)
        {
           int n = mfi.index();
           const int* lo = m_grids[lev][n].loVect();
           const int* hi = m_grids[lev][n].hiVect();

           mgt_set_cfa_const (&lev, &n, lo, hi, &value_zero);
 
           if (is_constant == 1) {
              mgt_set_cfbx_const(&lev, &n, lo, hi, &value_one);
           } else {
              const int* bxlo = coeffs[lev][0][n].box().loVect();
              const int* bxhi = coeffs[lev][0][n].box().hiVect();
   	      mgt_set_cfbx(&lev, &n, coeffs[lev][0][n].dataPtr(), &value_one, bxlo, bxhi, lo, hi);
           }
 
#if (BL_SPACEDIM >= 2) 
           if (is_constant == 1) {
              mgt_set_cfby_const(&lev, &n, lo, hi, &value_one);
           } else {
              const int* bylo = coeffs[lev][1][n].box().loVect(); 
              const int* byhi = coeffs[lev][1][n].box().hiVect();
   	      mgt_set_cfby(&lev, &n, coeffs[lev][1][n].dataPtr(), &value_one, bylo, byhi, lo, hi);
           }
#endif
 
#if (BL_SPACEDIM == 3)
           if (is_constant == 1) {
              mgt_set_cfbz_const(&lev, &n, lo, hi, &value_one);
           } else {
              const int* bzlo = coeffs[lev][2][n].box().loVect();
              const int* bzhi = coeffs[lev][2][n].box().hiVect();
	      mgt_set_cfbz(&lev, &n, coeffs[lev][2][n].dataPtr(), &value_one, bzlo, bzhi, lo, hi);
           }
#endif
        }

      int dm = BL_SPACEDIM;
      mgt_finalize_stencil_lev(&lev, xa[lev].dataPtr(), xb[lev].dataPtr(), pxa, pxb, &dm);
    }

  mgt_finalize_stencil();
}

void
MGT_Solver::set_visc_coefficients(PArray<MultiFab>& aa, 
				  Array<PArray<MultiFab> >& bb, 
                                  const Real& beta, 
                                  Array< Array<Real> >& xa,
                                  Array< Array<Real> >& xb)
{
  for ( int lev = 0; lev < m_nlevel; ++lev )
  {
    mgt_init_coeffs_lev(&lev);

    double pxa[BL_SPACEDIM], pxb[BL_SPACEDIM];

    for ( int i = 0; i < BL_SPACEDIM; ++i ) 
      pxa[i] = pxb[i] = 0.;
  
    for (MFIter amfi(aa[lev]); amfi.isValid(); ++amfi)
    {      
      int n = amfi.index();

      const FArrayBox& a = aa[lev][amfi];
      const int* lo = amfi.validbox().loVect();
      const int* hi = amfi.validbox().hiVect();
      
      const int* alo = a.box().loVect();
      const int* ahi = a.box().hiVect();
      mgt_set_cfa (&lev, &n, a.dataPtr(), alo, ahi, lo, hi);

      const FArrayBox& bx = bb[0][lev][amfi];
      const int* bxlo = bx.box().loVect();
      const int* bxhi = bx.box().hiVect();
      mgt_set_cfbx(&lev, &n, bx.dataPtr(), &beta, bxlo, bxhi, lo, hi);

#if (BL_SPACEDIM >= 2)
      const FArrayBox& by = bb[1][lev][amfi];
      const int* bylo = by.box().loVect();
      const int* byhi = by.box().hiVect();
      mgt_set_cfby(&lev, &n, by.dataPtr(), &beta, bylo, byhi, lo, hi);
#endif

#if (BL_SPACEDIM == 3)
      const FArrayBox& bz = bb[2][lev][amfi];
      const int* bzlo = bz.box().loVect();
      const int* bzhi = bz.box().hiVect();
      mgt_set_cfbz(&lev, &n, bz.dataPtr(), &beta, bzlo, bzhi, lo, hi);
#endif
    }
    int dm = BL_SPACEDIM;
    mgt_finalize_stencil_lev(&lev, xa[lev].dataPtr(), xb[lev].dataPtr(), pxa, pxb, &dm);
  }
  mgt_finalize_stencil();
}

void
MGT_Solver::set_visc_coefficients(const MultiFab* aa[], const MultiFab* bb[][BL_SPACEDIM], 
                                  const Real& beta, 
                                  Array< Array<Real> >& xa,
                                  Array< Array<Real> >& xb)
{
  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      mgt_init_coeffs_lev(&lev);

      double pxa[BL_SPACEDIM], pxb[BL_SPACEDIM];

      for ( int i = 0; i < BL_SPACEDIM; ++i ) 
	{
	  pxa[i] = pxb[i] = 0.;
	}

      for (MFIter amfi(*(aa[lev])); amfi.isValid(); ++amfi)
	{
	  const FArrayBox* a = &((*(aa[lev]))[amfi]);
	  const FArrayBox* b[BL_SPACEDIM];

	  int n = amfi.index();

	  for ( int i = 0; i < BL_SPACEDIM; ++i )
	    {
	      b[i] = &((*(bb[lev][i]))[amfi]);
	    }
 	   
 	   const int* lo = amfi.validbox().loVect();
	   const int* hi = amfi.validbox().hiVect();

	   const int* alo = a->box().loVect();
	   const int* ahi = a->box().hiVect();
	   mgt_set_cfa (&lev, &n, a->dataPtr(), alo, ahi, lo, hi);

	   const int* bxlo = b[0]->box().loVect();
	   const int* bxhi = b[0]->box().hiVect();
	   mgt_set_cfbx(&lev, &n, b[0]->dataPtr(), &beta, bxlo, bxhi, lo, hi);

#if (BL_SPACEDIM >= 2)
	   const int* bylo = b[1]->box().loVect();
	   const int* byhi = b[1]->box().hiVect();
	   mgt_set_cfby(&lev, &n, b[1]->dataPtr(), &beta, bylo, byhi, lo, hi);
#endif

#if (BL_SPACEDIM == 3)
           const int* bzlo = b[2]->box().loVect();
  	   const int* bzhi = b[2]->box().hiVect();
  	   mgt_set_cfbz(&lev, &n, b[2]->dataPtr(), &beta, bzlo, bzhi, lo, hi);
#endif
	}
      int dm = BL_SPACEDIM;
      mgt_finalize_stencil_lev(&lev, xa[lev].dataPtr(), xb[lev].dataPtr(), pxa, pxb, &dm);
    }
  mgt_finalize_stencil();
}

void
MGT_Solver::set_visc_coefficients(MultiFab* aa[], MultiFab* bb[][BL_SPACEDIM], 
                                  const Real& beta, 
                                  Array< Array<Real> >& xa,
                                  Array< Array<Real> >& xb)
{
  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      mgt_init_coeffs_lev(&lev);

      double pxa[BL_SPACEDIM], pxb[BL_SPACEDIM];

      for ( int i = 0; i < BL_SPACEDIM; ++i ) 
	{
	  pxa[i] = pxb[i] = 0.;
	}

      for (MFIter amfi(*(aa[lev])); amfi.isValid(); ++amfi)
	{
	  const FArrayBox* a = &((*(aa[lev]))[amfi]);
	  const FArrayBox* b[BL_SPACEDIM];

	  int n = amfi.index();

	  for ( int i = 0; i < BL_SPACEDIM; ++i )
	    {
	      b[i] = &((*(bb[lev][i]))[amfi]);
	    }
 	   
 	   const int* lo = amfi.validbox().loVect();
	   const int* hi = amfi.validbox().hiVect();

	   const int* alo = a->box().loVect();
	   const int* ahi = a->box().hiVect();
	   mgt_set_cfa (&lev, &n, a->dataPtr(), alo, ahi, lo, hi);

	   const int* bxlo = b[0]->box().loVect();
	   const int* bxhi = b[0]->box().hiVect();
	   mgt_set_cfbx(&lev, &n, b[0]->dataPtr(), &beta, bxlo, bxhi, lo, hi);

#if (BL_SPACEDIM >= 2)
	   const int* bylo = b[1]->box().loVect();
	   const int* byhi = b[1]->box().hiVect();
	   mgt_set_cfby(&lev, &n, b[1]->dataPtr(), &beta, bylo, byhi, lo, hi);
#endif

#if (BL_SPACEDIM == 3)
           const int* bzlo = b[2]->box().loVect();
  	   const int* bzhi = b[2]->box().hiVect();
  	   mgt_set_cfbz(&lev, &n, b[2]->dataPtr(), &beta, bzlo, bzhi, lo, hi);
#endif
	}
      int dm = BL_SPACEDIM;
      mgt_finalize_stencil_lev(&lev, xa[lev].dataPtr(), xb[lev].dataPtr(), pxa, pxb, &dm);
    }
  mgt_finalize_stencil();
}


void MGT_Solver::set_maxorder(const int max_order)
{
  mgt_set_maxorder(&max_order);
}

void
MGT_Solver::set_porous_coefficients(PArray<MultiFab>& a1, 
				    PArray<MultiFab>& a2, 
                                    Array<PArray<MultiFab> >& bb, 
                                    const Real& beta, 
                                    Array< Array<Real> >& xa, 
				    Array< Array<Real> >& xb,
                                    int nc_opt)
{
  int nc = bb[0][0].nComp();
  for ( int lev = 0; lev < m_nlevel; ++lev )
  {
    mgt_init_mc_coeffs_lev(&lev,&nc,&nc_opt);
     
    double pxa[BL_SPACEDIM], pxb[BL_SPACEDIM];
    for ( int i = 0; i < BL_SPACEDIM; ++i ) 
      pxa[i] = pxb[i] = 0;
   
    for (MFIter amfi(a1[lev]); amfi.isValid(); ++amfi)
    {
      int n = amfi.index();

      const FArrayBox& af1 = a1[lev][amfi];
      const int* lo = amfi.validbox().loVect();
      const int* hi = amfi.validbox().hiVect();
	  
      const int* a1lo = af1.box().loVect();
      const int* a1hi = af1.box().hiVect();

      mgt_set_cfa (&lev, &n, af1.dataPtr(), a1lo, a1hi, lo, hi);
     
      if (nc_opt == 0)
      {
	FArrayBox& af2 = a2[lev][amfi];
	const int* a2lo = af2.box().loVect();
	const int* a2hi = af2.box().hiVect();
	mgt_set_cfa2 (&lev, &n, af2.dataPtr(), a2lo, a2hi, lo, hi, a2[lev].nComp());
      }
      const FArrayBox& bx = bb[0][lev][amfi];
      const int* bxlo = bx.box().loVect();
      const int* bxhi = bx.box().hiVect();
      mgt_set_cfbnx(&lev, &n, bx.dataPtr(), &beta, bxlo, bxhi, lo, hi, bx.nComp());

#if (BL_SPACEDIM >= 2)
      const FArrayBox& by = bb[1][lev][amfi];
      const int* bylo = by.box().loVect();
      const int* byhi = by.box().hiVect();
      mgt_set_cfbny(&lev, &n, by.dataPtr(), &beta, bylo, byhi, lo, hi, by.nComp());
#endif

#if (BL_SPACEDIM == 3)
      const FArrayBox& bz = bb[2][lev][amfi];
      const int* bzlo = bz.box().loVect();
      const int* bzhi =  bz.box().hiVect();
      mgt_set_cfbnz(&lev, &n, bz.dataPtr(), &beta, bzlo, bzhi, lo, hi, bz.nComp());
#endif
    }
    int dm = BL_SPACEDIM;
    mgt_mc_finalize_stencil_lev(&lev, xa[lev].dataPtr(), xb[lev].dataPtr(), 
				pxa, pxb, &dm, &nc_opt);
  }
  mgt_finalize_stencil();
}

void
MGT_Solver::set_porous_coefficients(const MultiFab* a1[], const MultiFab* a2[], 
                                    const MultiFab* bb[][BL_SPACEDIM], 
                                    const Real& beta, 
                                    Array< Array<Real> >& xa, 
				    Array< Array<Real> >& xb,
                                    int nc_opt)
{
  int nc = (*bb[0][0]).nComp();
  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      mgt_init_mc_coeffs_lev(&lev,&nc,&nc_opt);
      double pxa[BL_SPACEDIM], pxb[BL_SPACEDIM];

      for ( int i = 0; i < BL_SPACEDIM; ++i ) 
	{
	  pxa[i] = pxb[i] = 0;
	}

      for (MFIter amfi(*(a1[lev])); amfi.isValid(); ++amfi)
	{
	  const FArrayBox* af1 = &((*(a1[lev]))[amfi]);
	  const FArrayBox* b[BL_SPACEDIM];

	  int n = amfi.index();

	  for ( int i = 0; i < BL_SPACEDIM; ++i )
	  {
	    b[i] = &((*(bb[lev][i]))[amfi]);
	  }

	  const int* lo = amfi.validbox().loVect();
	  const int* hi = amfi.validbox().hiVect();
	  
	  const int* a1lo = af1->box().loVect();
	  const int* a1hi = af1->box().hiVect();
	  mgt_set_cfa (&lev, &n, af1->dataPtr(), a1lo, a1hi, lo, hi);
	  
	  if (nc_opt == 0)
	  {
	    const FArrayBox* af2 = &((*(a2[lev]))[amfi]);
	    const int* a2lo = af2->box().loVect();
	    const int* a2hi = af2->box().hiVect();
	    mgt_set_cfa2 (&lev, &n, af2->dataPtr(), a2lo, a2hi, lo, hi, a2[0]->nComp());
	  }

	  const int* bxlo = b[0]->box().loVect();
	  const int* bxhi = b[0]->box().hiVect();
	  mgt_set_cfbnx(&lev, &n, b[0]->dataPtr(), &beta, bxlo, bxhi, lo, hi, b[0]->nComp());

#if (BL_SPACEDIM >= 2)
	  const int* bylo = b[1]->box().loVect();
	  const int* byhi = b[1]->box().hiVect();
	  mgt_set_cfbny(&lev, &n, b[1]->dataPtr(), &beta, bylo, byhi, lo, hi, b[1]->nComp());
#endif

#if (BL_SPACEDIM == 3)
	  const int* bzlo = b[2]->box().loVect();
	  const int* bzhi = b[2]->box().hiVect();
	  mgt_set_cfbnz(&lev, &n, b[2]->dataPtr(), &beta, bzlo, bzhi, lo, hi, b[2]->nComp());
#endif
	}
      int dm = BL_SPACEDIM;
      
      mgt_mc_finalize_stencil_lev(&lev, xa[lev].dataPtr(), xb[lev].dataPtr(), 
				  pxa, pxb, &dm, &nc_opt);
    }
  mgt_finalize_stencil();
}

void
MGT_Solver::set_porous_coefficients(MultiFab* a1[], const  MultiFab* a2[], 
                                    MultiFab* bb[][BL_SPACEDIM], 
                                    const Real& beta, 
				    Array< Array<Real> >& xa,
				    Array< Array<Real> >& xb,
				    int nc_opt)
{
  int nc = (*bb[0][0]).nComp();
  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      mgt_init_mc_coeffs_lev(&lev,&nc,&nc_opt);
      double pxa[BL_SPACEDIM], pxb[BL_SPACEDIM];

      for ( int i = 0; i < BL_SPACEDIM; ++i ) 
	{
	  pxa[i] = pxb[i] = 0;
	}

      for (MFIter amfi(*(a1[lev])); amfi.isValid(); ++amfi)
	{
	  const FArrayBox* af1 = &((*(a1[lev]))[amfi]);
	  
	  const FArrayBox* b[BL_SPACEDIM];
	  for ( int i = 0; i < BL_SPACEDIM; ++i )
	    {
	      b[i] = &((*(bb[lev][i]))[amfi]);
	    }

 	   int n = amfi.index();
 	   const int* lo = amfi.validbox().loVect();
	   const int* hi = amfi.validbox().hiVect();

	   const int* a1lo = af1->box().loVect();
	   const int* a1hi = af1->box().hiVect();
	   mgt_set_cfa (&lev, &n, af1->dataPtr(), a1lo, a1hi, lo, hi);

	   if (nc_opt == 0)
	   {
	     const FArrayBox* af2 = &((*(a2[lev]))[amfi]);
	     const int* a2lo = af2->box().loVect();
	     const int* a2hi = af2->box().hiVect();
	     mgt_set_cfa2 (&lev, &n, af2->dataPtr(), a2lo, a2hi, lo, hi, a2[0]->nComp());
	   }

	   const int* bxlo = b[0]->box().loVect();
	   const int* bxhi = b[0]->box().hiVect();
	   mgt_set_cfbnx(&lev, &n, b[0]->dataPtr(), &beta, bxlo, bxhi, lo, hi, b[0]->nComp());


#if (BL_SPACEDIM >= 2)
	   const int* bylo = b[1]->box().loVect();
	   const int* byhi = b[1]->box().hiVect();
	   mgt_set_cfbny(&lev, &n, b[1]->dataPtr(), &beta, bylo, byhi, lo, hi, b[1]->nComp());
#endif

#if (BL_SPACEDIM == 3)
           const int* bzlo = b[2]->box().loVect();
  	   const int* bzhi = b[2]->box().hiVect();
  	   mgt_set_cfbnz(&lev, &n, b[2]->dataPtr(), &beta, bzlo, bzhi, lo, hi, b[2]->nComp());
#endif
	}
      int dm = BL_SPACEDIM;
      mgt_mc_finalize_stencil_lev(&lev, xa[lev].dataPtr(), xb[lev].dataPtr(), 
				  pxa, pxb, &dm, &nc_opt);
    }
  mgt_finalize_stencil();
}


void
MGT_Solver::set_nodal_coefficients(const MultiFab* sig[])
{
  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      mgt_init_nodal_coeffs_lev(&lev);

      for (MFIter smfi(*(sig[lev])); smfi.isValid(); ++smfi)
	{
	  const FArrayBox* s = &((*(sig[lev]))[smfi]);
 	  int n = smfi.index();
 	  const int* lo = smfi.validbox().loVect();
	  const int* hi = smfi.validbox().hiVect();

	  const int* slo = s->box().loVect();
	  const int* shi = s->box().hiVect();
	  mgt_set_cfs (&lev, &n, s->dataPtr(), slo, shi, lo, hi);
	}
      mgt_finalize_nodal_stencil_lev(&lev);
    }
  mgt_finalize_nodal_stencil();
}

void 
MGT_Solver::solve(MultiFab* uu[], MultiFab* rh[], const Real& tol, const Real& abs_tol,
                  const BndryData& bd, Real& final_resnorm)
{
  solve(uu,rh,tol,abs_tol,bd,0,final_resnorm);
}

void 
MGT_Solver::solve(MultiFab* uu[], MultiFab* rh[], const Real& tol, const Real& abs_tol,
                  const BndryData& bd, int need_grad_phi, Real& final_resnorm)
{
  // Copy the boundary register values into the solution array to be copied into F90
  int lev = 0;
  for (OrientationIter oitr; oitr; ++oitr)
  {
      const FabSet& fs = bd.bndryValues(oitr());
      for (MFIter umfi(*(uu[lev])); umfi.isValid(); ++umfi)
      {
        FArrayBox& dest = (*(uu[lev]))[umfi];
        dest.copy(fs[umfi],fs[umfi].box());
      }
  }
  uu[lev]->FillBoundary();

  
  
  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      for (MFIter umfi(*(uu[lev])); umfi.isValid(); ++umfi)
	{
	  int n = umfi.index();

	  const int* lo = umfi.validbox().loVect();
	  const int* hi = umfi.validbox().hiVect();

	  const FArrayBox& rhs = (*(rh[lev]))[umfi];
	  const Real* rd = rhs.dataPtr();
	  const int* rlo = rhs.box().loVect();
	  const int* rhi = rhs.box().hiVect();
	  mgt_set_rh(&lev, &n, rd, rlo, rhi, lo, hi);

	  const FArrayBox& sol = (*(uu[lev]))[umfi];
	  const Real* sd = sol.dataPtr();
	  const int* slo = sol.box().loVect();
	  const int* shi = sol.box().hiVect();
	  mgt_set_uu(&lev, &n, sd, slo, shi, lo, hi);
	}
    }
  mgt_solve(tol,abs_tol,&need_grad_phi,&final_resnorm);

  int ng = 0;
  if (need_grad_phi == 1) ng = 1;

  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      for (MFIter umfi(*(uu[lev])); umfi.isValid(); ++umfi)
	{
	  FArrayBox& sol = (*(uu[lev]))[umfi];
	  Real* sd = sol.dataPtr();
	  int n = umfi.index();
	  const int* lo = umfi.validbox().loVect();
	  const int* hi = umfi.validbox().hiVect();
	  const int* plo = sol.box().loVect();
	  const int* phi = sol.box().hiVect();
	  mgt_get_uu(&lev, &n, sd, plo, phi, lo, hi, &ng);
	}
    }
}

void 
MGT_Solver::solve(MultiFab* uu[], MultiFab* rh[], const Real& tol, const Real& abs_tol,
                  const BndryData bd[], int need_grad_phi, Real& final_resnorm)
{
  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      // Copy the boundary register values into the solution array to
      // be copied into F90
      
      for (OrientationIter oitr; oitr; ++oitr)
	{
	  const FabSet& fs = bd[lev].bndryValues(oitr());
	  for (MFIter umfi(*(uu[lev])); umfi.isValid(); ++umfi)
	    {
	      FArrayBox& dest = (*(uu[lev]))[umfi];
	      dest.copy(fs[umfi],fs[umfi].box());
	    }
	}
    }

  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      for (MFIter umfi(*(uu[lev])); umfi.isValid(); ++umfi)
	{
	  int n = umfi.index();

	  const int* lo = umfi.validbox().loVect();
	  const int* hi = umfi.validbox().hiVect();

	  const FArrayBox& rhs = (*(rh[lev]))[umfi];
	  const Real* rd = rhs.dataPtr();
	  const int* rlo = rhs.box().loVect();
	  const int* rhi = rhs.box().hiVect();
	  mgt_set_rh(&lev, &n, rd, rlo, rhi, lo, hi);

	  const FArrayBox& sol = (*(uu[lev]))[umfi];
	  const Real* sd = sol.dataPtr();
	  const int* slo = sol.box().loVect();
	  const int* shi = sol.box().hiVect();
	  mgt_set_uu(&lev, &n, sd, slo, shi, lo, hi);
	}
    }
  mgt_solve(tol,abs_tol,&need_grad_phi,&final_resnorm);

  int ng = 0;
  if (need_grad_phi == 1) ng = 1;

  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      for (MFIter umfi(*(uu[lev])); umfi.isValid(); ++umfi)
	{
	  FArrayBox& sol = (*(uu[lev]))[umfi];
	  Real* sd = sol.dataPtr();
	  int n = umfi.index();
	  const int* lo = umfi.validbox().loVect();
	  const int* hi = umfi.validbox().hiVect();
	  const int* plo = sol.box().loVect();
	  const int* phi = sol.box().hiVect();
	  mgt_get_uu(&lev, &n, sd, plo, phi, lo, hi, &ng);
	}
    }
}
 
void 
MGT_Solver::solve(MultiFab* uu[], MultiFab* rh[], const Real& tol, const Real& abs_tol,
                  int need_grad_phi, Real& final_resnorm)
{
  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      for (MFIter umfi(*(uu[lev])); umfi.isValid(); ++umfi)
	{
	  int n = umfi.index();

	  const int* lo = umfi.validbox().loVect();
	  const int* hi = umfi.validbox().hiVect();

	  const FArrayBox& rhs = (*(rh[lev]))[umfi];
	  const Real* rd = rhs.dataPtr();
	  const int* rlo = rhs.box().loVect();
	  const int* rhi = rhs.box().hiVect();
	  mgt_set_rh(&lev, &n, rd, rlo, rhi, lo, hi);

	  const FArrayBox& sol = (*(uu[lev]))[umfi];
	  const Real* sd = sol.dataPtr();
	  const int* slo = sol.box().loVect();
	  const int* shi = sol.box().hiVect();
	  mgt_set_uu(&lev, &n, sd, slo, shi, lo, hi);
	}
    }
  mgt_solve(tol,abs_tol,&need_grad_phi,&final_resnorm);

  int ng = 0;
  if (need_grad_phi == 1) ng = 1;

  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      for (MFIter umfi(*(uu[lev])); umfi.isValid(); ++umfi)
	{
	  FArrayBox& sol = (*(uu[lev]))[umfi];
	  Real* sd = sol.dataPtr();
	  int n = umfi.index();
	  const int* lo = umfi.validbox().loVect();
	  const int* hi = umfi.validbox().hiVect();
	  const int* plo = sol.box().loVect();
	  const int* phi = sol.box().hiVect();
	  mgt_get_uu(&lev, &n, sd, plo, phi, lo, hi, &ng);
	}
    }
}

void 
MGT_Solver::applyop(MultiFab* uu[], MultiFab* res[], const BndryData& bd)
{
  // Copy the boundary register values into the solution array to be copied into F90
  int lev = 0;
  for (OrientationIter oitr; oitr; ++oitr)
  {
      const FabSet& fs = bd.bndryValues(oitr());
      for (MFIter umfi(*(uu[lev])); umfi.isValid(); ++umfi)
      {
        FArrayBox& dest = (*(uu[lev]))[umfi];
        dest.copy(fs[umfi],fs[umfi].box());
      }
  }
  uu[lev]->FillBoundary();

  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      for (MFIter umfi(*(uu[lev])); umfi.isValid(); ++umfi)
	{
	  int n = umfi.index();

	  const int* lo = umfi.validbox().loVect();
	  const int* hi = umfi.validbox().hiVect();

	  const FArrayBox& sol = (*(uu[lev]))[umfi];
	  const Real* sd = sol.dataPtr();
	  const int* slo = sol.box().loVect();
	  const int* shi = sol.box().hiVect();
	  mgt_set_uu(&lev, &n, sd, slo, shi, lo, hi);
	}
    }

  mgt_applyop();

  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      for (MFIter mfi(*(res[lev])); mfi.isValid(); ++mfi)
	{
	  FArrayBox& resfab = (*(res[lev]))[mfi];
	  Real* rd = resfab.dataPtr();
	  int n = mfi.index();
	  const int* lo = mfi.validbox().loVect();
	  const int* hi = mfi.validbox().hiVect();
	  const int* rlo = resfab.box().loVect();
	  const int* rhi = resfab.box().hiVect();
	  mgt_get_res(&lev, &n, rd, rlo, rhi, lo, hi);
	}
    }
}

void 
MGT_Solver::applyop(MultiFab* uu[], MultiFab* res[], const BndryData bd[])
{
  // Copy the boundary register values into the solution array to be
  // copied into F90
  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      // Copy the boundary register values into the solution array to be copied into F90
      for (OrientationIter oitr; oitr; ++oitr)
	{
	  const FabSet& fs = bd[lev].bndryValues(oitr());
	  for (MFIter umfi(*(uu[lev])); umfi.isValid(); ++umfi)
	    {
	      FArrayBox& dest = (*(uu[lev]))[umfi];
	      dest.copy(fs[umfi],fs[umfi].box());
	    }
	}
      uu[lev]->FillBoundary();
    }

  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      for (MFIter umfi(*(uu[lev])); umfi.isValid(); ++umfi)
	{
	  int n = umfi.index();

	  const int* lo = umfi.validbox().loVect();
	  const int* hi = umfi.validbox().hiVect();

	  const FArrayBox& sol = (*(uu[lev]))[umfi];
	  const Real* sd = sol.dataPtr();
	  const int* slo = sol.box().loVect();
	  const int* shi = sol.box().hiVect();
	  mgt_set_uu(&lev, &n, sd, slo, shi, lo, hi);
	}
    }

  mgt_applyop();

  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      for (MFIter mfi(*(res[lev])); mfi.isValid(); ++mfi)
	{
	  FArrayBox& resfab = (*(res[lev]))[mfi];
	  Real* rd = resfab.dataPtr();
	  int n = mfi.index();
	  const int* lo = mfi.validbox().loVect();
	  const int* hi = mfi.validbox().hiVect();
	  const int* rlo = resfab.box().loVect();
	  const int* rhi = resfab.box().hiVect();
	  mgt_get_res(&lev, &n, rd, rlo, rhi, lo, hi);
	}
    }
}

void 
MGT_Solver::applybc(MultiFab* uu[], const BndryData& bd)
{
  // Copy the boundary register values into the solution array to be copied into F90
  int lev = 0;
  for (OrientationIter oitr; oitr; ++oitr)
  {
      const FabSet& fs = bd.bndryValues(oitr());
      for (MFIter umfi(*(uu[lev])); umfi.isValid(); ++umfi)
      {
        FArrayBox& dest = (*(uu[lev]))[umfi];
        dest.copy(fs[umfi],fs[umfi].box());
      }
  }
  uu[lev]->FillBoundary();

  for ( int lev = 0; lev < m_nlevel; ++lev )
  {
    for (MFIter umfi(*(uu[lev])); umfi.isValid(); ++umfi)
    {
      FArrayBox& sol = (*(uu[lev]))[umfi];
      Real* sd = sol.dataPtr();
      int n = umfi.index();
      const int* lo = umfi.validbox().loVect();
      const int* hi = umfi.validbox().hiVect();
      const int* plo = sol.box().loVect();
      const int* phi = sol.box().hiVect();
      mgt_set_uu(&lev, &n, sd, plo, phi, lo, hi);
    }
  }
}

void 
MGT_Solver::compute_residual(MultiFab* uu[], MultiFab* rh[], MultiFab* res[], const BndryData& bd)
{
  // Copy the boundary register values into the solution array to be copied into F90
  int lev = 0;
  for (OrientationIter oitr; oitr; ++oitr)
  {
      const FabSet& fs = bd.bndryValues(oitr());
      for (MFIter umfi(*(uu[lev])); umfi.isValid(); ++umfi)
      {
        FArrayBox& dest = (*(uu[lev]))[umfi];
        dest.copy(fs[umfi],fs[umfi].box());
      }
  }

  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      for (MFIter umfi(*(uu[lev])); umfi.isValid(); ++umfi)
	{
	  int n = umfi.index();

	  const int* lo = umfi.validbox().loVect();
	  const int* hi = umfi.validbox().hiVect();

	  const FArrayBox& rhs = (*(rh[lev]))[umfi];
	  const Real* rd = rhs.dataPtr();
	  const int* rlo = rhs.box().loVect();
	  const int* rhi = rhs.box().hiVect();
	  mgt_set_rh(&lev, &n, rd, rlo, rhi, lo, hi);

	  const FArrayBox& sol = (*(uu[lev]))[umfi];
	  const Real* sd = sol.dataPtr();
	  const int* slo = sol.box().loVect();
	  const int* shi = sol.box().hiVect();
	  mgt_set_uu(&lev, &n, sd, slo, shi, lo, hi);
	}
    }

  mgt_compute_residual();

  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      for (MFIter mfi(*(res[lev])); mfi.isValid(); ++mfi)
	{
	  FArrayBox& resfab = (*(res[lev]))[mfi];
	  Real* rd = resfab.dataPtr();
	  int n = mfi.index();
	  const int* lo = mfi.validbox().loVect();
	  const int* hi = mfi.validbox().hiVect();
	  const int* rlo = resfab.box().loVect();
	  const int* rhi = resfab.box().hiVect();
	  mgt_get_res(&lev, &n, rd, rlo, rhi, lo, hi);
	}
    }
}

void 
MGT_Solver::get_fluxes(int lev, PArray<MultiFab>& flux, const Real* dx)
{
  mgt_compute_flux(lev);

  for ( int dir = 0; dir < BL_SPACEDIM; ++dir )
    {
      for (MFIter mfi(flux[dir]); mfi.isValid(); ++mfi)
        {
          FArrayBox& gp = flux[dir][mfi];
          Real* gpd = gp.dataPtr();

          int n = mfi.index();
          const int* lo = mfi.validbox().loVect();
          const int* hi = mfi.validbox().hiVect();
          const int* gplo = gp.box().loVect();
          const int* gphi = gp.box().hiVect();

          mgt_get_gp(&lev, &dir, &n, gpd, gplo, gphi, lo, hi);
          gp.mult(dx[dir]);
        }
    }

  mgt_delete_flux(lev);
}

void 
MGT_Solver::get_fluxes(int lev, 
		       MultiFab* const* flux, 
		       const Real* dx)
{
  mgt_compute_flux(lev);

  for ( int dir = 0; dir < BL_SPACEDIM; ++dir )
    {
      for (MFIter mfi(*flux[dir]); mfi.isValid(); ++mfi)
        {
          FArrayBox& gp = (*flux[dir])[mfi];
          Real* gpd = gp.dataPtr();

          int n = mfi.index();
          const int* lo = mfi.validbox().loVect();
          const int* hi = mfi.validbox().hiVect();
          const int* gplo = gp.box().loVect();
          const int* gphi = gp.box().hiVect();

          mgt_get_gp(&lev, &dir, &n, gpd, gplo, gphi, lo, hi);
          gp.mult(dx[dir]);
        }
    }

  mgt_delete_flux(lev);
}

void 
MGT_Solver::nodal_project(MultiFab* p[], MultiFab* vel[], MultiFab* Rhs[], const Real& tol, const Real& abs_tol)
{
  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      for (MFIter vmfi(*(vel[lev])); vmfi.isValid(); ++vmfi)
	{
	  int n = vmfi.index();

	  const int* lo = vmfi.validbox().loVect();
	  const int* hi = vmfi.validbox().hiVect();

	  const FArrayBox& velfab = (*(vel[lev]))[vmfi];
	  const Real* vd = velfab.dataPtr();
	  const int* vlo = velfab.box().loVect();
	  const int* vhi = velfab.box().hiVect();
	  mgt_set_vel(&lev, &n, vd, vlo, vhi, lo, hi);
	}

      for (MFIter pmfi(*(p[lev])); pmfi.isValid(); ++pmfi)
	{
	  int n = pmfi.index();

	  const int* lo = pmfi.validbox().loVect();
	  const int* hi = pmfi.validbox().hiVect();

	  const FArrayBox& sol = (*(p[lev]))[pmfi];
	  const Real* sd = sol.dataPtr();
	  const int* slo = sol.box().loVect();
	  const int* shi = sol.box().hiVect();
	  mgt_set_pr(&lev, &n, sd, slo, shi, lo, hi);
	}
    }

  mgt_divu();

  mgt_nodal_solve(tol,abs_tol);

  mgt_newu();

  for ( int lev = 0; lev < m_nlevel; ++lev )
    {
      for (MFIter pmfi(*(p[lev])); pmfi.isValid(); ++pmfi)
	{
	  FArrayBox& sol = (*(p[lev]))[pmfi];
	  Real* sd = sol.dataPtr();
	  int n = pmfi.index();
	  const int* lo = pmfi.validbox().loVect();
	  const int* hi = pmfi.validbox().hiVect();
	  const int* plo = sol.box().loVect();
	  const int* phi = sol.box().hiVect();
	  mgt_get_pr(&lev, &n, sd, plo, phi, lo, hi);
	}

      for (MFIter vmfi(*(vel[lev])); vmfi.isValid(); ++vmfi)
	{
	  FArrayBox& velfab = (*(vel[lev]))[vmfi];
	  Real* vd = velfab.dataPtr();
	  int n = vmfi.index();
	  const int* lo = vmfi.validbox().loVect();
	  const int* hi = vmfi.validbox().hiVect();
	  const int* vlo = velfab.box().loVect();
	  const int* vhi = velfab.box().hiVect();
	  mgt_get_vel(&lev, &n, vd, vlo, vhi, lo, hi);
	}
    }
}

MGT_Solver::~MGT_Solver()
{
  if (m_nodal) {
    mgt_nodal_dealloc();
  } else {
    mgt_dealloc();
  }
}
