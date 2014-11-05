//Pin para el sensor de temperatura TMP36
int sensorPin = 0; // El pin analogico del TMP36 he TMP36's Vout (sense) pin is connected to
                   //La resolucion del pin es de 10mV/Grado centigrado con 500 mV offset, lo que permite llegar a temperaturas negativas (eso lei).
//Led RGB                       
int ledR = 11;  //Led Rojo
int ledG = 9;  //Led Verde
int ledB = 10;  //Led Azul
int altavoz = 13;

//"voltaje"
int vcc = 5;

//Metodo de inicializacion para el programa
void setup()
{
  Serial.begin(9600);  //Creamos una conexion serial con el PC para poder
                       //ver por consola (en el monitor) los valores.
  //Activamos los pin que vamos a usar
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(altavoz, OUTPUT);
}
 
void loop()                     // Bucle de repeticion del programa
{
 //Conseguimos la lectura del voltaje del sensor de temperatura
 //OJO: Lo que se lee no son voltajes ni temperatura, 
 //ya que este depende del voltaje que se le pasa al sensor.
 int lectura = analogRead(sensorPin);  
 
 //Convertimos la lectura a voltaje, 
 float voltaje = (lectura * vcc)/1024.0;
 
 // Imprimimos el voltaje por pantalla
 Serial.print(voltaje); Serial.println(" Voltios");
 
 // Ahora imprimimos la temperatura en funcion del voltaje
 float temperatura = (voltaje - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatura); Serial.println(" grados C\n");
 //Lo pruebo con temperaturas modificables facilmente, presionando alrededor del sensor con los dedos.
 //Tomo por debajo de 23º como temperatura fria, tocando con un cubito ha llegado a bajar hasta 14º 
 if(temperatura < 23){
   //Encendemos el led AZUL dando los colores en RGB
   analogWrite(ledR, 0);
   analogWrite(ledG, 0);
   analogWrite(ledB, 255);
   //Silenciamos el altavoz en caso de que estuviera sonando, y si no tambien.
   noTone(altavoz);
   //Esperamos 1 segundo
   delay(1000);   
 }else if(temperatura >= 23 && temperatura <25){
   //NARANJA
   analogWrite(ledR, 150);
   analogWrite(ledG, 255);
   analogWrite(ledB, 0);
   //Este bucle sirve para que pite intermitentemente el zumbador
   for( int i =0; i < 5; i++){
      //tone(pin, frecuencia)
      tone(altavoz,300); 
      delay(50);
      noTone(altavoz);
      delay(150);
   }
 }else{
   //ROJO
   analogWrite(ledR, 255);
   analogWrite(ledG, 0);
   analogWrite(ledB, 0);
   tone(altavoz,300);
   delay(1000);   
 }
 

}
