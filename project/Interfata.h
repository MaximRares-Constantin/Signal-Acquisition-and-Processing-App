/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: Main_uir */
#define  PANEL_GRAPH_FILTERED_DATA        2       /* control type: graph, callback function: (none) */
#define  PANEL_ANVELOPA                   3       /* control type: graph, callback function: (none) */
#define  PANEL_HISTOGRAM                  4       /* control type: graph, callback function: (none) */
#define  PANEL_GRAPH_RAW_DATA             5       /* control type: graph, callback function: RAW_DATA_FC */
#define  PANEL_SAVE                       6       /* control type: command, callback function: SAVE_FC */
#define  PANEL_GEN_ANVELOPA               7       /* control type: command, callback function: GEN_ANVELOPA_FC */
#define  PANEL_LOAD                       8       /* control type: command, callback function: LOAD_FC */
#define  PANEL_COMMANDBUTTON_APLICA       9       /* control type: command, callback function: APLICA_FC */
#define  PANEL_COMMANDBUTTON_NEXT         10      /* control type: command, callback function: CB_NEXT_FC */
#define  PANEL_COMMANDBUTTON_PREV         11      /* control type: command, callback function: CB_PREV_FC */
#define  PANEL_stop_timer                 12      /* control type: numeric, callback function: stop_timer_FC */
#define  PANEL_start_timer                13      /* control type: numeric, callback function: start_timer_FC */
#define  PANEL_TEXTMSG                    14      /* control type: textMsg, callback function: (none) */
#define  PANEL_DIM_FEREASTRA              15      /* control type: ring, callback function: (none) */
#define  PANEL_FILTRU                     16      /* control type: ring, callback function: SELECTARE_FILTRU */
#define  PANEL_NR_VAL_MIN                 17      /* control type: numeric, callback function: (none) */
#define  PANEL_NR_VAL_MAX                 18      /* control type: numeric, callback function: (none) */
#define  PANEL_kurtosis                   19      /* control type: numeric, callback function: (none) */
#define  PANEL_skewness                   20      /* control type: numeric, callback function: (none) */
#define  PANEL_VAL_MEDIANA                21      /* control type: numeric, callback function: (none) */
#define  PANEL_VAL_DISPERSIE              22      /* control type: numeric, callback function: (none) */
#define  PANEL_VAL_MEDIE                  23      /* control type: numeric, callback function: (none) */
#define  PANEL_NR_ZEROS                   24      /* control type: numeric, callback function: (none) */
#define  PANEL_MIN_VAL                    25      /* control type: numeric, callback function: (none) */
#define  PANEL_MAX_VAL                    26      /* control type: numeric, callback function: (none) */
#define  PANEL_VAL_ALPHA                  27      /* control type: numeric, callback function: (none) */
#define  PANEL_SWITCH_PANEL               28      /* control type: binary, callback function: SWITCH_PANEL_FC */

#define  PANEL_2                          2       /* callback function: main_panel_2 */
#define  PANEL_2_SWITCH_PANEL             2       /* control type: binary, callback function: SWITCH_PANEL_FC */
#define  PANEL_2_RAW_DATA                 3       /* control type: graph, callback function: (none) */
#define  PANEL_2_Spectru_filt             4       /* control type: graph, callback function: (none) */
#define  PANEL_2_Window_filt              5       /* control type: graph, callback function: (none) */
#define  PANEL_2_SAVE_FILT                6       /* control type: command, callback function: SAVE_FILT_FC */
#define  PANEL_2_WINDOW                   7       /* control type: graph, callback function: (none) */
#define  PANEL_2_SPECTRU                  8       /* control type: graph, callback function: (none) */
#define  PANEL_2_COMMANDBUTTON_SPECTRU    9       /* control type: command, callback function: SPECTRU_FC */
#define  PANEL_2_IDC_SEC                  10      /* control type: numeric, callback function: (none) */
#define  PANEL_2_IDC_NR_PCT               11      /* control type: ring, callback function: (none) */
#define  PANEL_2_CMD_APLICA               12      /* control type: command, callback function: APLICA_FC2 */
#define  PANEL_2_IDC_FREQ_PEAK            13      /* control type: numeric, callback function: (none) */
#define  PANEL_2_IDC_POWER_PEAK           14      /* control type: numeric, callback function: (none) */
#define  PANEL_2_WINDOW_TYPE              15      /* control type: ring, callback function: (none) */
#define  PANEL_2_FILTER_TYPE              16      /* control type: ring, callback function: (none) */
#define  PANEL_2_IDC_CUT_FREQ             17      /* control type: numeric, callback function: (none) */
#define  PANEL_2_IDC_ORDER                18      /* control type: numeric, callback function: (none) */
#define  PANEL_2_IDC_FPASS                19      /* control type: numeric, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK APLICA_FC(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK APLICA_FC2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_NEXT_FC(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CB_PREV_FC(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GEN_ANVELOPA_FC(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK LOAD_FC(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK main_panel_2(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Main_uir(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RAW_DATA_FC(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SAVE_FC(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SAVE_FILT_FC(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SELECTARE_FILTRU(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SPECTRU_FC(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK start_timer_FC(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK stop_timer_FC(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SWITCH_PANEL_FC(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif