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
} deg;

// Overall space of box = 200x200
const int totalX = 200;
const int totalY = 200;

void setup() {
  Serial.begin(9600); // Starts the serial communication
	deg.adjref = mapDouble(analogRead(A0),0.0,1023.0,0.0,360.0);
	Serial.println(deg.adjref);
}
void loop() {
	//test();
}

// map() math function with decimal-point implementation
double mapDouble(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

Vector getCoordinate(){
	deg.compass = mapDouble(analogRead(A0),0.0,1023.0,0.0,360.0);
	deg.angleDiff = deg.compass - deg.adjref;

	// Right-angled triangle's adjacent segway 
	if (abs(deg.angleDiff) >= 45){
		if(deg.angleDiff < 0){
			deg.adjref -= 90;		// Set the next quadrant
		}
		else if (deg.angleDiff > 0){
			deg.adjref += 90;		// Set the previous quadrant
		}
		deg.angleDiff = deg.compass - deg.adjref;	// Calc new angleDiff with new adjacent
	}
	
	ultrasA.update();
	ultrasB.update();
	double x,y;

	// All quadrants in these conditionals are rotated -45 as the shape of the space is a box (4-gons)
	if (deg.compass > 315.0 && deg.compass < 45.0){
		y = totalY - (ultrasA.value * cos(deg.angleDiff));
		x = totalX - (ultrasB.value * cos(deg.angleDiff));
	}
	else if (deg.compass > 225  && deg.compass < 135){
		x = ultrasA.value * cos(deg.angleDiff);
		y = totalY - (ultrasB.value * cos(deg.angleDiff));
	}
	else if (deg.compass > 135 && deg.compass < 225){
		x = ultrasB.value * cos(deg.angleDiff);
		y = ultrasA.value * cos(deg.angleDiff);
	}
	else if (deg.compass > 45 && deg.compass < 135){
		x = totalX - (ultrasA.value * cos(deg.angleDiff));
		y = ultrasB.value * cos(deg.angleDiff);
	}
	Vector tmp(x,y);
	return tmp;
}

void setupTest(){
	ultrasA.update();
	ultrasB.update();
	Serial.print("X: "); Serial.print(ultrasB.value);
	Serial.print("\tY: "); Serial.print(ultrasA.value);

	// Substitute magnetometer compasss module with a simple potentiometer
	 Serial.print("\tPotRot: "); Serial.println(mapDouble(analogRead(A0),0.0,1023.0,0.0,360.0));
	delay(200);
}

void coordinateTest(){
	Serial.print("Compass: "); Serial.print(deg.compass);
	Serial.print("\tDiff: "); Serial.print(deg.angleDiff); 
	Serial.print("\tpos: "); Serial.print(getCoordinate().x); Serial.print(","); Serial.println(getCoordinate().y);

	delay(100);
}

