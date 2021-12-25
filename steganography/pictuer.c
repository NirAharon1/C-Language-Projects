#include <formatio.h>
#include "toolbox.h"
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "pictuer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h> 
#define MAX_COLOR 255//BGR format

static int panelHandle;
static int bmpHandler,ENCRYPTED_PICTURE_bmpHandler, bmpHandlerTemp,saving_Temp;
int ColorSize, BitSize, MaskSize;
int ByteInRow, Pixel, pWidth, pHeight;
int ByteInRow2, Pixel2, pWidth2, pHeight2;
static int max_length;
unsigned char *MyPicData;
unsigned char *ENCRYPTED_PICTURE_MyPicData;
unsigned char *NewData;
unsigned char *alpha2;
unsigned char *TempPicData,*Data_steganography;
char *  itoa ( int value, char * str, int base );

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "pictuer.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	SetCtrlVal (panelHandle, PANEL_LED, 0);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	free(MyPicData);
	return 0;
}

int CVICALLBACK QuitCallback (int panel, int control, int event,
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

int CVICALLBACK add_new_picture (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)//insert new picture
{
	char FileName[260],counter_string[50];
	switch (event)
	{
		case EVENT_COMMIT:
			int error =FileSelectPopup ("", "*.jpg", "", "", VAL_LOAD_BUTTON, 0, 0, 1, 1, FileName);//select picture and drew it on canvas
			if(error<=0){break;}//catch an error if the user haven't chosen an image
			GetBitmapFromFile (FileName, &bmpHandler);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS_ORIGINAL, bmpHandler, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
			GetBitmapInfo (bmpHandler, &ColorSize, &BitSize, &MaskSize);
			MyPicData = (unsigned char*) malloc(BitSize);//allocating memory to save image data
			GetBitmapData (bmpHandler, &ByteInRow, &Pixel, &pWidth, &pHeight, NULL, MyPicData, NULL);
			SetInputMode (panelHandle, PANEL_Steganography, 1);
			SetInputMode (panelHandle, PANEL_STRING, 1);
			max_length= pHeight/8;
			SetCtrlAttribute (panelHandle, PANEL_STRING, ATTR_MAX_ENTRY_LENGTH, max_length);//setting a finite length of the input text.
			snprintf(counter_string,50,"%d characters out of %d have been left",max_length,max_length);
			SetCtrlVal (panelHandle, PANEL_COUNT,counter_string);
			break;
	}
	return 0;
}

int CVICALLBACK NEGATIVE (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)//get the negative of the image
{
int k,j;
unsigned char *TempPicData;
	switch (event)
	{
		case EVENT_COMMIT:
			if(MyPicData==NULL){break;}//error handling- No image
			SetCtrlVal (panelHandle, PANEL_LED, 1);//processing indicator on
			TempPicData = MyPicData;
			for (k=0; k<pHeight; k++)
				for (j=0; j<ByteInRow; j++)
					if(k*ByteInRow+j== BitSize){
						break;}
					else{
					TempPicData[k*ByteInRow+j] ^= -1;}//trans every unsigned char byte to his opposite  
			NewBitmap (ByteInRow, Pixel, pWidth, pHeight, NULL, TempPicData, NULL,&bmpHandlerTemp);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS_2, bmpHandlerTemp,VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
			DiscardBitmap (bmpHandlerTemp);
			SetCtrlVal (panelHandle, PANEL_LED, 0);//processing indicator off 
			break;
	}
	return 0;
}

int CVICALLBACK save1 (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)//save the data of the original image to a text file  
{
int k,j,l,zz=0;
	switch (event)
	{
		case EVENT_COMMIT:
			FILE *pFile;//file pointer
			pFile = fopen("original image to a text.txt","w");
			GetBitmapInfo (bmpHandler, &ColorSize, &BitSize, &MaskSize);
			MyPicData = (unsigned char*) malloc(BitSize);
			GetBitmapData (bmpHandler, &ByteInRow, &Pixel, &pWidth, &pHeight, NULL, MyPicData, NULL);
			for (k=0; k<pHeight; k++){//iterate of each line 
					for (j=0,l=0; j<ByteInRow; j++){//iterate of each row 
					fprintf(pFile,"%d\t",MyPicData[k*ByteInRow+j]);
					if (l==3){
						fprintf(pFile,"\n");
						l=0;}
					else{
						l++;}
					zz+=1;//count the total amount of pixels
				}
			fprintf(pFile,"\n\n\n");}
			fprintf(pFile,"the total amount of pixels is %d",zz);
			fclose(pFile);
			break;
	}
	return 0;
}

int CVICALLBACK save2 (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)///save the data of the manipulated image to a text file
{
int k,j,l,zz=0;
int yyy_hand;
NewData = (unsigned char*) malloc(BitSize);
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlBitmap (panelHandle, PANEL_CANVAS_2, 0, &yyy_hand);
			GetBitmapDataEx (yyy_hand, &ByteInRow2, &Pixel2, &pWidth2, &pHeight2, NULL, NewData, NULL, alpha2);
			FILE *pFile;
			pFile = fopen("manipulated image to a text.txt.txt","w");
			for (k=0; k<pHeight2; k++){
					for (j=0,l=0; j<ByteInRow2; j++){
					fprintf(pFile,"%d\t",NewData[k*ByteInRow2+j]);
					if (l==3){
						fprintf(pFile,"\n");
						l=0;}
					else{
						l++;}
					zz+=1;//count the total amount of pixels 
				}
			fprintf(pFile,"\n\n\n");}
			fprintf(pFile,"the total amount of pixels is %d",zz);
			fclose(pFile);
			break;
	}
	return 0;
}

