/* ///////////////////////////////////////////////////////////////////// */
/*! 
  \file  
  \brief Contains functions to assist problem initialization in init.c.

  The init_tools.c file contains helper functions used mainly in init.c. This is to keep init.c relatively clean, with only functions that were originally defined. 

  \author AYW 
  \date   2012-12-07 14:41 JST
*/
/* ///////////////////////////////////////////////////////////////////// */


#include "pluto.h"
#include "pluto_usr.h"
#include "init_tools.h"

/* Global struct and arrays for normalization */
VarNorm vn;
double ini_cgs[USER_DEF_PARAMETERS];
double ini_code[USER_DEF_PARAMETERS];


/* Functions */

/* ************************************************************** */
void PrintInitData01(const double *out_primitives,
                     const double *halo_primitives) {
/*
 * Print some additional data during initialization
 *
 **************************************************************** */


    print("\n");
    print("> Conditions at (0, 0, 0):\n");
    print("\n");
    print("        %14s  %14s  %14s\n",
           "Nozzle primitives", "Hot halo prim", "ratio");
    print("  rho   %14g  %14g  %14g\n",
           out_primitives[RHO], halo_primitives[RHO],
           out_primitives[RHO] / halo_primitives[RHO]);
    print("  pr    %14g  %14g  %14g\n",
           out_primitives[PRS], halo_primitives[PRS],
           out_primitives[PRS] / halo_primitives[PRS]);
    print("\n");
}


/* ************************************************************** */
void SetBaseNormalization() {
/*
 * Sets initializes VarNorm struct with derived normalizations
 * Gives cgs units upon multiplication form code units.
 *
 * Note that pot_norm is also the (mass) specific energy density [erg / g],
 * eint_norm is the energy [erg], and pres_norm is energy density [erg / cm^-3]
 *
 **************************************************************** */

    vn.l_norm = UNIT_LENGTH;
    vn.dens_norm = UNIT_DENSITY;
    vn.v_norm = UNIT_VELOCITY;
    vn.temp_norm = KELVIN;

    /* Derived normalizations */
    vn.t_norm = vn.l_norm / vn.v_norm;
    vn.area_norm = vn.l_norm * vn.l_norm;
    vn.pres_norm = vn.dens_norm * vn.v_norm * vn.v_norm;
    vn.power_norm = vn.pres_norm * vn.v_norm * vn.area_norm;
    vn.eflux_norm = vn.pres_norm * vn.v_norm;
    vn.eint_norm = vn.pres_norm * vn.l_norm * vn.l_norm * vn.l_norm;
    vn.mdot_norm = vn.dens_norm * pow(vn.l_norm, 3) / vn.t_norm;
    vn.newton_norm = 1. / (vn.t_norm * vn.t_norm * vn.dens_norm);
    vn.pot_norm = vn.v_norm * vn.v_norm;
    vn.acc_norm = vn.v_norm / vn.t_norm;
    vn.n_norm = 1. / (vn.l_norm * vn.l_norm * vn.l_norm);
    vn.m_norm = vn.dens_norm * vn.l_norm * vn.l_norm * vn.l_norm;

    print("> Base normalization initialized.\n\n");

    return;
}


