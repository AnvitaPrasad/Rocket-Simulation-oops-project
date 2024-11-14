void runSimulation(float thrust, float &fuel, float deltaTime) {
    PositionVelocity posVel;
    Acceleration accel;
    FinAngles fins;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-10, 10);
    float previousVelocity = 0.0;

    while (fuel > 0 || posVel.velocity > 0) { // Ensure loop continues as long as fuel or upward velocity exists
        // Generate random Euler angles
        EulerAngles euler(dist(gen), dist(gen), dist(gen));
        fins.adjustFins(euler);

        // Apply thrust only if fuel is sufficient
        if (fuel > thrust * deltaTime) {
            posVel.update(thrust, deltaTime);
            fuel -= thrust * deltaTime;
        } else if (fuel > 0) {
            // Use remaining fuel in the last iteration to apply scaled thrust and set fuel to 0
            posVel.update(fuel / deltaTime, deltaTime);
            fuel = 0;
        }

        // Calculate acceleration based on previous and current velocities
        float acceleration = accel.calculate(previousVelocity, posVel.velocity, deltaTime);
        previousVelocity = posVel.velocity;

        // Display the state of the rocket
        std::cout << "Euler Angles - Roll: " << euler.roll 
                  << " Pitch: " << euler.pitch 
                  << " Yaw: " << euler.yaw << std::endl;
        std::cout << "Fin Angles - Roll: " << fins.finRoll 
                  << " Pitch: " << fins.finPitch 
                  << " Yaw: " << fins.finYaw << std::endl;
        std::cout << "Position: " << posVel.position 
                  << " Velocity: " << posVel.velocity 
                  << " Fuel: " << fuel << std::endl;
        std::cout << "Acceleration: " << acceleration << std::endl;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        // Check if the rocket has reached apogee (velocity <= 0) and break if so
        if (posVel.velocity <= 0 && fuel <= 0) {
            std::cout << "Rocket has reached apogee at position: " << posVel.position << std::endl;
            break;
        }
    }

    // Final message if fuel runs out before reaching apogee
    if (fuel <= 0 && posVel.velocity > 0) {
        std::cout << "Fuel exhausted before reaching apogee. Rocket continues ascent due to momentum." << std::endl;
    }

    std::cout << "Simulation complete. Rocket has reached apogee or fuel is exhausted." << std::endl;
}