int CVICALLBACK color_change (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)//increase the value of blue=0//green=1//red=2 by 3
{
int k,j,xxx=0,yyy=0;
unsigned char *TempPicData=0;
	switch (event)
	{
		case EVENT_COMMIT:
			if(MyPicData==NULL){break;}//error handling- No image
			SetCtrlVal (panelHandle, PANEL_LED, 1);//processing indicator on 
			switch (control){//using "switch" to save code line 
					case PANEL_red_up:
					  	xxx=2;//the position of red in [B,G,R,A] array
						yyy=3;//increase by 3
						break;
					case PANEL_red_down:
						xxx=2;
						yyy=-3;
						break;
					case PANEL_green_up:
						xxx=1;
						yyy=3;
						break;
					case PANEL_green_down:
						xxx=1;
						yyy=-3;
						break;
					case PANEL_blue_up:
						xxx=0;
						yyy=3;
						break;
					case PANEL_blue_down:
						xxx=0;
						yyy=-3;
						break;}
			TempPicData = MyPicData;			
			for (k=0; k<pHeight; k++)
							for (j=xxx; j<ByteInRow; j+=4)
								if(k*ByteInRow+j== BitSize){
									break;}
								else{
									if(TempPicData[k*ByteInRow+j]>4||TempPicData[k*ByteInRow+j]<252){//don't pass over 255 or less than 1
										TempPicData[k*ByteInRow+j] += yyy;}}
													
			NewBitmap (ByteInRow, Pixel, pWidth, pHeight, NULL, TempPicData, NULL,&bmpHandlerTemp);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS_2, bmpHandlerTemp,VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
			DiscardBitmap (bmpHandlerTemp);
			SetCtrlVal (panelHandle, PANEL_LED, 0);//processing indicator off
			break;
	}
	return 0;
}

int CVICALLBACK Black_White (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)//tern colored image to black and white by change the [B,G,R,A] array
{																				//by change the [B,G,R,A] array to [255,255,255,0] or [0,0,0,0]
int k,j,THRESHOLD;
unsigned char *TempPicData;
unsigned char WHITE=255,BLACK=0,buffer=0; 
	switch (event)
	{
		case EVENT_COMMIT:
			if(MyPicData==NULL){break;}//error handling- No image
			SetCtrlVal (panelHandle, PANEL_LED, 1);//processing indicator on 
			GetBitmapData (bmpHandler, &ByteInRow, &Pixel, &pWidth, &pHeight, NULL, MyPicData, NULL);
			GetCtrlVal (panelHandle, PANEL_Black_and_White_scale, &THRESHOLD);//read the threshold value from the scale.
			TempPicData = MyPicData;
			for (k=0; k<pHeight-1; k++)
				for (j=0; j<ByteInRow-4; j+=4)
					if(k*ByteInRow+j== BitSize){
						break;}
					else{
					buffer=((MyPicData[k*ByteInRow+j]+MyPicData[k*ByteInRow+j+1]+MyPicData[k*ByteInRow+j+2])/3> THRESHOLD) ? WHITE : BLACK;
					TempPicData[k*ByteInRow+j] = buffer;
					TempPicData[k*ByteInRow+j+1] = buffer;
					TempPicData[k*ByteInRow+j+2] = buffer;}
			
			NewBitmap (ByteInRow, Pixel, pWidth, pHeight, NULL, TempPicData, NULL,&bmpHandlerTemp);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS_2, bmpHandlerTemp,VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
			DiscardBitmap (bmpHandlerTemp);
			SetCtrlVal (panelHandle, PANEL_LED, 0);//processing indicator off
			break;
	}
	return 0; 
	
}