/* ************************************************************** */
void SetIniNormalization() {
/*
 * Sets noramlizations for ini input variables.
 * ini_cgs converts ini parameters to cgs upon multiplication,
 * whereas ini_code converts ini parameters to code units.
 *
 **************************************************************** */

    double year, degrad;
    year = CONST_ly / CONST_c;
    degrad = CONST_PI / 180.;

    ini_cgs[PAR_OPOW] = 1.;
    ini_cgs[PAR_OSPD] = NOZZLE_SELECT(1., CONST_c);
    ini_cgs[PAR_OMDT] = NOZZLE_SELECT(1., CONST_Msun / year);
    ini_cgs[PAR_OANG] = degrad;
    ini_cgs[PAR_ORAD] = vn.l_norm;
    ini_cgs[PAR_ODBH] = vn.l_norm;
    ini_cgs[PAR_ODIR] = degrad;
    ini_cgs[PAR_OOMG] = 1. / (1.e6 * year);
    ini_cgs[PAR_OPHI] = degrad;
    ini_cgs[PAR_OSPH] = vn.l_norm;
    ini_cgs[PAR_OEFF] = 1.;
    ini_cgs[PAR_ARAD] = vn.l_norm;
    ini_cgs[PAR_AMBH] = CONST_Msun;
    ini_cgs[PAR_AEFF] = 1.;
    ini_cgs[PAR_AMLD] = 1.;
    ini_cgs[PAR_ASNK] = vn.l_norm;
    ini_cgs[PAR_HRHO] = vn.dens_norm;
    ini_cgs[PAR_HTMP] = 1;
    ini_cgs[PAR_HVX1] = 1.e5;
    ini_cgs[PAR_HVX2] = 1.e5;
    ini_cgs[PAR_HVX3] = 1.e5;
    ini_cgs[PAR_HVRD] = 1.e5;
    ini_cgs[PAR_HRAD] = vn.l_norm;
//    ini_cgs[PAR_MGAL] = CONST_Msun;
    ini_cgs[PAR_WRHO] = vn.dens_norm;
    ini_cgs[PAR_WTRB] = 1.e5;
    ini_cgs[PAR_WRAD] = vn.l_norm;
    ini_cgs[PAR_WROT] = 1.;
    ini_cgs[PAR_WX1L] = vn.l_norm;
    ini_cgs[PAR_WX1H] = vn.l_norm;
    ini_cgs[PAR_WX2L] = vn.l_norm;
    ini_cgs[PAR_WX2H] = vn.l_norm;
    ini_cgs[PAR_WX3L] = vn.l_norm;
    ini_cgs[PAR_WX3H] = vn.l_norm;
    ini_cgs[PAR_WVRD] = 1.e5;
    ini_cgs[PAR_WVPL] = 1.e5;
    ini_cgs[PAR_WVPP] = 1.e5;
    ini_cgs[PAR_WVAN] = 1.e5;
    ini_cgs[PAR_SGAV] = 1.e5;
    ini_cgs[PAR_NCLD] = 1;
//    ini_cgs[PAR_SPOW] = 1;
//    ini_cgs[PAR_SDUR] = 1.e6 * year;
//    ini_cgs[PAR_SRAD] = vn.l_norm;
//    ini_cgs[PAR_SHGT] = vn.l_norm;
    ini_cgs[PAR_LOMX] = 1;
    ini_cgs[PAR_LCMX] = 1;

    ini_code[PAR_OPOW] = ini_cgs[PAR_OPOW] / vn.power_norm;
    ini_code[PAR_OSPD] = ini_cgs[PAR_OSPD] / NOZZLE_SELECT(1., vn.v_norm);
    ini_code[PAR_OMDT] = ini_cgs[PAR_OMDT] / NOZZLE_SELECT(1., vn.mdot_norm);
    ini_code[PAR_OANG] = ini_cgs[PAR_OANG];
    ini_code[PAR_ORAD] = ini_cgs[PAR_ORAD] / vn.l_norm;
    ini_code[PAR_ODBH] = ini_cgs[PAR_ODBH] / vn.l_norm;
    ini_code[PAR_ODIR] = ini_cgs[PAR_ODIR];
    ini_code[PAR_OOMG] = ini_cgs[PAR_OOMG] * vn.t_norm;
    ini_code[PAR_OPHI] = ini_cgs[PAR_OPHI];
    ini_code[PAR_OSPH] = ini_cgs[PAR_OSPH] / vn.l_norm;
    ini_code[PAR_OEFF] = ini_cgs[PAR_OEFF];
    ini_code[PAR_ARAD] = ini_cgs[PAR_ARAD] / vn.l_norm;
    ini_code[PAR_AMBH] = ini_cgs[PAR_AMBH] / vn.m_norm;
    ini_code[PAR_AEFF] = ini_cgs[PAR_AEFF];
    ini_code[PAR_AMLD] = ini_cgs[PAR_AMLD];
    ini_code[PAR_ASNK] = ini_cgs[PAR_ASNK] / vn.l_norm;
    ini_code[PAR_HRHO] = ini_cgs[PAR_HRHO] / vn.dens_norm;
    ini_code[PAR_HTMP] = ini_cgs[PAR_HTMP] / vn.temp_norm;
    ini_code[PAR_HVX1] = ini_cgs[PAR_HVX1] / vn.v_norm;
    ini_code[PAR_HVX2] = ini_cgs[PAR_HVX2] / vn.v_norm;
    ini_code[PAR_HVX3] = ini_cgs[PAR_HVX3] / vn.v_norm;
    ini_code[PAR_HVRD] = ini_cgs[PAR_HVRD] / vn.v_norm;
    ini_code[PAR_HRAD] = ini_cgs[PAR_HRAD] / vn.l_norm;
//    ini_code[PAR_MGAL] = ini_cgs[PAR_MGAL] / vn.m_norm;
    ini_code[PAR_WRHO] = ini_cgs[PAR_WRHO] / vn.dens_norm;
    ini_code[PAR_WTRB] = ini_cgs[PAR_WTRB] / vn.v_norm;
    ini_code[PAR_WRAD] = ini_cgs[PAR_WRAD] / vn.l_norm;
    ini_code[PAR_WROT] = ini_cgs[PAR_WROT];
    ini_code[PAR_WX1L] = ini_cgs[PAR_WX1L] / vn.l_norm;
    ini_code[PAR_WX1H] = ini_cgs[PAR_WX1H] / vn.l_norm;
    ini_code[PAR_WX2L] = ini_cgs[PAR_WX2L] / vn.l_norm;
    ini_code[PAR_WX2H] = ini_cgs[PAR_WX2H] / vn.l_norm;
    ini_code[PAR_WX3L] = ini_cgs[PAR_WX3L] / vn.l_norm;
    ini_code[PAR_WX3H] = ini_cgs[PAR_WX3H] / vn.l_norm;
    ini_code[PAR_WVRD] = ini_cgs[PAR_WVRD] / vn.v_norm;
    ini_code[PAR_WVPL] = ini_cgs[PAR_WVPL] / vn.v_norm;
    ini_code[PAR_WVPP] = ini_cgs[PAR_WVPP] / vn.v_norm;
    ini_code[PAR_WVAN] = ini_cgs[PAR_WVAN] / vn.v_norm;
    ini_code[PAR_SGAV] = ini_cgs[PAR_SGAV] / vn.v_norm;
    ini_code[PAR_NCLD] = ini_cgs[PAR_NCLD];
//    ini_code[PAR_SPOW] = ini_cgs[PAR_SPOW] / vn.power_norm;
//    ini_code[PAR_SDUR] = ini_cgs[PAR_SDUR] / vn.t_norm;
//    ini_code[PAR_SRAD] = ini_cgs[PAR_SRAD] / vn.l_norm;
//    ini_code[PAR_SHGT] = ini_cgs[PAR_SHGT] / vn.l_norm;
    ini_code[PAR_LOMX] = ini_cgs[PAR_LOMX];
    ini_code[PAR_LCMX] = ini_cgs[PAR_LCMX];

//----DM: 7Aug15, Turned off PAR_LEV1 as not enough parameter slots---//
    /* AYW 2016-02-29 NOTE: increased number of parameters */
//  ini_cgs[PAR_LEV1] = 1;
//  ini_code[PAR_LEV1] = ini_cgs[PAR_LEV1];


    print("> Ini parameter normalization array initialized.\n\n");

    return;

}


