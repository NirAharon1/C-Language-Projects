# Welcome to my C language projects

## <span style="color:red">[Project 1 -Steganography](https://github.com/NirAharon1/C-Language-Projects/tree/main/steganography "steganography") </span>

This C project implements an algorithm for encrypting text data of a chosen image.            
The algorithm takes advantage of bit-wise operation, so the change in the image is undetectable for the naked eye.
also, I implement a demonstration of simple image processing technics.

<img src="steganography/Steganography Algorithm using LSB Replacement.png" width="538" height="227">

### The encrypting function
```c
int CVICALLBACK Steganography(int panel, int control, int event) {
  int i,l,j;							
  unsigned char x;
  GetBitmapData (bmpHandler, &ByteInRow, &Pixel, &pWidth, &pHeight);
  secret_massage = malloc ((stringLength + 1) * sizeof (char));
  for (i=0; i<stringLength; i++){
    for(l=7,j=2; l>=0; l--, j+=4){
        x=(secret_massage[i]&(1<<l))?1:0; // convert ascii character to binary using "<<" operator
        Data_steganography[i*ByteInRow+j]+=x;}} //add x value of 1 or 0 to the red pixel
  NewBitmap (ByteInRow, Pixel, pWidth, pHeight, NULL, Data_steganography, NULL,&bmpHandlerTemp);}
```

## <span style="color:red">[Project 2 -PID controller](https://github.com/NirAharon1/C-Language-Projects/tree/main/PID%20controller "steganography") </span>
This project present GUI that recived data from a physical sensor that sends data with an RS-232 cable to a microcontroller.
the PID controller analyzes the sensor and give order to the physical heating element to heat the system in a supervised way forming control loop.
With the GUI you can adjust the parameters of PID to manage the heating rate and prevent the burning of the heating element.
- P - proportional
- I - integral
- D - derivative

<img src="PID controller/PID-controller.jpg" width="538" height="227">