int CVICALLBACK blurring (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
int k,j,x,on_off,blurring_cycle=1;
unsigned char *TempPicData;
float v=1.0 / 9.0;
float z=1.0 / 24.0;
float kernel[3][3];
float flat_kernel[3][3]={{v,v,v},	    	 //initialize the flat blurrring kernel
		   			   	 {v,v,v},
		  		    	 {v,v,v}};
float gaussian_kernel[3][3]={{1*z,3*z,1*z},	 //initialize the gaussian blurrring kernel
		   			   	     {2*z,8*z,2*z},
		  		    	     {1*z,3*z,1*z}};

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlAttribute (panelHandle, PANEL_BINARYSWITCH, ATTR_CTRL_VAL, &on_off);
			if(on_off==0){
				memcpy(kernel, flat_kernel,36);}
			else{
				memcpy(kernel, gaussian_kernel,36);}
			if(MyPicData==NULL){break;}//error handling- No image
			SetCtrlVal (panelHandle, PANEL_LED, 1);//processing indicator on 
			TempPicData = MyPicData;
			GetCtrlVal (panelHandle, PANEL_blurring_cycle, &blurring_cycle);
			for(x=0;x<blurring_cycle;x++){
					for (k=1; k<pHeight-2; k++){
						for (j=4; j<ByteInRow-4; j+=4){
					if(k*ByteInRow+j== BitSize){
			 			break;}
					else{//convolution between the data array and the kernel array 
						TempPicData[k*ByteInRow+j] =((float)kernel[0][0])*MyPicData[k*ByteInRow+j-4+((-1)*ByteInRow)]+((float)kernel[0][1])*MyPicData[k*ByteInRow+j+((-1)*ByteInRow)]+((float)kernel[0][2])*MyPicData[k*ByteInRow+j+4+((-1)*ByteInRow)]
												   +((float)kernel[1][0])*MyPicData[k*ByteInRow+j-4+(0*ByteInRow)]+((float)kernel[1][1])*MyPicData[k*ByteInRow+j+(0*ByteInRow)]+((float)kernel[1][2])*MyPicData[k*ByteInRow+j+4+(0*ByteInRow)]
												   +((float)kernel[2][0])*MyPicData[k*ByteInRow+j-4+(1*ByteInRow)]+((float)kernel[2][1])*MyPicData[k*ByteInRow+j+(1*ByteInRow)]+((float)kernel[2][1])*MyPicData[k*ByteInRow+j+4+(1*ByteInRow)];
						
						TempPicData[k*ByteInRow+j+1] =((float)kernel[0][0])*MyPicData[k*ByteInRow+j-4+1+((-1)*ByteInRow)]+((float)kernel[0][1])*MyPicData[k*ByteInRow+j+1+((-1)*ByteInRow)]+((float)kernel[0][2])*MyPicData[k*ByteInRow+j+4+1+((-1)*ByteInRow)]
												     +((float)kernel[1][0])*MyPicData[k*ByteInRow+j-4+1+(0*ByteInRow)]+((float)kernel[1][1])*MyPicData[k*ByteInRow+j+1+(0*ByteInRow)]+((float)kernel[1][2])*MyPicData[k*ByteInRow+j+4+1+(0*ByteInRow)]
												     +((float)kernel[2][0])*MyPicData[k*ByteInRow+j-4+1+(1*ByteInRow)]+((float)kernel[2][1])*MyPicData[k*ByteInRow+j+1+(1*ByteInRow)]+((float)kernel[2][1])*MyPicData[k*ByteInRow+j+4+1+(1*ByteInRow)]; 
						
						TempPicData[k*ByteInRow+j+2] =((float)kernel[0][0])*MyPicData[k*ByteInRow+j-4+2+((-1)*ByteInRow)]+((float)kernel[0][1])*MyPicData[k*ByteInRow+j+2+((-1)*ByteInRow)]+((float)kernel[0][2])*MyPicData[k*ByteInRow+j+4+2+((-1)*ByteInRow)]
												     +((float)kernel[1][0])*MyPicData[k*ByteInRow+j-4+2+(0*ByteInRow)]+((float)kernel[1][1])*MyPicData[k*ByteInRow+j+2+(0*ByteInRow)]+((float)kernel[1][2])*MyPicData[k*ByteInRow+j+4+2+(0*ByteInRow)]
												     +((float)kernel[2][0])*MyPicData[k*ByteInRow+j-4+2+(1*ByteInRow)]+((float)kernel[2][1])*MyPicData[k*ByteInRow+j+2+(1*ByteInRow)]+((float)kernel[2][1])*MyPicData[k*ByteInRow+j+4+2+(1*ByteInRow)];}}}}
					
			NewBitmap (ByteInRow, Pixel, pWidth, pHeight, NULL, TempPicData, NULL,&bmpHandlerTemp);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS_2, bmpHandlerTemp,VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
			DiscardBitmap (bmpHandlerTemp);
			SetCtrlVal (panelHandle, PANEL_LED, 0);//processing indicator off
			break;
	}
	return 0;
}

