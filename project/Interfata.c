#include <cvirte.h>		
#include <userint.h>
#include <utility.h>
#include <formatio.h>
#include <ansi_c.h>
#include <advanlys.h>
#include "Interfata.h"
#include "toolbox.h"

#define SAMPLE_RATE		0
#define NPOINTS			1

int panelHandle = 0, panelHandle2 = 0;

int waveInfo[2]; //waveInfo[0] = sampleRate
				 //waveInfo[1] = number of elements
double sampleRate = 0.0;
int npoints = 0;
double *waveData = 0;
double *waveDataTemp = 0;
int idstart= 0;
int idstop =1;
double *filt = 0;
double *f=0;
int imgHandle;
int hist[100];
int interv=100;
double axis[100];
double *anvelopa = 0;
double skew;
double kurt;
ListType coada;

double* FitrOrdin1(double alpha){
	for(int i = 1;i<npoints;i++)
		f[i] = (1-alpha)*f[i-1]+alpha*waveData[i];
	return f;
}

double *mediere(int n)
{
	double sum=0.0;
	for(int i=0;i<npoints;i++)
		{
			sum +=waveData[i];
			ListInsertItem(coada,&waveData[i] ,0);
			int aux = ListNumItems(coada);
			double tmp;
			while(aux > n)
			{
				ListRemoveItem(coada, &tmp , FRONT_OF_LIST);
				sum=sum-tmp;
				aux--;
				
			}
			filt[i] = sum/aux;
		}
	return filt;
}

int main (int argc, char *argv[])
{
	
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Interfata.uir", PANEL)) < 0)
		return -1;
	if ((panelHandle2 = LoadPanel (0, "Interfata.uir", PANEL_2)) < 0)
		return -1;
	coada = ListCreate(sizeof(double));
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	
	return 0;
}

