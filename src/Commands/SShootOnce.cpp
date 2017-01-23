#include "SShootOnce.h"
#include "Robot.h"

SShootOnce::SShootOnce() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::shooter.get());
}

// Called just before this Command runs the first time
void SShootOnce::Initialize() {
	Robot::shooter->Shoot();
}

// Called repeatedly when this Command is scheduled to run
void SShootOnce::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool SShootOnce::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void SShootOnce::End() {
	Robot::shooter->ShootStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SShootOnce::Interrupted() {
	End();
}