int CVICALLBACK Steganography (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)//insert text on top of image in hidden way
{																				  //get text from textbox
int i,l,j,k,zz=0;																  //converting the text to binary
unsigned char x; 																  //separate each byte to zero and one
	switch (event)																  //add the value of bit to the red value in the [B,G,R,A] array
	{
		case EVENT_COMMIT:
			SetCtrlVal (panelHandle, PANEL_LED, 1);//processing indicator on 
			static int stringLength;
			static char *secret_massage = 0;
			GetBitmapData (bmpHandler, &ByteInRow, &Pixel, &pWidth, &pHeight, NULL, MyPicData, NULL);
			Data_steganography = MyPicData;
			GetCtrlAttribute (panelHandle, PANEL_STRING, ATTR_STRING_TEXT_LENGTH, &stringLength);
			secret_massage = malloc ((stringLength + 1) * sizeof (char));
			GetCtrlVal (panelHandle, PANEL_STRING, secret_massage);

			FILE *pFile2;
			pFile2 = fopen("input in binary.txt","w");
			for (i=0; i<stringLength; i++){
				for(l=7,j=2; l>=0; l--, j+=4){
					x=(secret_massage[i]&(1<<l))?1:0;//convert ascii character to binary using "<<" operator
					Data_steganography[i*ByteInRow+j]+=x;//add x value of 1 or 0 to the red pixel
					fprintf(pFile2,"%d",x);}
				fprintf(pFile2,"\n");}//%c
			fclose(pFile2);
			FILE *pFile;
			pFile = fopen("image after Steganography.txt","w");
			for (k=0; k<pHeight; k++){
					for (j=0,l=0; j<ByteInRow; j++){
					fprintf(pFile,"%d\t",Data_steganography[k*ByteInRow+j]);
					if (l==3){
						fprintf(pFile,"\n");
						l=0;}
					else{
						l++;}
					zz+=1;
				}
			fprintf(pFile,"\n\n\n");}
			fprintf(pFile,"%d",zz);
			fclose(pFile);
			
			NewBitmap (ByteInRow, Pixel, pWidth, pHeight, NULL, Data_steganography, NULL,&bmpHandlerTemp); 
			SaveBitmapToBMPFile (bmpHandlerTemp, "NewBitmap.BMP");
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS_2, bmpHandlerTemp,VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
			SetInputMode (panelHandle, PANEL_Decrypt, 1);
			SetCtrlVal (panelHandle, PANEL_LED, 0);//processing indicator off
			break;
	}
	return 0;
}

