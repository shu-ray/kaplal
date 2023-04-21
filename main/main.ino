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
		
		int value;
		void update(){
  			// Clears the trigPin
  			digitalWrite(trigPin, LOW);
  			delayMicroseconds(2);
  			// Sets the trigPin on HIGH state for 10 micro seconds
  			digitalWrite(trigPin, HIGH);
  			delayMicroseconds(10);
  			digitalWrite(trigPin, LOW);
  			// Reads the echoPin, returns the sound wave travel time in microseconds
  			duration = pulseIn(echoPin, HIGH);
  			// Calculate the distance(cm) by duration(ms) x speed of sound(340m/s) / 2 (sound wave bounce time) 
  			value = round(duration * 0.034 / 2);
		}
};

Ultrasonic ultrasA(11,10);
Ultrasonic ultrasB(6,5);

class Vector{
	public:
		double x,y;
		Vector(double _x,double _y){
			x = _x;
			y = _y;
		}
};

Vector kaplal(0,0);

struct degrees{
	double compass;			// Current compass read
	double adjref;	// Which start of quadrant to be adjacent of formed right-angled triangle 
	double angleDiff;	// Subtraction of current compass read and referenced adjacent of quadrant

	// Indicate which ultrasonic readings to calculate X or Y axis coordinate value (X=0,  Y=1)
	bool flagA = 1;
	bool flagB = 0;
} deg;

void init_setup(){
	deg.adjref = mapDouble(analogRead(A0),0.0,1023.0,0.0,360.0);
}

Vector getCoordinates(){
	deg.compass = mapDouble(analogRead(A0),0.0,1023.0,0.0,360.0);
	deg.angleDiff = deg.compass - deg.adjref;

	double x,y;

	// Compass 
	if (deg.angleDiff){
		
	}

	ultrasB.update();
	ultrasA.update();

	Vector coordinate(0,0);
	return coordinate;
}

void setup() {
  Serial.begin(9600); // Starts the serial communication
	init_setup();
	Serial.println(deg.adjref);
}
void loop() {
	//test();
}

// map() math function with decimal-point implementation
double mapDouble(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void test(){
	ultrasA.update();
	ultrasB.update();
	Serial.print("X: "); Serial.print(ultrasB.value);
	Serial.print("\tY: "); Serial.print(ultrasA.value);

	// Substitute magnetometer compasss module with a simple potentiometer
	 Serial.print("\tPotRot: "); Serial.println(mapDouble(analogRead(A0),0.0,1023.0,0.0,360.0));
	delay(200);
}
