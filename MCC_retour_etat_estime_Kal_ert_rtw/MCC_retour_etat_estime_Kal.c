/*
 * File: MCC_retour_etat_estime_Kal.c
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

#include "MCC_retour_etat_estime_Kal.h"
#include <emmintrin.h>
#include "rtwtypes.h"
#include "MCC_retour_etat_estime_Kal_private.h"
#include <string.h>
#include <math.h>

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si ,
  RT_MODEL_MCC_retour_etat_esti_T *const MCC_retour_etat_estime_Kal_M)
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  MCC_retour_etat_estime_Kal_derivatives(MCC_retour_etat_estime_Kal_M);

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  MCC_retour_etat_estime_Kal_step(MCC_retour_etat_estime_Kal_M);
  MCC_retour_etat_estime_Kal_derivatives(MCC_retour_etat_estime_Kal_M);

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  MCC_retour_etat_estime_Kal_step(MCC_retour_etat_estime_Kal_M);
  MCC_retour_etat_estime_Kal_derivatives(MCC_retour_etat_estime_Kal_M);

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  MCC_retour_etat_estime_Kal_step(MCC_retour_etat_estime_Kal_M);
  MCC_retour_etat_estime_Kal_derivatives(MCC_retour_etat_estime_Kal_M);

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  uint32_T hi;
  uint32_T lo;

  /* Uniform random number generator (random number between 0 and 1)

     #define IA      16807                      magic multiplier = 7^5
     #define IM      2147483647                 modulus = 2^31-1
     #define IQ      127773                     IM div IA
     #define IR      2836                       IM modulo IA
     #define S       4.656612875245797e-10      reciprocal of 2^31-1
     test = IA * (seed % IQ) - IR * (seed/IQ)
     seed = test < 0 ? (test + IM) : test
     return (seed*S)
   */
  lo = *u % 127773U * 16807U;
  hi = *u / 127773U * 2836U;
  if (lo < hi) {
    *u = 2147483647U - (hi - lo);
  } else {
    *u = lo - hi;
  }

  return (real_T)*u * 4.6566128752457969E-10;
}

real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  real_T si;
  real_T sr;
  real_T y;

  /* Normal (Gaussian) random number generator */
  do {
    sr = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = sr * sr + si * si;
  } while (si > 1.0);

  y = sqrt(-2.0 * log(si) / si) * sr;
  return y;
}