int CVICALLBACK Decrypt (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)//get the hidden message from the original image and encrypt the image 
{
int i,j,l,x=0,q;
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlVal (panelHandle, PANEL_LED, 1);//processing indicator on 
			char str[1024]="";
			if(ENCRYPTED_PICTURE_MyPicData==NULL){
				ENCRYPTED_PICTURE_MyPicData = (unsigned char*) malloc(BitSize);
				GetBitmapFromFile ("NewBitmap.BMP",&bmpHandlerTemp );
				GetBitmapData (bmpHandlerTemp, &ByteInRow, &Pixel, &pWidth, &pHeight, NULL, ENCRYPTED_PICTURE_MyPicData, NULL);
				GetBitmapData (bmpHandler, NULL, NULL, NULL, NULL, NULL, MyPicData, NULL);
				 
			}
			FILE *pFile2;
			pFile2 = fopen("decrypt massage.txt","w");
			for (i=0; i<pHeight; i++){
				int t=1;
				char xxx[100]="";
				for(l=7,j=2,q=0; l>=0; l--, j+=4,t*=10,q++){
					x=ENCRYPTED_PICTURE_MyPicData[i*ByteInRow+j]-MyPicData[i*ByteInRow+j];
					sprintf (&xxx[q], "%d", x);}
					if (strcmp(xxx,"00000000") == 0){//stop after the last character to save time
						fprintf(pFile2,"end\nthe string is ");
					 	break;}
					unsigned char c;
					c = (unsigned char)strtol(xxx, 0, 2);//convert binary to ascii character
					int len = strlen(str);
					str[len] = c;
					str[len+1]='\0';
				fprintf(pFile2,"%s %c\n",xxx,c);}
				fprintf(pFile2,"%s\n",str);
			DeleteTextBoxLines (panelHandle, PANEL_STRING_2, 0, -1);
			SetCtrlVal (panelHandle, PANEL_STRING_2, str);
			SetInputMode (panelHandle, PANEL_Decrypt, 0);
			fclose(pFile2);
			ENCRYPTED_PICTURE_MyPicData= NULL;
			SetCtrlVal (panelHandle, PANEL_LED, 0);//processing indicator off
			break;
	}
	return 0;
}

int CVICALLBACK ADD_ENCRYPTED_PICTURE (int panel, int control, int event,
									   void *callbackData, int eventData1, int eventData2) 
{																						  
	char ENCRYPTED_PICTURE_FileName[260];
	switch (event)
	{
		case EVENT_COMMIT:
			int error = FileSelectPopup ("", "*.BMP", "", "", VAL_LOAD_BUTTON, 0, 0, 1, 1, ENCRYPTED_PICTURE_FileName);
			if(error<=0){break;}//catch an error if the user haven't chosen an image 
			GetBitmapFromFile (ENCRYPTED_PICTURE_FileName, &ENCRYPTED_PICTURE_bmpHandler);
			CanvasDrawBitmap (panelHandle, PANEL_CANVAS_2, ENCRYPTED_PICTURE_bmpHandler, VAL_ENTIRE_OBJECT, VAL_ENTIRE_OBJECT);
			ENCRYPTED_PICTURE_MyPicData = (unsigned char*) malloc(BitSize);
			GetBitmapData (ENCRYPTED_PICTURE_bmpHandler, &ByteInRow, &Pixel, &pWidth, &pHeight, NULL, ENCRYPTED_PICTURE_MyPicData, NULL);
			SetInputMode (panelHandle, PANEL_Decrypt, 1);
			break;
	}
	return 0;
}

int CVICALLBACK add_text_encrypt (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)//Limits the number of character that can be put
{																					 //in textbox to prevent over the limit
int number_of_lines,total_length=0,length_of_line,i;								 
	switch (event)
	{
		case EVENT_KEYPRESS:
			char counter_string2[50];
			GetNumTextBoxLines (panelHandle, PANEL_STRING, &number_of_lines);
			for (i = 0; i < number_of_lines; i++) {
			GetTextBoxLineLength (panelHandle, PANEL_STRING, i, &length_of_line);
			total_length+=length_of_line;}
			snprintf(counter_string2,50,"%d characters out of %d have been left",max_length-total_length-i,max_length);//update the string
			SetCtrlVal (panelHandle, PANEL_COUNT,counter_string2);

			break;
	}
	return 0;
}

int CVICALLBACK saving (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
char FileName[260];
	switch (event)
	{
		case EVENT_COMMIT:
			FileSelectPopup ("", "*.BMP", "", "manipulated image", VAL_SAVE_BUTTON, 0, 0, 1, 1, FileName);
			GetCtrlBitmap (panelHandle, PANEL_CANVAS_2, NULL, &saving_Temp);
			SaveBitmapToJPEGFile (saving_Temp, FileName, JPEG_DCTFLOAT, 100);
			DiscardBitmap (saving_Temp);
			break;

			break;
	}
	return 0;
}
