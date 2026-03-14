/*
 * File: ert_main.c
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

#include <stddef.h>
#include <stdio.h>            /* This example main program uses printf/fflush */
#include "MCC_retour_etat_estime_Kal.h" /* Model header file */

static RT_MODEL_MCC_retour_etat_esti_T MCC_retour_etat_estime_Kal_M_;
static RT_MODEL_MCC_retour_etat_esti_T *const MCC_retour_etat_estime_Kal_MPtr =
  &MCC_retour_etat_estime_Kal_M_;      /* Real-time model */
static B_MCC_retour_etat_estime_Kal_T MCC_retour_etat_estime_Kal_B;/* Observable signals */
static DW_MCC_retour_etat_estime_Kal_T MCC_retour_etat_estime_Kal_DW;/* Observable states */
static X_MCC_retour_etat_estime_Kal_T MCC_retour_etat_estime_Kal_X;/* Observable continuous states */
static XDis_MCC_retour_etat_estime_K_T MCC_retour_etat_estime_Kal_XDis;/* Continuous states Disabled */

/*
 * Associating rt_OneStep with a real-time clock or interrupt service routine
 * is what makes the generated code "real-time".  The function rt_OneStep is
 * always associated with the base rate of the model.  Subrates are managed
 * by the base rate from inside the generated code.  Enabling/disabling
 * interrupts and floating point context switches are target specific.  This
 * example code indicates where these should take place relative to executing
 * the generated code step function.  Overrun behavior should be tailored to
 * your application needs.  This example simply sets an error status in the
 * real-time model and returns from rt_OneStep.
 */
void rt_OneStep(RT_MODEL_MCC_retour_etat_esti_T *const
                MCC_retour_etat_estime_Kal_M);
void rt_OneStep(RT_MODEL_MCC_retour_etat_esti_T *const
                MCC_retour_etat_estime_Kal_M)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(MCC_retour_etat_estime_Kal_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  MCC_retour_etat_estime_Kal_step(MCC_retour_etat_estime_Kal_M);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}

/*
 * The example main function illustrates what is required by your
 * application code to initialize, execute, and terminate the generated code.
 * Attaching rt_OneStep to a real-time clock is target specific. This example
 * illustrates how you do this relative to initializing the model.
 */
int_T main(int_T argc, const char *argv[])
{
  RT_MODEL_MCC_retour_etat_esti_T *const MCC_retour_etat_estime_Kal_M =
    MCC_retour_etat_estime_Kal_MPtr;

  /* Unused arguments */
  (void)(argc);
  (void)(argv);

  /* Pack model data into RTM */
  MCC_retour_etat_estime_Kal_M->blockIO = &MCC_retour_etat_estime_Kal_B;
  MCC_retour_etat_estime_Kal_M->dwork = &MCC_retour_etat_estime_Kal_DW;
  MCC_retour_etat_estime_Kal_M->contStates = &MCC_retour_etat_estime_Kal_X;
  MCC_retour_etat_estime_Kal_M->contStateDisabled =
    &MCC_retour_etat_estime_Kal_XDis;

  /* Initialize model */
  MCC_retour_etat_estime_Kal_initialize(MCC_retour_etat_estime_Kal_M);

  /* Simulating the model step behavior (in non real-time) to
   *  simulate model behavior at stop time.
   */
  while (rtmGetErrorStatus(MCC_retour_etat_estime_Kal_M) == (NULL)&&
         !rtmGetStopRequested(MCC_retour_etat_estime_Kal_M)) {
    rt_OneStep(MCC_retour_etat_estime_Kal_M);
  }

  /* Terminate model */
  MCC_retour_etat_estime_Kal_terminate(MCC_retour_etat_estime_Kal_M);
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
