#include <analysis.h>
#include <ansi_c.h>
#include <utility.h>
#include <cvirte.h>		
#include <userint.h>
#include "LowLevelDriver64.h" 
#include "IODrive2007DAC.h" 
#include "DELAYMIC.h"
#include "nir_finel_project.h" 

static int panelHandle;
static double  coefficients[10];

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "nir_finel_project.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	setParallelPortAddr(0x3FF8, 0x3FF4);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	return 0;
}

int CVICALLBACK QuitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			AnalogOut(0, 0);
			AnalogOut(1, 0);
			BuzzerEnable(0); 
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK fast_test (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{ double volt_fast_test=0, volt_in;
  int x=0;
  int time_interval=200;
  double volt_array[time_interval];
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, PANEL_NUMERICSLIDE, &volt_fast_test);
			AnalogOut(0, volt_fast_test);
			SetAnalogInx(0);
			for (x=0;x<time_interval;x++){
				volt_in = AnalogIn(0);
				volt_array[x]=volt_in;
				Delay(0.0001);
			}
			PlotY (panelHandle, PANEL_GRAPH, volt_array, time_interval, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 0.001, VAL_RED);
			SetCtrlAttribute (panelHandle, PANEL_V_in_vs_V_out, ATTR_LABEL_TEXT, "V_in_vs_V_out  ");
			AnalogOut(0, 0);
			AnalogOut(1, 0);
			BuzzerEnable(0);
			break;
	}
	return 0;
}


int CVICALLBACK Calibration (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{ double volt_out=0,minimum_volt=0, volt_in=0,maximum_volt=0;
  int x=0,number_of_steps;
  int time_interval=75;
  double volt_array[100*time_interval];
  double volt_out_array[100*time_interval];
  double milisec_array[5000];
  double  polynomial_values[10000];
  double  mean_squared_error;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_minimum_volt, &minimum_volt);
			GetCtrlVal (panelHandle, PANEL_maximum_volt, &maximum_volt);
			GetCtrlVal (panelHandle, PANEL_number_of_steps, &number_of_steps);
			SetAnalogInx(0);
			
			for (x=0,volt_out=minimum_volt;volt_out<=maximum_volt;volt_out+=((maximum_volt-minimum_volt)/number_of_steps)){
					AnalogOut(0, volt_out); 
					volt_in = AnalogIn(0);
					volt_array[x]=volt_in;
					volt_out_array[x]=volt_out;
					Delay(0.075);
					x++;}
			
			PlotY (panelHandle, PANEL_GRAPH, volt_array+1, number_of_steps, VAL_DOUBLE, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_DK_CYAN);
			for(int i = 0; i < time_interval*5; i++)
  				milisec_array[i] = i;
			
			SetCtrlAttribute (panelHandle, PANEL_V_in_vs_V_out, ATTR_LABEL_TEXT, "V_in_vs_V_out  ");
			PlotXY (panelHandle, PANEL_V_in_vs_V_out,volt_out_array+1 , volt_array+1, number_of_steps, VAL_DOUBLE, VAL_DOUBLE, VAL_SCATTER, VAL_SOLID_CIRCLE, VAL_SOLID, 1, VAL_RED);
			PolyFit (volt_array+10,volt_out_array+10 , number_of_steps-10, 2, polynomial_values, coefficients, &mean_squared_error);
			SetCtrlAttribute (panelHandle, PANEL_run_ope_loop, ATTR_VISIBLE, 1);
			SetInputMode (panelHandle, PANEL_run_ope_loop, 1);
			AnalogOut(0, 0);
			AnalogOut(1, 0);
			BuzzerEnable(0);
			break;}
	return 0;}




