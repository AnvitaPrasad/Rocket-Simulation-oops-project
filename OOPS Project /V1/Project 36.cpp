#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <thread>  // For std::this_thread::sleep_for

class EulerAngles {
public:
    double roll, pitch, yaw;

    EulerAngles() : roll(0.0), pitch(0.0), yaw(0.0) {}

    // Overload ++ operator to simulate change in angles
    EulerAngles& operator++() {
        roll += (std::rand() % 10 - 5) * 0.1;  // Random small change
        pitch += (std::rand() % 10 - 5) * 0.1;
        yaw += (std::rand() % 10 - 5) * 0.1;
        return *this;
    }

    void display() const {
        std::cout << "Roll: " << roll << ", Pitch: " << pitch << ", Yaw: " << yaw << '\n';
    }
};

class FinAngle {
public:
    double angle;

    FinAngle() : angle(0.0) {}

    // Function to set fin angle based on the specific influence of roll, pitch, and yaw
    void setAngle(double pitchInfluence, double yawInfluence, double rollInfluence) {
        angle = pitchInfluence + yawInfluence + rollInfluence;
    }

    void display(int finNumber) const {
        std::cout << "Fin " << finNumber << " Angle: " << angle << " degrees\n";
    }
};

class Rocket {
    double fuel;
    double mass;
    double thrust;
    double burnRate;
    double altitude;       // Altitude above the ground
    double verticalSpeed;  // Vertical speed component
    double acceleration;
    FinAngle fins[4];      // Array to represent four fins

public:
    Rocket(double initialFuel, double rocketMass, double thrustForce, double burnRate)
        : fuel(initialFuel), mass(rocketMass), thrust(thrustForce), burnRate(burnRate),
          altitude(0.0), verticalSpeed(0.0), acceleration(0.0) {}

    // Overload += operator to simulate fuel consumption and rocket motion
    Rocket& operator+=(double timeStep) {
        if (fuel > 0) {
            fuel -= burnRate * timeStep;  // Decrease fuel
            if (fuel < 0) fuel = 0;       // Prevent negative fuel

            acceleration = (thrust / mass) - 9.81;  // Simplified model: thrust minus gravity
            verticalSpeed += acceleration * timeStep;  // Update vertical speed
            altitude += verticalSpeed * timeStep;      // Update altitude based on vertical speed

            // Simple handling to stop the simulation if altitude goes negative (rocket is falling)
            if (altitude < 0) altitude = 0;
        } else {
            // Gravity acts alone after fuel is depleted
            acceleration = -9.81;
            verticalSpeed += acceleration * timeStep;
            altitude += verticalSpeed * timeStep;
            if (altitude < 0) altitude = 0;
        }
        return *this;
    }

    // Getter for altitude
    double getAltitude() const {
        return altitude;
    }

    // Overload [] operator to access fins
    FinAngle& operator[](int index) {
        return fins[index];
    }

    bool isFuelAvailable() const {
        return fuel > 0;
    }

    void displayStatus() const {
        std::cout << "Fuel: " << fuel << " kg, " << " Vertical Speed: " 
                  << verticalSpeed << " m/s, Acceleration: " << acceleration << " m/s^2\n";
    }

    void preLaunchCheck() {
        std::cout << "Initiating pre-launch checks...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Fuel level: OK\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Thrust system: OK\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Guidance system: OK\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "All systems go. Preparing for launch...\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
};

// Main function to simulate rocket flight
int main() {
    std::srand(std::time(0));  // Seed random number generator

    // Ask user for rocket parameters
    double initialFuel, thrustForce, burnRate;
    std::cout << "Enter the initial fuel amount (kg): ";
    std::cin >> initialFuel;
    std::cout << "Enter the thrust force (N): ";
    std::cin >> thrustForce;
    std::cout << "Enter the burn rate (kg/s): ";
    std::cin >> burnRate;

    // Initialize components with user inputs
    EulerAngles eulerAngles;
    Rocket rocket(initialFuel, 1000.0, thrustForce, burnRate);  // Mass set as 1000 kg for simplicity

    double timeStep = 0.1;  // Simulation time step (in seconds)
    int step = 0;

    // Launch sequence
    rocket.preLaunchCheck();

    // Launch loop
    while (rocket.isFuelAvailable() || rocket.getAltitude() > 0) {  // Continue until fuel runs out and altitude is zero
        std::cout << "Time: " << step * timeStep << "s\n";

        // Update and display Euler angles
        ++eulerAngles;  // Increment Euler angles to simulate atmospheric changes
        eulerAngles.display();

        // Update and display each fin angle based on different combinations of Euler angles
        rocket[0].setAngle(eulerAngles.pitch * 0.8, eulerAngles.yaw * 0.1, eulerAngles.roll * 0.1);  // Fin 1
        rocket[1].setAngle(eulerAngles.pitch * 0.1, eulerAngles.yaw * 0.8, eulerAngles.roll * 0.1);  // Fin 2
        rocket[2].setAngle(eulerAngles.pitch * 0.5, eulerAngles.yaw * 0.2, eulerAngles.roll * 0.3);  // Fin 3
        rocket[3].setAngle(eulerAngles.pitch * 0.2, eulerAngles.yaw * 0.5, eulerAngles.roll * 0.3);  // Fin 4

        // Display fin angles
        for (int i = 0; i < 4; ++i) {
            rocket[i].display(i + 1);
        }

        // Update and display rocket status
        rocket += timeStep;  // Fuel consumption and altitude update
        rocket.displayStatus();

        std::cout << "---------------------------------------\n";

        step++;

        // Delay for visibility (simulate time passing in a real-time environment)
        if (rocket.isFuelAvailable() || rocket.getAltitude() > 0) 
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "\nRocket has reached apogee and landed. Simulation ended.\n";
    return 0;
}

