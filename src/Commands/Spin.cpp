#include "Spin.h"
#include "Robot.h"
#include <cmath>
#include <Timer.h>
#include "../Subsystems/Shooter.h"

Spin::Spin() : Command("Spin") {

	Requires(Robot::shooter.get());

}

// Called just before this Command runs the first time
void Spin::Initialize() {

#ifdef DASHBOARD_VARIABLES

    Shooter::VITESSE = frc::Preferences::GetInstance()->GetDouble("shoot_vitesse", 79.0);
    Shooter::THRESHOLD = frc::Preferences::GetInstance()->GetDouble("shoot_threshold", 5.0);
    Shooter::SERVO_OPEN = frc::Preferences::GetInstance()->GetDouble("servo_open", 150.0);
    Shooter::SERVO_CLOSE = frc::Preferences::GetInstance()->GetDouble("servo_close", 100.0);

#endif

    Robot::shooter->SetAbsoluteTolerance(Shooter::THRESHOLD);
    Robot::shooter->SetSetpoint(Shooter::VITESSE);
    Robot::shooter->Enable();

}



void Spin::Execute() {

}


// Make this return true when this Command no longer needs to run execute()
bool Spin::IsFinished() {
	return false;
}


// Called once after isFinished returns true
void Spin::End() {

	Robot::shooter->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Spin::Interrupted() {
	End();
}