int CVICALLBACK PID (int panel, int control, int event,
					 void *callbackData, int eventData1, int eventData2)
{   int run_steps=100,x=0;
	double wish_volt=0,volt_out=0,current_volt=0;
	double Kp=2.1,Ki=1.1,Kd=1.1;
	double last_error=0,error,Integral=0,derivative=0;
	double volt_array_in[run_steps*8];
  	double volt_array_out[run_steps*8];
	double error_array[run_steps*8];
	int kp_On_Off=1,ki_On_Off=1,kd_On_Off=1;
	int Interruption_steps=0,Interruption_start=0,Interrupt_On_Off=0,y=0;
	double Interruption_volt=0;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_wish_volt, &wish_volt);
			GetCtrlVal (panelHandle, PANEL_K_p, &Kp);
			GetCtrlVal (panelHandle, PANEL_K_I, &Ki);
			GetCtrlVal (panelHandle, PANEL_K_d, &Kd);
			GetCtrlVal (panelHandle, PANEL_kp_On_Off, &kp_On_Off);
			GetCtrlVal (panelHandle, PANEL_ki_On_Off, &ki_On_Off);
			GetCtrlVal (panelHandle, PANEL_kd_On_Off, &kd_On_Off);
			
			GetCtrlVal (panelHandle, PANEL_Interruption_steps, &Interruption_steps);
			GetCtrlVal (panelHandle, PANEL_Interruption_start, &Interruption_start);
			GetCtrlVal (panelHandle, PANEL_Interruption_volt, &Interruption_volt);	  
			GetCtrlVal (panelHandle, PANEL_Interrupt_On_Off, &Interrupt_On_Off);
			
			Kp=Kp*kp_On_Off;
			Ki=Ki*ki_On_Off;
			Kd=Kd*kd_On_Off;
			AnalogOut(0, volt_out);
			Delay(0.20);
			while (x<run_steps){
				current_volt= AnalogIn(0);
				error = wish_volt-current_volt;
				Integral=Integral+error;
				derivative= error-last_error;
				volt_out= (Kp*error)+(Ki*Integral)+(Kd*derivative); 
				if(volt_out>10){volt_out=10;}
				AnalogOut(0, volt_out);
				volt_array_in[x]=current_volt;
				volt_array_out[x]=volt_out; 
				error_array[x]=error;
				last_error=error;
				if(Interrupt_On_Off==1 & x>Interruption_start &y<Interruption_steps){
					AnalogOut(1, Interruption_volt);
					y++;}
				else{AnalogOut(1, 0);}
				Delay(0.01);
				x++;
			}
			
			PlotLine (panelHandle, PANEL_GRAPH, 0, wish_volt, 100, wish_volt, VAL_GREEN);
			PlotY (panelHandle, PANEL_GRAPH, volt_array_in, run_steps, VAL_DOUBLE, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);
			PlotY (panelHandle, PANEL_GRAPH, error_array, run_steps, VAL_DOUBLE, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_YELLOW);
			SetAxisRange (panelHandle, PANEL_V_in_vs_V_out, VAL_MANUAL, 0.0, 100.0, VAL_MANUAL, 0.0, 10.0);
			PlotY (panelHandle, PANEL_V_in_vs_V_out, volt_array_out, run_steps, VAL_DOUBLE, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_WHITE);
			SetCtrlAttribute (panelHandle, PANEL_V_in_vs_V_out, ATTR_LABEL_TEXT, "out volt vs time");
			SetAxisRange (panelHandle, PANEL_GRAPH, VAL_MANUAL, 0.0, 100.0, VAL_MANUAL, 0.0, 10.0);
			AnalogOut(0, 0);
			AnalogOut(1, 0);
			break;
	}
	return 0;
}

int CVICALLBACK clear_graph (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DeleteGraphPlot (panelHandle, PANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW);
			DeleteGraphPlot (panelHandle, PANEL_V_in_vs_V_out, -1, VAL_IMMEDIATE_DRAW);
			break;
	}
	return 0;
}

int CVICALLBACK run_ope_loop (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{double wish_volt=0,volt_out=0,volt_in=0;
	int x=0;
   	double volt_array_in[1000];
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_wish_volt, &wish_volt);
			volt_out=(coefficients[0]+coefficients[1]*wish_volt+coefficients[1]*wish_volt*wish_volt);
			AnalogOut(0, volt_out);
			for (x=0;x<30;x++){
					volt_in = AnalogIn(0);
					volt_array_in[x]=volt_in;
					Delay(0.02);}
			AnalogOut(0, 0);
			AnalogOut(1, 0);
			PlotY (panelHandle, PANEL_GRAPH, volt_array_in, 30, VAL_DOUBLE, VAL_FAT_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);	

			break;
	}
	return 0;
}