/* ************************************************ */
double Speed2Lorentz(const double vel)
/*!
 * Return Lorentz factor from Lorentz factor
 *
 ************************************************** */
{
    double vsqr = 0, clight2;

    clight2 = pow(CONST_c / UNIT_VELOCITY, 2);

    vsqr = vel * vel;
    return 1.0 / sqrt(1.0 - vsqr / clight2);
}


/* ************************************************ */
double Lorentz2Speed(const double lorentz)
/*!
 * Return velocity from Lorentz factor
 *
 ************************************************** */
{
    double clight;
    clight = CONST_c / vn.v_norm;
    return sqrt(1. - 1. / (lorentz * lorentz)) * clight;
}


/* ************************************************ */
void PrintGridStruct(Grid *grid, int show_for_rank, int k, int j, int i) {
    /*!
     * grid     array of grid structures
     *
     * The function prints out grid structure members and
     * is useful for parallel debugging.
     *
     ************************************************** */

    print("\n");
    print("Printing members of GRID structure on rank %d\n", prank);
    print("                        IDIR             JDIR              KDIR\n");
    print("grid[]->xbeg        = %16e %16e %16e\n", grid->xbeg[IDIR],        grid->xbeg[JDIR],        grid->xbeg[KDIR]);
    print("grid[]->xend        = %16e %16e %16e\n", grid->xend[IDIR],        grid->xend[JDIR],        grid->xend[KDIR]);
    print("grid[]->xbeg_glob   = %16e %16e %16e\n", grid->xbeg_glob[IDIR],   grid->xbeg_glob[JDIR],   grid->xbeg_glob[KDIR]);
    print("grid[]->xend_glob   = %16e %16e %16e\n", grid->xend_glob[IDIR],   grid->xend_glob[JDIR],   grid->xend_glob[KDIR]);
    print("grid[]->x[]         = %16e %16e %16e\n", grid->x[IDIR][i],        grid->x[JDIR][j],        grid->x[KDIR][k]);
    print("grid[]->x_glob[]    = %16e %16e %16e\n", grid->x_glob[IDIR][i],   grid->x_glob[JDIR][j],   grid->x_glob[KDIR][k]);
    print("grid[]->xr[]        = %16e %16e %16e\n", grid->xr[IDIR][i],       grid->xr[JDIR][j],       grid->xr[KDIR][k]);
    print("grid[]->xr_glob[]   = %16e %16e %16e\n", grid->xr_glob[IDIR][i],  grid->xr_glob[JDIR][j],  grid->xr_glob[KDIR][k]);
    print("grid[]->xl[]        = %16e %16e %16e\n", grid->xl[IDIR][i],       grid->xl[JDIR][j],       grid->xl[KDIR][k]);
    print("grid[]->xl_glob[]   = %16e %16e %16e\n", grid->xl_glob[IDIR][i],  grid->xl_glob[JDIR][j],  grid->xl_glob[KDIR][k]);
    print("grid[]->dx[]        = %16e %16e %16e\n", grid->dx[IDIR][i],       grid->dx[JDIR][j],       grid->dx[KDIR][k]);
    print("grid[]->dx_glob[]   = %16e %16e %16e\n", grid->dx_glob[IDIR][i],  grid->dx_glob[JDIR][j],  grid->dx_glob[KDIR][k]);
    print("grid[]->xgc[]       = %16e %16e %16e\n", grid->xgc[IDIR][i],      grid->xgc[JDIR][j],      grid->xgc[KDIR][k]);
    print("grid[]->dV[][][]    = %16e          \n", grid->dV[k][j][i]);
    print("grid[]->A[][][]     = %16e %16e %16e\n", grid->A[IDIR][k][j][i],  grid->A[JDIR][k][j][i],  grid->A[KDIR][k][j][i]);
    print("grid[]->rt          = %16e          \n", grid->rt[i]);
    print("grid[]->sp, s, dmu  = %16e %16e %16e\n", grid->sp[j],             grid->s[j],              grid->dmu[j]);
    print("grid[]->inv_dx[]    = %16e %16e %16e\n", grid->inv_dx[IDIR][i],   grid->inv_dx[JDIR][j],   grid->inv_dx[KDIR][k]);
    print("grid[]->inv_dxi[]   = %16e %16e %16e\n", grid->inv_dxi[IDIR][i],  grid->inv_dxi[JDIR][j],  grid->inv_dxi[KDIR][k]);
    print("grid[]->dl_min      = %16e %16e %16e\n", grid->dl_min[IDIR],      grid->dl_min[JDIR],      grid->dl_min[KDIR]);
    print("grid[]->np_tot_glob = %16d %16d %16d\n", grid->np_tot_glob[IDIR], grid->np_tot_glob[JDIR], grid->np_tot_glob[KDIR]);
    print("grid[]->np_int_glob = %16d %16d %16d\n", grid->np_int_glob[IDIR], grid->np_int_glob[JDIR], grid->np_int_glob[KDIR]);
    print("grid[]->np_tot      = %16d %16d %16d\n", grid->np_tot[IDIR],      grid->np_tot[JDIR],      grid->np_tot[KDIR]);
    print("grid[]->np_int      = %16d %16d %16d\n", grid->np_int[IDIR],      grid->np_int[JDIR],      grid->np_int[KDIR]);
    print("grid[]->nghost      = %16d %16d %16d\n", grid->nghost[IDIR],      grid->nghost[JDIR],      grid->nghost[KDIR]);
    print("grid[]->lbound      = %16d %16d %16d\n", grid->lbound[IDIR],      grid->lbound[JDIR],      grid->lbound[KDIR]);
    print("grid[]->rbound      = %16d %16d %16d\n", grid->rbound[IDIR],      grid->rbound[JDIR],      grid->rbound[KDIR]);
    print("grid[]->gbeg        = %16d %16d %16d\n", grid->gbeg[IDIR],        grid->gbeg[JDIR],        grid->gbeg[KDIR]);
    print("grid[]->gend        = %16d %16d %16d\n", grid->gend[IDIR],        grid->gend[JDIR],        grid->gend[KDIR]);
    print("grid[]->beg         = %16d %16d %16d\n", grid->beg[IDIR],         grid->beg[JDIR],         grid->beg[KDIR]);
    print("grid[]->end         = %16d %16d %16d\n", grid->end[IDIR],         grid->end[JDIR],         grid->end[KDIR]);
    print("grid[]->lbeg        = %16d %16d %16d\n", grid->lbeg[IDIR],        grid->lbeg[JDIR],        grid->lbeg[KDIR]);
    print("grid[]->lend        = %16d %16d %16d\n", grid->lend[IDIR],        grid->lend[JDIR],        grid->lend[KDIR]);
    print("grid[]->uniform     = %16d %16d %16d\n", grid->uniform[IDIR],     grid->uniform[JDIR],     grid->uniform[KDIR]);
    print("grid[]->nproc       = %16d %16d %16d\n", grid->nproc[IDIR],       grid->nproc[JDIR],       grid->nproc[KDIR]);
    print("grid[]->rank_coord  = %16d %16d %16d\n", grid->rank_coord[IDIR],  grid->rank_coord[JDIR],  grid->rank_coord[KDIR]);
    print("grid[]->level       = %16d          \n", grid->level);
    print("\n");

}