/* Model step function */
void MCC_retour_etat_estime_Kal_step(RT_MODEL_MCC_retour_etat_esti_T *const
  MCC_retour_etat_estime_Kal_M)
{
  B_MCC_retour_etat_estime_Kal_T *MCC_retour_etat_estime_Kal_B =
    MCC_retour_etat_estime_Kal_M->blockIO;
  DW_MCC_retour_etat_estime_Kal_T *MCC_retour_etat_estime_Kal_DW =
    MCC_retour_etat_estime_Kal_M->dwork;
  X_MCC_retour_etat_estime_Kal_T *MCC_retour_etat_estime_Kal_X =
    MCC_retour_etat_estime_Kal_M->contStates;
  __m128d tmp_0;
  real_T tmp_1;
  int32_T tmp;
  if (rtmIsMajorTimeStep(MCC_retour_etat_estime_Kal_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&MCC_retour_etat_estime_Kal_M->solverInfo,
                          ((MCC_retour_etat_estime_Kal_M->Timing.clockTick0+1)*
      MCC_retour_etat_estime_Kal_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(MCC_retour_etat_estime_Kal_M)) {
    MCC_retour_etat_estime_Kal_M->Timing.t[0] = rtsiGetT
      (&MCC_retour_etat_estime_Kal_M->solverInfo);
  }

  /* Step: '<Root>/Step' incorporates:
   *  Step: '<Root>/Step1'
   */
  tmp_1 = MCC_retour_etat_estime_Kal_M->Timing.t[0];

  /* Sum: '<Root>/Sum' incorporates:
   *  Step: '<Root>/Step'
   */
  if (tmp_1 < 0.1) {
    tmp = 0;
  } else {
    tmp = 190;
  }

  /* SignalConversion generated from: '<Root>/State-Space' incorporates:
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/Gain1'
   *  StateSpace: '<Root>/State-Space1'
   *  Step: '<Root>/Step'
   *  Sum: '<Root>/Sum'
   */
  MCC_retour_etat_estime_Kal_B->TmpSignalConversionAtStateSpace[0] =
    6.089999999999943 * (real_T)tmp - (0.60668928571428149 *
    MCC_retour_etat_estime_Kal_X->StateSpace1_CSTATE[0U] + 5.482027589285658 *
    MCC_retour_etat_estime_Kal_X->StateSpace1_CSTATE[1U]);

  /* Step: '<Root>/Step1' */
  if (tmp_1 < 0.5) {
    /* SignalConversion generated from: '<Root>/State-Space' */
    MCC_retour_etat_estime_Kal_B->TmpSignalConversionAtStateSpace[1] = 0.0;
  } else {
    /* SignalConversion generated from: '<Root>/State-Space' */
    MCC_retour_etat_estime_Kal_B->TmpSignalConversionAtStateSpace[1] = 10.0;
  }

  if (rtmIsMajorTimeStep(MCC_retour_etat_estime_Kal_M)) {
    /* Gain: '<S1>/Output' incorporates:
     *  RandomNumber: '<S1>/White Noise'
     */
    MCC_retour_etat_estime_Kal_B->Output = 316.22776601683796 *
      MCC_retour_etat_estime_Kal_DW->NextOutput;
  }

  /* Gain: '<Root>/Gain2' incorporates:
   *  Gain: '<Root>/Gain3'
   *  StateSpace: '<Root>/State-Space'
   *  StateSpace: '<Root>/State-Space1'
   *  Sum: '<Root>/Add'
   *  Sum: '<Root>/Add1'
   *  Sum: '<Root>/Add2'
   */
  tmp_0 = _mm_add_pd(_mm_add_pd(_mm_set1_pd
    ((MCC_retour_etat_estime_Kal_X->StateSpace_CSTATE[0U] +
      MCC_retour_etat_estime_Kal_X->StateSpace1_CSTATE[0U]) *
     -0.011592479767419023), _mm_set1_pd
    (((MCC_retour_etat_estime_Kal_X->StateSpace_CSTATE[1U] +
       MCC_retour_etat_estime_Kal_B->Output) -
      MCC_retour_etat_estime_Kal_X->StateSpace1_CSTATE[1U]) *
     0.00800525124482019)), _mm_loadu_pd
                     (&MCC_retour_etat_estime_Kal_B->TmpSignalConversionAtStateSpace
                      [0]));

  /* Sum: '<Root>/Add1' */
  _mm_storeu_pd(&MCC_retour_etat_estime_Kal_B->Add1[0], tmp_0);
  if (rtmIsMajorTimeStep(MCC_retour_etat_estime_Kal_M)) {
    if (rtmIsMajorTimeStep(MCC_retour_etat_estime_Kal_M)) {
      /* Update for RandomNumber: '<S1>/White Noise' */
      MCC_retour_etat_estime_Kal_DW->NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
        (&MCC_retour_etat_estime_Kal_DW->RandSeed);
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(MCC_retour_etat_estime_Kal_M)) {
    rt_ertODEUpdateContinuousStates(&MCC_retour_etat_estime_Kal_M->solverInfo,
      MCC_retour_etat_estime_Kal_M);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++MCC_retour_etat_estime_Kal_M->Timing.clockTick0;
    MCC_retour_etat_estime_Kal_M->Timing.t[0] = rtsiGetSolverStopTime
      (&MCC_retour_etat_estime_Kal_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      MCC_retour_etat_estime_Kal_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void MCC_retour_etat_estime_Kal_derivatives(RT_MODEL_MCC_retour_etat_esti_T *
  const MCC_retour_etat_estime_Kal_M)
{
  B_MCC_retour_etat_estime_Kal_T *MCC_retour_etat_estime_Kal_B =
    MCC_retour_etat_estime_Kal_M->blockIO;
  X_MCC_retour_etat_estime_Kal_T *MCC_retour_etat_estime_Kal_X =
    MCC_retour_etat_estime_Kal_M->contStates;
  __m128d tmp;
  __m128d tmp_0;
  XDot_MCC_retour_etat_estime_K_T *_rtXdot;
  int32_T ri;
  uint32_T StateSpace1_CSTATE_tmp;
  _rtXdot = ((XDot_MCC_retour_etat_estime_K_T *)
             MCC_retour_etat_estime_Kal_M->derivs);

  /* Derivatives for StateSpace: '<Root>/State-Space' */
  _rtXdot->StateSpace_CSTATE[0] = 0.0;
  _rtXdot->StateSpace_CSTATE[1] = 0.0;
  for (ri = 0; (uint32_T)ri < 2U; ri = (int32_T)((uint32_T)ri + 1U)) {
    StateSpace1_CSTATE_tmp = MCC_retour_etat_estime_K_ConstP.pooled6[(uint32_T)
      ri];
    _rtXdot->StateSpace_CSTATE[StateSpace1_CSTATE_tmp] +=
      MCC_retour_etat_estime_K_ConstP.pooled1[(uint32_T)ri] *
      MCC_retour_etat_estime_Kal_X->StateSpace_CSTATE[0U];
  }

  while ((uint32_T)ri < 4U) {
    StateSpace1_CSTATE_tmp = MCC_retour_etat_estime_K_ConstP.pooled6[(uint32_T)
      ri];
    _rtXdot->StateSpace_CSTATE[StateSpace1_CSTATE_tmp] +=
      MCC_retour_etat_estime_K_ConstP.pooled1[(uint32_T)ri] *
      MCC_retour_etat_estime_Kal_X->StateSpace_CSTATE[1U];
    ri = (int32_T)((uint32_T)ri + 1U);
  }

  tmp_0 = _mm_loadu_pd(&MCC_retour_etat_estime_K_ConstP.pooled2[0U]);
  tmp = _mm_add_pd(_mm_mul_pd(tmp_0, _mm_loadu_pd
    (&MCC_retour_etat_estime_Kal_B->TmpSignalConversionAtStateSpace[0U])),
                   _mm_loadu_pd(&_rtXdot->StateSpace_CSTATE[0U]));
  _mm_storeu_pd(&_rtXdot->StateSpace_CSTATE[0U], tmp);

  /* End of Derivatives for StateSpace: '<Root>/State-Space' */

  /* Derivatives for StateSpace: '<Root>/State-Space1' */
  _rtXdot->StateSpace1_CSTATE[0] = 0.0;
  _rtXdot->StateSpace1_CSTATE[1] = 0.0;
  for (ri = 0; (uint32_T)ri < 2U; ri = (int32_T)((uint32_T)ri + 1U)) {
    StateSpace1_CSTATE_tmp = MCC_retour_etat_estime_K_ConstP.pooled6[(uint32_T)
      ri];
    _rtXdot->StateSpace1_CSTATE[StateSpace1_CSTATE_tmp] +=
      MCC_retour_etat_estime_K_ConstP.pooled1[(uint32_T)ri] *
      MCC_retour_etat_estime_Kal_X->StateSpace1_CSTATE[0U];
  }

  while ((uint32_T)ri < 4U) {
    StateSpace1_CSTATE_tmp = MCC_retour_etat_estime_K_ConstP.pooled6[(uint32_T)
      ri];
    _rtXdot->StateSpace1_CSTATE[StateSpace1_CSTATE_tmp] +=
      MCC_retour_etat_estime_K_ConstP.pooled1[(uint32_T)ri] *
      MCC_retour_etat_estime_Kal_X->StateSpace1_CSTATE[1U];
    ri = (int32_T)((uint32_T)ri + 1U);
  }

  tmp = _mm_add_pd(_mm_mul_pd(tmp_0, _mm_loadu_pd
    (&MCC_retour_etat_estime_Kal_B->Add1[0U])), _mm_loadu_pd
                   (&_rtXdot->StateSpace1_CSTATE[0U]));
  _mm_storeu_pd(&_rtXdot->StateSpace1_CSTATE[0U], tmp);

  /* End of Derivatives for StateSpace: '<Root>/State-Space1' */
}

/* Model initialize function */
void MCC_retour_etat_estime_Kal_initialize(RT_MODEL_MCC_retour_etat_esti_T *
  const MCC_retour_etat_estime_Kal_M)
{
  DW_MCC_retour_etat_estime_Kal_T *MCC_retour_etat_estime_Kal_DW =
    MCC_retour_etat_estime_Kal_M->dwork;
  X_MCC_retour_etat_estime_Kal_T *MCC_retour_etat_estime_Kal_X =
    MCC_retour_etat_estime_Kal_M->contStates;
  B_MCC_retour_etat_estime_Kal_T *MCC_retour_etat_estime_Kal_B =
    MCC_retour_etat_estime_Kal_M->blockIO;
  XDis_MCC_retour_etat_estime_K_T *MCC_retour_etat_estime_Kal_XDis =
    ((XDis_MCC_retour_etat_estime_K_T *)
     MCC_retour_etat_estime_Kal_M->contStateDisabled);

  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&MCC_retour_etat_estime_Kal_M->solverInfo,
                          &MCC_retour_etat_estime_Kal_M->Timing.simTimeStep);
    rtsiSetTPtr(&MCC_retour_etat_estime_Kal_M->solverInfo, &rtmGetTPtr
                (MCC_retour_etat_estime_Kal_M));
    rtsiSetStepSizePtr(&MCC_retour_etat_estime_Kal_M->solverInfo,
                       &MCC_retour_etat_estime_Kal_M->Timing.stepSize0);
    rtsiSetdXPtr(&MCC_retour_etat_estime_Kal_M->solverInfo,
                 &MCC_retour_etat_estime_Kal_M->derivs);
    rtsiSetContStatesPtr(&MCC_retour_etat_estime_Kal_M->solverInfo, (real_T **)
                         &MCC_retour_etat_estime_Kal_M->contStates);
    rtsiSetNumContStatesPtr(&MCC_retour_etat_estime_Kal_M->solverInfo,
      &MCC_retour_etat_estime_Kal_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&MCC_retour_etat_estime_Kal_M->solverInfo,
      &MCC_retour_etat_estime_Kal_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&MCC_retour_etat_estime_Kal_M->solverInfo,
      &MCC_retour_etat_estime_Kal_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&MCC_retour_etat_estime_Kal_M->solverInfo,
      &MCC_retour_etat_estime_Kal_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&MCC_retour_etat_estime_Kal_M->solverInfo,
      (boolean_T**) &MCC_retour_etat_estime_Kal_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&MCC_retour_etat_estime_Kal_M->solverInfo,
                          (&rtmGetErrorStatus(MCC_retour_etat_estime_Kal_M)));
    rtsiSetRTModelPtr(&MCC_retour_etat_estime_Kal_M->solverInfo,
                      MCC_retour_etat_estime_Kal_M);
  }

  rtsiSetSimTimeStep(&MCC_retour_etat_estime_Kal_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&MCC_retour_etat_estime_Kal_M->solverInfo,
    false);
  rtsiSetIsContModeFrozen(&MCC_retour_etat_estime_Kal_M->solverInfo, false);
  MCC_retour_etat_estime_Kal_M->intgData.y = MCC_retour_etat_estime_Kal_M->odeY;
  MCC_retour_etat_estime_Kal_M->intgData.f[0] =
    MCC_retour_etat_estime_Kal_M->odeF[0];
  MCC_retour_etat_estime_Kal_M->intgData.f[1] =
    MCC_retour_etat_estime_Kal_M->odeF[1];
  MCC_retour_etat_estime_Kal_M->intgData.f[2] =
    MCC_retour_etat_estime_Kal_M->odeF[2];
  MCC_retour_etat_estime_Kal_M->intgData.f[3] =
    MCC_retour_etat_estime_Kal_M->odeF[3];
  MCC_retour_etat_estime_Kal_M->contStates = ((X_MCC_retour_etat_estime_Kal_T *)
    MCC_retour_etat_estime_Kal_X);
  MCC_retour_etat_estime_Kal_M->contStateDisabled =
    ((XDis_MCC_retour_etat_estime_K_T *) MCC_retour_etat_estime_Kal_XDis);
  MCC_retour_etat_estime_Kal_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&MCC_retour_etat_estime_Kal_M->solverInfo, (void *)
                    &MCC_retour_etat_estime_Kal_M->intgData);
  rtsiSetSolverName(&MCC_retour_etat_estime_Kal_M->solverInfo,"ode4");
  rtmSetTPtr(MCC_retour_etat_estime_Kal_M,
             &MCC_retour_etat_estime_Kal_M->Timing.tArray[0]);
  MCC_retour_etat_estime_Kal_M->Timing.stepSize0 = 0.001;

  /* block I/O */
  (void) memset(((void *) MCC_retour_etat_estime_Kal_B), 0,
                sizeof(B_MCC_retour_etat_estime_Kal_T));

  /* states (continuous) */
  {
    (void) memset((void *)MCC_retour_etat_estime_Kal_X, 0,
                  sizeof(X_MCC_retour_etat_estime_Kal_T));
  }

  /* disabled states */
  {
    (void) memset((void *)MCC_retour_etat_estime_Kal_XDis, 0,
                  sizeof(XDis_MCC_retour_etat_estime_K_T));
  }

  /* states (dwork) */
  (void) memset((void *)MCC_retour_etat_estime_Kal_DW, 0,
                sizeof(DW_MCC_retour_etat_estime_Kal_T));

  /* InitializeConditions for StateSpace: '<Root>/State-Space' */
  MCC_retour_etat_estime_Kal_X->StateSpace_CSTATE[0] = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/State-Space1' */
  MCC_retour_etat_estime_Kal_X->StateSpace1_CSTATE[0] = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/State-Space' */
  MCC_retour_etat_estime_Kal_X->StateSpace_CSTATE[1] = 0.0;

  /* InitializeConditions for StateSpace: '<Root>/State-Space1' */
  MCC_retour_etat_estime_Kal_X->StateSpace1_CSTATE[1] = 0.0;

  /* InitializeConditions for RandomNumber: '<S1>/White Noise' */
  MCC_retour_etat_estime_Kal_DW->RandSeed = 1529675776U;
  MCC_retour_etat_estime_Kal_DW->NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
    (&MCC_retour_etat_estime_Kal_DW->RandSeed);
}

/* Model terminate function */
void MCC_retour_etat_estime_Kal_terminate(RT_MODEL_MCC_retour_etat_esti_T *const
  MCC_retour_etat_estime_Kal_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(MCC_retour_etat_estime_Kal_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
