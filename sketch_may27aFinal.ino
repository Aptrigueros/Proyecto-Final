#define IN1  12
#define IN2  11
#define IN3  10
#define IN4  9

class StepperMotor {
  private:
    int stepsLeft;
    boolean direction;
    int steps;
    const int stepArray[8][4] = {
      {1, 0, 0, 0},
      {1, 1, 0, 0},
      {0, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 1, 0},
      {0, 0, 1, 1},
      {0, 0, 0, 1},
      {1, 0, 0, 1}
    };

  public:
    StepperMotor() : stepsLeft(4095), direction(true), steps(0) {
      pinMode(IN1, OUTPUT);
      pinMode(IN2, OUTPUT);
      pinMode(IN3, OUTPUT);
      pinMode(IN4, OUTPUT);
    }

    void setDirection(boolean dir) {
      direction = dir;
    }

    void setStepsLeft(int steps) {
      stepsLeft = steps;
    }

    void stepper() {
      digitalWrite(IN1, stepArray[steps][0]);
      digitalWrite(IN2, stepArray[steps][1]);
      digitalWrite(IN3, stepArray[steps][2]);
      digitalWrite(IN4, stepArray[steps][3]);
      updateDirection();
    }

    void updateDirection() {
      if (direction) {
        steps++;
      } else {
        steps--;
      }
      steps = (steps + 7) % 7;
    }

    void run() {
      while (stepsLeft > 0) {
        stepper();
        stepsLeft--;
        delay(1);
      }
      delay(300);
      direction = !direction;
      stepsLeft = 4095;
    }
};

StepperMotor myMotor;

void setup() {
  Serial.begin(115200);
}

void loop() {
  myMotor.run();
}