/* ************************************************ */
void PrintBaseNormalizations() {
    /*!
     * grid     array of grid structures
     *
     * The function prints out grid structure members and
     * is useful for parallel debugging.
     *
     ************************************************** */

    print("vn.l_norm      = %16e \n", vn.l_norm );
    print("vn.dens_norm   = %16e \n", vn.dens_norm );
    print("vn.v_norm      = %16e \n", vn.v_norm );
    print("vn.temp_norm   = %16e \n", vn.temp_norm );
    print("vn.t_norm      = %16e \n", vn.t_norm );
    print("vn.area_norm   = %16e \n", vn.area_norm );
    print("vn.pres_norm   = %16e \n", vn.pres_norm );
    print("vn.power_norm  = %16e \n", vn.power_norm );
    print("vn.eflux_norm  = %16e \n", vn.eflux_norm );
    print("vn.eint_norm   = %16e \n", vn.eint_norm );
    print("vn.mdot_norm   = %16e \n", vn.mdot_norm );
    print("vn.newton_norm = %16e \n", vn.newton_norm );
    print("vn.pot_norm    = %16e \n", vn.pot_norm );
    print("vn.acc_norm    = %16e \n", vn.acc_norm );
    print("vn.n_norm      = %16e \n", vn.n_norm );
    print("vn.m_norm      = %16e \n", vn.m_norm );
    print("\n");
    print("\n");
    print("\n");

}
