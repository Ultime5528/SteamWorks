#include "StopShoot.h"
#include "Robot.h"


StopShoot::StopShoot() : Command("StopShoot") {

	Requires(Robot::shooter.get());

}

// Called just before this Command runs the first time
void StopShoot::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void StopShoot::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool StopShoot::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void StopShoot::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopShoot::Interrupted() {

}
