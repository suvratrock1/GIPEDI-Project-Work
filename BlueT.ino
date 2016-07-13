#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); //Rx, Tx

    const int analogIn = A0;
   
    int mVperAmp = 100; 
    int RawValue= 0;
    int ACSoffset = 2500;
    double Voltage = 0;
    double Amps = 0;
    int app;
    double a[100];
    double b[100];
    double c[100];
    unsigned long ptime=0;
void setup()
{
    mySerial.begin(9600);
    ask();
    current();
    dp();
}
void loop()
{
  unsigned long ctime=millis();
  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 1023.0) * 5000; // Gets you mV
  Amps = ((Voltage - ACSoffset) / mVperAmp);
  Amps=Amps+0.12;
   if(Amps<0)
  {
    Amps=Amps*(-1);
  }
  
  int r;
int n;

for(r=1;r<=app;r++){
 n=app;
ga(b,n,r);
}

if((ctime-ptime)>60000){
  result();
   ptime=ctime;
  }
 
}


void ch(double b[], double data[], int start, int end, int index, int r,int ind[]){
double sum=0;
if(index==r){
for(int j=0;j<r;j++)
{sum=sum+data[j]; } check(sum, ind, r); return; 
}
for(int i=start;i<=end && end-i+1>=r-index;i++){
data[index]=b[i]; ind[index]=i;
ch(b,data,i+1,end,index+1,r,ind);
}
}

void ga(double b[], int n, int r){
double data[r]; int ind[r];
ch(b,data,0,n-1,0,r,ind);
}

void check(double sum, int ind[],int r){
int j;


if(Amps<sum+0.07 && Amps>sum-0.03){for(j=0;j<r;j++){c[ind[j]]=c[ind[j]]+1;}delay(1000); }

}


void ask()
{
  int i=0;
 
  mySerial.print("Enter the no. of appliances in your house ");
 
  while (mySerial.available() == 0);
  app=mySerial.parseInt();
  mySerial.print(app);mySerial.print("\n");
 
  for(i=0;i<app;i++){
    mySerial.print("Enter the watt of the appliance no. "); mySerial.print(i+1); mySerial.print(" ");
    while (mySerial.available() == 0);
    a[i]=mySerial.parseInt();
    mySerial.print( a[i]);
    mySerial.print("\n");
  }
 
}

void dp()
{
 int i=0;
   mySerial.print("The no. of appliances entered by you are "); mySerial.print(app);
   mySerial.print("\n");
   for(i=0;i<app;i++){
     mySerial.print(a[i]);mySerial.print(" ");mySerial.print(b[i]);mySerial.print("\n");
   }
    
 mySerial.print("\n");
}

void current()
{
 int i=0;
  
   for(i=0;i<app;i++){
    b[i]=a[i]/220;
   }
}

void result()
{
  int Tpower=0,i;
 mySerial.print("The total power consumed was in Ws was in the past minute : ");
 
  for(i=0;i<app;i++){
   Tpower=Tpower+(a[i]*c[i]); 
    }
  mySerial.print(Tpower);mySerial.print("\n");
i=0;
 
 mySerial.print("The individual running time of each appliance was : "); mySerial.print("\n");

 for(i=0;i<app;i++){
   mySerial.print("Running time of Appliance no. ");mySerial.print(i+1);mySerial.print(" is "); mySerial.print(c[i]);
   mySerial.print(" and power consumed in last minute is "); mySerial.print(a[i]*c[i]); mySerial.print(" in Ws "); mySerial.print("\n");
  c[i]=0;
 }
  
 mySerial.print("\n");
}

