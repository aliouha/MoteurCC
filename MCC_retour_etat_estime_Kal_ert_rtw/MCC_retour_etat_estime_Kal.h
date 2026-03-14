/*
 * File: MCC_retour_etat_estime_Kal.h
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

#ifndef MCC_retour_etat_estime_Kal_h_
#define MCC_retour_etat_estime_Kal_h_
#ifndef MCC_retour_etat_estime_Kal_COMMON_INCLUDES_
#define MCC_retour_etat_estime_Kal_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                         /* MCC_retour_etat_estime_Kal_COMMON_INCLUDES_ */

#include "MCC_retour_etat_estime_Kal_types.h"
#include <string.h>
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T TmpSignalConversionAtStateSpace[2];
  real_T Output;                       /* '<S1>/Output' */
  real_T Add1[2];                      /* '<Root>/Add1' */
} B_MCC_retour_etat_estime_Kal_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T NextOutput;                   /* '<S1>/White Noise' */
  uint32_T RandSeed;                   /* '<S1>/White Noise' */
} DW_MCC_retour_etat_estime_Kal_T;

/* Continuous states (default storage) */
typedef struct {
  real_T StateSpace_CSTATE[2];         /* '<Root>/State-Space' */
  real_T StateSpace1_CSTATE[2];        /* '<Root>/State-Space1' */
} X_MCC_retour_etat_estime_Kal_T;

/* State derivatives (default storage) */
typedef struct {
  real_T StateSpace_CSTATE[2];         /* '<Root>/State-Space' */
  real_T StateSpace1_CSTATE[2];        /* '<Root>/State-Space1' */
} XDot_MCC_retour_etat_estime_K_T;

/* State disabled  */
typedef struct {
  boolean_T StateSpace_CSTATE[2];      /* '<Root>/State-Space' */
  boolean_T StateSpace1_CSTATE[2];     /* '<Root>/State-Space1' */
} XDis_MCC_retour_etat_estime_K_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Constant parameters (default storage) */
typedef struct {
  /* Pooled Parameter (Expression: A)
   * Referenced by:
   *   '<Root>/State-Space'
   *   '<Root>/State-Space1'
   */
  real_T pooled1[4];

  /* Pooled Parameter (Expression: B_sim)
   * Referenced by:
   *   '<Root>/State-Space'
   *   '<Root>/State-Space1'
   */
  real_T pooled2[2];

  /* Pooled Parameter (Expression: A)
   * Referenced by:
   *   '<Root>/State-Space'
   *   '<Root>/State-Space1'
   */
  uint32_T pooled6[4];
} ConstP_MCC_retour_etat_estime_T;

/* Real-time Model Data Structure */
struct tag_RTM_MCC_retour_etat_estim_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  B_MCC_retour_etat_estime_Kal_T *blockIO;
  X_MCC_retour_etat_estime_Kal_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_MCC_retour_etat_estime_K_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[4];
  real_T odeF[4][4];
  ODE4_IntgData intgData;
  DW_MCC_retour_etat_estime_Kal_T *dwork;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Constant parameters (default storage) */
extern const ConstP_MCC_retour_etat_estime_T MCC_retour_etat_estime_K_ConstP;

/* Model entry point functions */
extern void MCC_retour_etat_estime_Kal_initialize
  (RT_MODEL_MCC_retour_etat_esti_T *const MCC_retour_etat_estime_Kal_M);
extern void MCC_retour_etat_estime_Kal_step(RT_MODEL_MCC_retour_etat_esti_T *
  const MCC_retour_etat_estime_Kal_M);
extern void MCC_retour_etat_estime_Kal_terminate(RT_MODEL_MCC_retour_etat_esti_T
  *const MCC_retour_etat_estime_Kal_M);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<Root>/Scope1' : Unused code path elimination
 * Block '<Root>/Scope2' : Unused code path elimination
 * Block '<Root>/Scope3' : Unused code path elimination
 * Block '<Root>/Scope4' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'MCC_retour_etat_estime_Kal'
 * '<S1>'   : 'MCC_retour_etat_estime_Kal/Band-Limited White Noise'
 */
#endif                                 /* MCC_retour_etat_estime_Kal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
