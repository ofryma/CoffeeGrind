 #include <IRremote.h>


#define relay_1 3
#define warnning_led 13

IRrecv irrcv(12);
decode_results results;

int flag = 1;
int i=0;
int lamp_state=0;
int zero = 23591
int one = 2023
int two = 22711
int three = -20569
int lamp = 6975
int slp = 16375

void setup() {
  
  Serial.begin(9600);
  pinMode(relay_1,OUTPUT);
  pinMode(warnning_led,OUTPUT);
  irrcv.enableIRIn();
  
}

void loop() {

  // 0 - 23591
  // 1 - 2023
  // 2 - 22711
  // 3 - (-20569)
  //Lamp- 6975
  //SLP - 16375
  

    if(flag){
      i=0;
    for(i;i<4;i++){
      Serial.println("  ");
    }
    Serial.println("System Ready...");
    i=0;
    for(i;i<4;i++){
      Serial.println("  ");
    }
    flag=0;
  }

  if (irrcv.decode(&results)){
    //Serial.println(int(results.value));
    val = int(results.value)
    if(val==zero){
      Serial.println("*** E-Nose Protocol Selected - 8 times");
      warnningAlert();
      EnoseProtocol(8); 
      flag=1;
    }
    else if(val==one){
      Serial.println("*** E-Nose Protocol Selected - 16 times");
      warnningAlert();
      EnoseProtocol(16); 
      flag=1;
      delay(3000);
    }
    else if(val==two){
      Serial.println("*** Grinding Protocol Selected - 8 times");
      warnningAlert();
      GrindingProtocol(8); 
      flag=1;
    }
    else if(val==three){
      Serial.println("*** Grinding Protocol Selected - 16 times");
      warnningAlert();
      GrindingProtocol(16); 
      flag=1;
    }
    else if(val==slp){
      
    }
    else if(val==lamp){
      if(lamp_state){
        digitalWrite(relay_1,LOW);
        lamp_state=0;
      }
      else{
        digitalWrite(relay_1,HIGH);
        lamp_state=1;
      }
    } 


    irrcv.enableIRIn();
  }
  

  

}


//protocols

void GrindingProtocol(int iter){
  int time_interval1 = 750; //milliseconds
  int time_interval2 = 750;
  int iter_num = iter; //number of iterations for this function
  int i=0;

  Serial.println("Grinding Protocol: Started");
  
  while(i<iter_num){
    digitalWrite(relay_1,HIGH);
  delay(time_interval1);
  digitalWrite(relay_1,LOW);
  delay(time_interval2);
  i=i+1;
    
  }

  Serial.println("Grinding Protocol: Ended");
  
  
}
void EnoseProtocol(int iter){

  int time_interval = 1500; //milliseconds
  int iter_num = iter; //number of iterations for this function
  int i=0;

  Serial.println("E-Nose Protocol: Started");
  
  while(i<iter_num){
    digitalWrite(relay_1,HIGH);
    delay(time_interval);
    digitalWrite(relay_1,LOW);
    delay(time_interval);
    i++;
  }
  Serial.println("E-Nose Protocol: Ended");
}

void warnningAlert(){
int i=0;
int blink_num=7;
  for(i;i<blink_num;i++){
    digitalWrite(warnning_led,HIGH);
    delay(100);
    digitalWrite(warnning_led,LOW);
    delay(100);
  }
  delay(1000);
}
int saftyPress(){

  // 0 - 23591
  // 1 - 2023
  // 2 - 22711
  // 3 - (-20569)
  //Lamp- 6975
  //SLP - 16375
  
  int val ;

  irrcv.enableIRIn();
  if (irrcv.decode(&results)){
    
    val=int(results.value);

    if(val==23591 || val== 2023 || val==22711 || val==(-20569) || val==6975 || val==16375){
    return 1;
    }
  return 0;

    
  }
}  
