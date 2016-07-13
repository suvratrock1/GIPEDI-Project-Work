
    const int analogIn = A0;
   
    int mVperAmp = 100; 
    int RawValue= 0;
    int ACSoffset = 2500;
    double Voltage = 0;
    double Amps = 0;
    int app;
    double a[10];
    double b[10];
    double c[10];
    unsigned long ptime=0;

    
void setup()
{
    Serial.begin(9600);
    
    ask(); // Function to ask the user to enter the no. of appliances
           // and their respective power ratings
           
    current(); // Function to determine current consumption value of each appliance at 220volts
    
    dp(); // Function to display data entered by the user
}

void loop()
{
  
  unsigned long ctime=millis();
  RawValue = analogRead(analogIn);
  Voltage = (RawValue / 1023.0) * 5000; // Gets you mV
  Amps = ((Voltage - ACSoffset) / mVperAmp);
  Amps=Amps+0.12; //Error Correction
   if(Amps<0)
  {
    Amps=Amps*(-1);
  }
  
  int r;
int n;

for(r=1;r<=app;r++){
 n=app;
ga(b,n,r); // Function to generate non repetetive combinations
           // of current consumption of each appliance
           // as determined by the power ratings entered by the user
}

// To print result after every 60000 milli seconds
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


if(Amps<sum+0.1 && Amps>sum-0.1){for(j=0;j<r;j++){c[ind[j]]=c[ind[j]]+1;} delay(1000);}

}


void ask()
{
  int i=0;
 
  Serial.print("Enter the no. of appliances in your house ");
 
  while (Serial.available() == 0);
  app=Serial.parseInt();
  Serial.print(app);Serial.print("\n");
 
  for(i=0;i<app;i++){
    Serial.print("Enter the watt of the appliance no. "); Serial.print(i+1); Serial.print(" ");
    while (Serial.available() == 0);
    a[i]=Serial.parseInt();
    Serial.print( a[i]);
    Serial.print("\n");
  }
  
 
}

void dp()
{
 int i=0;
   Serial.print("\nThe no. of appliances entered by you are "); Serial.print(app);
   Serial.print("\n");
   Serial.print("Entered Watts        Current Consumption(in Amps) \n");
   for(i=0;i<app;i++){
     Serial.print(a[i]);Serial.print("                 ");Serial.print(b[i]);Serial.print("\n");
   }
    
 Serial.print("\n");
 
}

void current()
{
 int i=0;
  
   for(i=0;i<app;i++){
    b[i]=a[i]/220; // For 220volts power supply
   }
}

void result()
{
  int Tpower=0,i;
 Serial.print("The total power consumed in the past one minute was (in Ws) :");
 
  for(i=0;i<app;i++){
   Tpower=Tpower+(a[i]*c[i]); 
    }
  Serial.print(Tpower);Serial.print("\n");
i=0;
 
 Serial.print("The individual running time of each appliance was : "); Serial.print("\n");

 for(i=0;i<app;i++){
   Serial.print("Running time of Appliance no. ");Serial.print(i+1);Serial.print(" is "); Serial.print(c[i]);
   Serial.print(" seconds and power consumed in the past minute was "); Serial.print(a[i]*c[i]); Serial.print(" in Ws "); Serial.print("\n");
  c[i]=0; 
 }
  
 Serial.print("\n");
 
}