int CVICALLBACK Main_uir (int panel, int event, void *callbackData,
						  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK LOAD_FC (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	double min = 0.0, max = 0.0, media = 0.0, dispersia = 0.0, mediana = 0.0;
	int indMin = 0, indMax = 0,zeros = 0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			//executa script python pentru conversia unui fisierului .wav in .txt
			//LaunchExecutable("python main.py");
			
			//astept sa fie generate cele doua fisiere (modificati timpul daca este necesar
			//Delay(4);
			
			//incarc informatiile privind rata de esantionare si numarul de valori
			FileToArray("wafeInfo.txt", waveInfo, VAL_INTEGER, 2, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			sampleRate = waveInfo[SAMPLE_RATE];
			npoints = waveInfo[NPOINTS];
			
			//alocare memorie pentru numarul de puncte
			waveData = (double *) calloc(npoints, sizeof(double));
			
			filt = (double *) calloc(npoints, sizeof(double));
			
			f = (double *) calloc(npoints, sizeof(double));
			
			//incarcare din fisierul .txt in memorie (vector)
			FileToArray("waveData.txt", waveData, VAL_DOUBLE, npoints, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			
			//afisare pe grapf
			PlotY(panel, PANEL_GRAPH_RAW_DATA, waveData, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
			
			MaxMin1D(waveData, npoints, &max, &indMax, &min, &indMin);
	
			for(int i=0;i<npoints-1;i++)
				if((waveData[i] > 0 && waveData[i+1] < 0) || (waveData[i] < 0 && waveData[i+1] > 0) || (waveData[i]==0))
					zeros++;
			
			Mean(waveData,npoints,&media);
			
			StdDev(waveData,npoints,&media,&dispersia);
			
			Median(waveData,npoints,&mediana);
			
			
			SetCtrlVal(panel, PANEL_MAX_VAL, max);
			SetCtrlVal(panel, PANEL_MIN_VAL, min);
			SetCtrlVal(panel, PANEL_NR_VAL_MAX, indMax);
			SetCtrlVal(panel, PANEL_NR_VAL_MIN, indMin);
			SetCtrlVal(panel, PANEL_NR_ZEROS, zeros);
			SetCtrlVal(panel, PANEL_VAL_MEDIE, media);
			SetCtrlVal(panel, PANEL_VAL_MEDIANA, mediana);
			SetCtrlVal(panel, PANEL_VAL_DISPERSIE, dispersia);
			
			Histogram(waveData,npoints,min-1,max+1,hist,axis,interv);
			DeleteGraphPlot (panel,PANEL_HISTOGRAM, -1, VAL_DELAYED_DRAW);
            PlotXY (panel,PANEL_HISTOGRAM, axis,  hist, interv, VAL_DOUBLE, VAL_SSIZE_T, VAL_VERTICAL_BAR, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED); 
			
			break;
	}
	return 0;
}

int CVICALLBACK RAW_DATA_FC (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK CB_PREV_FC (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(idstart-1>=0){
				SetCtrlVal(panel,PANEL_start_timer,idstart-1);
				SetCtrlVal(panel,PANEL_stop_timer,idstop-1);	
				
				GetCtrlVal(panel,PANEL_start_timer, &idstart);
				GetCtrlVal(panel,PANEL_stop_timer, &idstop);
				
				SetAxisScalingMode(panel,PANEL_GRAPH_RAW_DATA,VAL_BOTTOM_XAXIS,VAL_MANUAL,idstart*44100,idstop*44100);
			}
			break;
	}
	return 0;
}

int CVICALLBACK CB_NEXT_FC (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(idstop+1<7){
				SetCtrlVal(panel,PANEL_start_timer,idstart+1);
				SetCtrlVal(panel,PANEL_stop_timer,idstop+1);	
				
				GetCtrlVal(panel,PANEL_start_timer, &idstart);
				GetCtrlVal(panel,PANEL_stop_timer, &idstop);
				
				SetAxisScalingMode(panel,PANEL_GRAPH_RAW_DATA,VAL_BOTTOM_XAXIS,VAL_MANUAL,idstart*44100,idstop*44100);
			}
			break;
	}
	return 0;
}

int CVICALLBACK start_timer_FC (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK stop_timer_FC (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK SELECTARE_FILTRU (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	int val, dim;
	double alpha;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel, PANEL_FILTRU, &val);
			
			if(val==1){
				SetCtrlAttribute(panel, PANEL_DIM_FEREASTRA, ATTR_DIMMED, val);
				SetCtrlAttribute(panel , PANEL_VAL_ALPHA, ATTR_DIMMED, !val);
				GetCtrlVal(panel, PANEL_VAL_ALPHA, &alpha);
				filt = FitrOrdin1(alpha);
				Moment(filt,256,3,&skew);
				Moment(filt,256,4,&kurt);
			
				SetCtrlVal(panel, PANEL_skewness, skew);
				SetCtrlVal(panel, PANEL_kurtosis, kurt);
			}
			else{
				SetCtrlAttribute(panel, PANEL_DIM_FEREASTRA, ATTR_DIMMED, val);
				SetCtrlAttribute(panel , PANEL_VAL_ALPHA, ATTR_DIMMED, !val);
				GetCtrlVal(panel, PANEL_DIM_FEREASTRA, &dim);
				filt = mediere(dim);
				Moment(filt,256,3,&skew);
				Moment(filt,256,4,&kurt);
			
				SetCtrlVal(panel, PANEL_skewness, skew);
				SetCtrlVal(panel, PANEL_kurtosis, kurt);
			}
			break;
	}
	return 0;
}

int CVICALLBACK APLICA_FC (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	double min, max;
	switch (event)
	{
		case EVENT_COMMIT:
			SELECTARE_FILTRU(panel, PANEL_FILTRU, EVENT_COMMIT, 0, 0, 0);
			DeleteGraphPlot(panel, PANEL_GRAPH_RAW_DATA, -1, VAL_IMMEDIATE_DRAW);
			PlotY(panel, PANEL_GRAPH_RAW_DATA, waveData, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
			
			GetAxisScalingMode(panel,PANEL_GRAPH_RAW_DATA,VAL_LEFT_YAXIS,0,&min,&max);
			SetAxisScalingMode(panel,PANEL_GRAPH_FILTERED_DATA,VAL_LEFT_YAXIS,VAL_MANUAL,min,max);
			
			DeleteGraphPlot(panel, PANEL_GRAPH_FILTERED_DATA, -1, VAL_IMMEDIATE_DRAW);
			PlotY(panel, PANEL_GRAPH_FILTERED_DATA, filt, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_BLUE);
			break;
	}
	return 0;
}

int CVICALLBACK SAVE_FC (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	char fileName[256] = {0}, fileName1[256] = {0}, fileName2[256] = {0}, fileName3[256] = {0};
	switch (event)
	{
		case EVENT_COMMIT:
			sprintf(fileName, "Raw_Signal.jpg");
			GetCtrlDisplayBitmap(panel, PANEL_GRAPH_RAW_DATA, 1, &imgHandle);
			SaveBitmapToJPEGFile(imgHandle, fileName, JPEG_DCTFAST, 100);
			
			sprintf(fileName1, "Filtered_Signal.jpg");
			GetCtrlDisplayBitmap(panel, PANEL_GRAPH_FILTERED_DATA, 1, &imgHandle);
			SaveBitmapToJPEGFile(imgHandle, fileName1, JPEG_DCTFAST, 100);
			
			sprintf(fileName2, "Histogram.jpg");
			GetCtrlDisplayBitmap(panel, PANEL_HISTOGRAM, 1, &imgHandle);
			SaveBitmapToJPEGFile(imgHandle, fileName2, JPEG_DCTFAST, 100);
			
			sprintf(fileName3, "Anvelopa.jpg");
			GetCtrlDisplayBitmap(panel, PANEL_ANVELOPA, 1, &imgHandle);
			SaveBitmapToJPEGFile(imgHandle, fileName3, JPEG_DCTFAST, 100);
			
			
			break;
	}
	return 0;
}

int CVICALLBACK GEN_ANVELOPA_FC (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//LaunchExecutable("python anvelopa.py");
			//Delay(4);
			
			anvelopa = (double *) calloc(npoints, sizeof(double));
			
			FileToArray("anvelopa.txt", anvelopa, VAL_DOUBLE, npoints, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			
			DeleteGraphPlot(panel, PANEL_ANVELOPA, -1, VAL_IMMEDIATE_DRAW);
			PlotY(panel, PANEL_ANVELOPA, anvelopa, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS,VAL_BLUE);
			PlotY(panel, PANEL_ANVELOPA, waveData, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
			break;
	}
	return 0;
}

int CVICALLBACK main_panel_2 (int panel, int event, void *callbackData,
							  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface(0);
			break;
	}
	return 0;
}

int CVICALLBACK SWITCH_PANEL_FC (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			if(panel == panelHandle)
			{
				SetCtrlVal(panelHandle2, PANEL_2_SWITCH_PANEL, 1);
				DisplayPanel(panelHandle2);
				HidePanel(panel);
			}
			else
			{
				SetCtrlVal(panelHandle, PANEL_SWITCH_PANEL, 0);
				DisplayPanel(panelHandle);
				HidePanel(panel);
			}
			
			break;
	}
	return 0;
}

int CVICALLBACK SPECTRU_FC (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
int n = 0, npoints1 = npoints/2;
GetCtrlVal(panel,PANEL_2_IDC_NR_PCT,&n);

double *convertedSpectrum;
convertedSpectrum = (double*)calloc(npoints1/6,sizeof(double));
//frecventa estimata pentru spectrul de putere (maxim) din vectorul autoSpectrum
double powerPeak = 0.0;
//valoarea maxima din spectru de putere (din autoSpectrum)
double freqPeak = 0.0;
//variabila ce reprezinta pasul in domeniul frecventei
double df = 0.0;
//voltage signal - descriere a semnalului achizitionat
char unit[32] = "V";
//spectrul de putere cu un numar de valori egal cu jumatate din dimensiunea bufferuluide intrare
double *autoSpectrum;
autoSpectrum = (double*)calloc(npoints1/6,sizeof(double));
//
WindowConst winConst;

double *rawSignal;
rawSignal = (double*)calloc(npoints1,sizeof(double));

int sec = 0;
GetCtrlVal(panel,PANEL_2_IDC_SEC,&sec);
sec=sec*npoints;
int j=0;
for (int i=0;i<npoints-1;i+=2){
		rawSignal[j]=waveData[i];
		j++;
}
	switch (event)
	{
		case EVENT_COMMIT:
			

//aplatizare forma semnal la capetele intervalului
ScaledWindowEx(rawSignal,n,RECTANGLE,0,&winConst);
//partea pozitiva a spectrului scalat de putere pentru un semnal esantionat
AutoPowerSpectrum(rawSignal,npoints/6,1.0/sampleRate,autoSpectrum,&df);
//calculeaza puterea si frecventa corespunzatoare varfului din spectrul semnalului
PowerFrequencyEstimate(autoSpectrum,npoints1/6,-1.0,winConst,df,7,&freqPeak,&powerPeak);
//afisez pe interfata valorile determinate
SetCtrlVal(panel , PANEL_2_IDC_FREQ_PEAK, freqPeak);
SetCtrlVal(panel, PANEL_2_IDC_POWER_PEAK, powerPeak);
//Functia converteste spectrul de intrare (care este puterea, amplitudinea sau amplificarea)
//în formate alternative (linear, logarithmic, dB) ce permit o reprezentare grafica mai convenabila.
SpectrumUnitConversion(autoSpectrum,n,SPECTRUM_POWER,SCALING_MODE_LINEAR,DISPLAY_UNIT_VRMS,df,winConst,convertedSpectrum,unit);
//sterg graph-ul unde urmeaza sa plotez spectrul semnalului
DeleteGraphPlot (panel, PANEL_2_SPECTRU, -1, VAL_IMMEDIATE_DRAW);
//plotez spectrul semnalului
PlotWaveform( panel, PANEL_2_SPECTRU, convertedSpectrum, npoints1/12 ,VAL_DOUBLE, 1.0, 0.0, 0.0, df, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_DK_GREEN);
//PlotY(panel, PANEL_2_SPECTRU, convertedSpectrum, numRead/4, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_DK_GREEN);
break;
	}
	return 0;
}




int CVICALLBACK APLICA_FC2 (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	int sec;
	int N=0;
	int npoints1 = npoints/2;
	double *raw;
	int winType;
	double final[npoints/6];
	double window[npoints/6];
	int fcut;
	int order;
	int fpass;
	int signalType;
	static WindowConst winConst;
	double *powerSpectrum;
	double *convertedSpectrum;
	char unit[32]="V";
	double df=0.0;
	double coef[55];
	double powerPeak = 0.0;
	double freqPeak = 0.0;	
	powerSpectrum=(double*)calloc(npoints1/6,sizeof(double));
	convertedSpectrum=(double*)calloc(npoints1/6,sizeof(double));
	switch (event)
	{
		case EVENT_COMMIT:
			//ferestruirea
			DeleteGraphPlot (panel,PANEL_2_WINDOW, -1, VAL_IMMEDIATE_DRAW);
			GetCtrlVal(panel, PANEL_2_IDC_NR_PCT, &N);
			
			GetCtrlVal(panel,PANEL_2_IDC_SEC,&sec);
			
			GetCtrlVal(panel,PANEL_2_IDC_CUT_FREQ,&fcut);
			GetCtrlVal(panel,PANEL_2_IDC_ORDER,&order);
			GetCtrlVal(panel,PANEL_2_IDC_FPASS,&fpass);
			
			raw=(double*)calloc(npoints1/6,sizeof(double));
			int j = 0;
			for(int i=0;i<npoints1/6;i=i+2)
			{
				raw[j]=waveData[sec*npoints/6+i];
				j++;
			}	 
			
			GetCtrlVal(panel,PANEL_2_WINDOW_TYPE,&winType);
			LinEv1D(raw,npoints1/6,0,1,window);	   
			
			switch (winType)
			{
				case 0:
					HanWin(window,npoints1/6);
					break;
				case 1:
					BkmanWin(window,npoints1/6);
					break;
			}
			DeleteGraphPlot (panel,PANEL_2_WINDOW, -1, VAL_IMMEDIATE_DRAW);
			PlotY (panel,PANEL_2_WINDOW, window, npoints1/6, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
			
			
			Mul1D(raw,window,npoints1/6,final);
			DeleteGraphPlot (panel,PANEL_2_RAW_DATA, -1, VAL_IMMEDIATE_DRAW);
			PlotY (panel,PANEL_2_RAW_DATA, raw, npoints1/12, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
			
			
			
			GetCtrlVal(panel,PANEL_2_FILTER_TYPE,&signalType);
			
			double *filteredSignal;
			filteredSignal = (double *) calloc(npoints1, sizeof(double));
			
			switch(signalType)
			{
				case 0:
					double beta = 0;
					if(winType == 0){
						beta = 3.86;
					}
					else{
						beta = 7.04;
					}
					Ksr_HPF (sampleRate, fcut, 55, coef,beta);
					Convolve(final,npoints1/6,coef,55,filteredSignal);
					break;
					
				case 1:
 					Bw_HPF(final,npoints1/6,sampleRate,fcut,order,filteredSignal);
				   	break;

						   
			}
			
			DeleteGraphPlot (panel, PANEL_2_Window_filt, -1, VAL_IMMEDIATE_DRAW);
			PlotY (panel, PANEL_2_Window_filt, final, npoints1/12, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
			
				
			//afisam spectrului filtrat
			ScaledWindowEx (filteredSignal, N, RECTANGLE_, 0, &winConst);
			DeleteGraphPlot (panel,PANEL_2_Spectru_filt, -1, VAL_IMMEDIATE_DRAW);
        	AutoPowerSpectrum (filteredSignal, npoints/6, 1.0/sampleRate, powerSpectrum, &df);
			PowerFrequencyEstimate(powerSpectrum,npoints1/6,-1.0,winConst,df,7,&freqPeak,&powerPeak);
			SpectrumUnitConversion(powerSpectrum, N, 0, SCALING_MODE_LINEAR, DISPLAY_UNIT_VPK, df, winConst,convertedSpectrum, unit);
			PlotY (panel,PANEL_2_Spectru_filt, convertedSpectrum, npoints1/12, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
			break;
	}
	return 0;
}

int CVICALLBACK SAVE_FILT_FC (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	char fileName[256] = {0}, fileName1[256] = {0}, fileName2[256] = {0}, fileName3[256] = {0};
	switch (event)
	{
		case EVENT_COMMIT:
			sprintf(fileName, "SPECTRU.jpg");
			GetCtrlDisplayBitmap(panel, PANEL_2_SPECTRU, 1, &imgHandle);
			SaveBitmapToJPEGFile(imgHandle, fileName, JPEG_DCTFAST, 100);
			
			sprintf(fileName1, "WINDOW.jpg");
			GetCtrlDisplayBitmap(panel, PANEL_2_WINDOW, 1, &imgHandle);
			SaveBitmapToJPEGFile(imgHandle, fileName1, JPEG_DCTFAST, 100);
			
			sprintf(fileName2, "WINDOW_FILT.jpg");
			GetCtrlDisplayBitmap(panel, PANEL_2_Window_filt, 1, &imgHandle);
			SaveBitmapToJPEGFile(imgHandle, fileName2, JPEG_DCTFAST, 100);
			
			sprintf(fileName3, "SPECTRU_FILT.jpg");
			GetCtrlDisplayBitmap(panel, PANEL_2_Spectru_filt, 1, &imgHandle);
			SaveBitmapToJPEGFile(imgHandle, fileName3, JPEG_DCTFAST, 100);
			
			
			break;
	}
	return 0;
}
