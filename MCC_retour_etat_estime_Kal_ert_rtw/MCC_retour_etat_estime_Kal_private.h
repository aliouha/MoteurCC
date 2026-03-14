/*
 * File: MCC_retour_etat_estime_Kal_private.h
 *
 * Code generated for Simulink model 'MCC_retour_etat_estime_Kal'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Sat Mar 14 16:07:38 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef MCC_retour_etat_estime_Kal_private_h_
#define MCC_retour_etat_estime_Kal_private_h_
#include "rtwtypes.h"
#include "MCC_retour_etat_estime_Kal_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

extern real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u);
extern real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u);

/* private model entry point functions */
extern void MCC_retour_etat_estime_Kal_derivatives
  (RT_MODEL_MCC_retour_etat_esti_T *const MCC_retour_etat_estime_Kal_M);

#endif                               /* MCC_retour_etat_estime_Kal_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
