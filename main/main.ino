class Ultrasonic{
	public:
		byte trigPin,echoPin;
		unsigned long duration;
		Ultrasonic(byte triggerPin,byte echo_Pin){
			trigPin = triggerPin;
			echoPin = echo_Pin;
  		pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  		pinMode(echoPin, INPUT); // Sets the echoPin as an Input
		}

		int read(){
  		// Clears the trigPin
  		digitalWrite(trigPin, LOW);
  		delayMicroseconds(2);
  		// Sets the trigPin on HIGH state for 10 micro seconds
  		digitalWrite(trigPin, HIGH);
  		delayMicroseconds(10);
  		digitalWrite(trigPin, LOW);
  		// Reads the echoPin, returns the sound wave travel time in microseconds
  		duration = pulseIn(echoPin, HIGH);
  		// Calculating the distance(cm) by duration(ms) x speed of sound(340m/s) / 2 (sound wave bounce time) 
  		return round(duration * 0.034 / 2);
		}
};

Ultrasonic ultrasY(11,10);
Ultrasonic ultrasX(6,5);

class Vector{
	public:
		short x,y;
		Vector(short _x,short _y){
			x = _x;
			y = _y;
		}
};

Vector kaplal(0,0);

struct reference{
	short x,y,diffX,diffY;
}referee ;

void init_setup(){
	// double degres = mapDouble(analogRead(A0),0.0,1023.0,0.0,360.0);
	referee.x = mapDouble(analogRead(A0),0.0,1023.0,0.0,360.0);
	referee.y = referee.x + 90;
}

void setup() {
  Serial.begin(9600); // Starts the serial communication
	init_setup();
	Serial.println(referee.x);
	Serial.println(referee.y);
}
void loop() {
	//test();
}

// map() math function with decimal-point implementation
double mapDouble(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void test(){
	Serial.print("X: "); Serial.print(ultrasX.read());
	Serial.print("\tY: "); Serial.print(ultrasY.read());

	// Substitute magnetometer compasss module with a simple potentiometer
	 Serial.print("\tPotRot: "); Serial.println(mapDouble(analogRead(A0),0.0,1023.0,0.0,360.0));
	delay(200);
}
