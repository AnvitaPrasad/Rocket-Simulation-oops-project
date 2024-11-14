#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <thread> // Ensure this header is included
#include <chrono>

class Rocket {
private:
    double roll, yaw, pitch;         // Euler angles
    double finAngle;                 // Fin angle
    double position;                 // Inertial position (height)
    double velocity;                 // Inertial velocity
    double fuel;                     // Fuel amount
    double thrust;                   // Thrust force
    double burnTime;                 // Burn time
    double acceleration;             // Acceleration

public:
    Rocket() : roll(0), yaw(0), pitch(0), finAngle(0), position(0), 
               velocity(0), fuel(1000), thrust(50), burnTime(10), acceleration(0) {
        std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed for random numbers
    }

    // Overload the << operator for displaying rocket status
    friend std::ostream& operator<<(std::ostream& os, const Rocket& r) {
        os << std::fixed << std::setprecision(2);
        os << "Position: " << r.position << " m\n";
        os << "Velocity: " << r.velocity << " m/s\n";
        os << "Roll: " << r.roll << " degrees, Yaw: " << r.yaw << " degrees, Pitch: " << r.pitch << " degrees\n";
        os << "Fin Angle: " << r.finAngle << " degrees\n";
        os << "Fuel: " << r.fuel << " kg\n";
        os << "Acceleration: " << r.acceleration << " m/s²\n";
        return os;
    }

    void updateEulerAngles() {
        roll = static_cast<double>(std::rand() % 360);
        yaw = static_cast<double>(std::rand() % 360);
        pitch = static_cast<double>(std::rand() % 360);
        finAngle = (roll + yaw + pitch) / 3; // Simple balance based on angles
    }

    void updateInertialParameters(double deltaTime) {
        if (fuel > 0) {
            // Calculate acceleration and update position and velocity
            acceleration = thrust / (mass() + fuel); // Simplified mass calculation
            velocity += acceleration * deltaTime;
            position += velocity * deltaTime;
            fuel -= thrust * deltaTime / 100; // Decrement fuel based on thrust and time

            if (fuel < 0) fuel = 0; // Ensure fuel doesn't go negative
        } else {
            // If fuel is depleted, rocket will coast upwards
            acceleration = -9.81; // Gravity pulls down
            velocity += acceleration * deltaTime;
            position += velocity * deltaTime;
        }
    }

    double mass() const {
        return 100 + fuel; // Assume rocket mass without fuel is 100 kg
    }

    void launch() {
        std::cout << "Rocket Launching...\n";
        double deltaTime = 0.1; // Update every 0.1 seconds
        while (fuel > 0 || velocity > 0) {
            updateEulerAngles();
            updateInertialParameters(deltaTime);
            std::cout << *this; // Display current status
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Sleep for 100ms
        }
        std::cout << "Rocket has reached apogee. Launch complete.\n";
    }
};

int main() {
    Rocket rocket;
    rocket.launch();
    return 0;
}
