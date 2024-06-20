#include "DecisionTree.h"
Eloquent::ML::Port::DecisionTree weatherClassifier;
#include <math.h>
#include "DHT.h"

// Variable Declaration
float t;
float h;
float hic;
int prediction;

#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Welcome!");
  delay(10);

  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  // Read humidity
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Celsius (the default)
  float hic = calculate_heat_index(t,h);



  // Print values of temperature, humidity and heat index to serial monitor
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C  Heat index: "));
  Serial.print(hic);
  Serial.println(F("°C"));

  float input[3] = {t,h,hic};
  // Giving input values to predict Function
  int prediction = weatherClassifier.predict(input);

  // Checking Condition of weather
  Serial.print("Prediction: ");
  // Serial.print(prediction);
  if (prediction == 0){
    Serial.println("Foggy \U0001F32B");
  }
  else if(prediction == 1){
    Serial.println("Rainy \U0001F327");
  }
  else if(prediction == 2){
    Serial.println("Cloudy \u2601️");
  }
  else if(prediction == 3){
    Serial.println("Sunny \u2600");
  }

  Serial.println();

  delay(1000);
}

double calculate_heat_index(double temperature, double humidity) {
    // Coefficients for the heat index formula
    double c1 = -42.379;
    double c2 = 2.04901523;
    double c3 = 10.14333127;
    double c4 = -0.22475541;
    double c5 = -6.83783e-3;
    double c6 = -5.481717e-2;
    double c7 = 1.22874e-3;
    double c8 = 8.5282e-4;
    double c9 = -1.99e-6;

    // Calculate the heat index
    double heat_index = (c1 + (c2 * temperature) + (c3 * humidity) + (c4 * temperature * humidity) +
                         (c5 * pow(temperature, 2)) + (c6 * pow(humidity, 2)) +
                         (c7 * pow(temperature, 2) * humidity) + (c8 * temperature * pow(humidity, 2)) +
                         (c9 * pow(temperature, 2) * pow(humidity, 2)));

    // Adjustments for specific conditions
    if (humidity < 13 && (80 <= temperature && temperature <= 112)) {
        double adjustment = ((13 - humidity) / 4.0) * sqrt((17 - fabs(temperature - 95.0)) / 17);
        heat_index -= adjustment;
    } else if (humidity > 85 && (80 <= temperature && temperature <= 87)) {
        double adjustment = ((humidity - 85) / 10.0) * ((87 - temperature) / 5.0);
        heat_index += adjustment;
    }

    return heat_index;
}
