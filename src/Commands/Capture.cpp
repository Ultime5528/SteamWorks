#include "Capture.h"
#include <Robot.h>
#include <cmath>

Capture::Capture(): Command("Capture"), m_centreX(0.0), m_largeur(0.0) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires (Robot::camera.get());
}

// Called just before this Command runs the first time
void Capture::Initialize( ) {

	frc::Preferences* prefs = frc::Preferences::GetInstance();

	grip::GripPipeline::H_MIN = prefs->GetDouble("hmin", 61);
	grip::GripPipeline::H_MAX = prefs->GetDouble("hmax", 80.0);
	grip::GripPipeline::S_MIN = prefs->GetDouble("smin", 241.0);
	grip::GripPipeline::S_MAX = prefs->GetDouble("smax", 255.0);
	grip::GripPipeline::V_MIN = prefs->GetDouble("vmin", 96.0);
	grip::GripPipeline::V_MAX = prefs->GetDouble("vmax", 190.0);
	Camera::LTHRESHOLD = prefs->GetDouble("lthreshold", 150.0);
	Camera::XTHRESHOLD = prefs->GetDouble("xthreshold",0.05);
	BasePilotable::KTURN = prefs ->GetDouble("kturn", 1);
	BasePilotable::BTURN = prefs ->GetDouble("bturn",0);
	BasePilotable::KMOVE = prefs ->GetDouble("kmove",1);
	BasePilotable::BMOVE = prefs ->GetDouble("bmove",0);



	Camera::EXPOSURE = (int)prefs->GetDouble("exposure", 0);

	Robot::camera->StartGrip(&Capture::SetParam, this);
}

// Called repeatedly when this Command is scheduled to run
void Capture::Execute() {

	double centreX, largeur;

	{
		std::lock_guard<priority_mutex> lock(mutex);
		centreX = m_centreX;
		largeur = m_largeur;
	}

	double move, turn;


	if(std::abs(centreX) < Camera::XTHRESHOLD){
		turn = 0;
	}
	else {
		turn = BasePilotable::KTURN * centreX + BasePilotable::BTURN;
	}

	if(largeur >= Camera::LTHRESHOLD){
		move = 0;
	}
	else { move = BasePilotable::KMOVE/ largeur + BasePilotable::BMOVE;

	}









	Robot::basePilotable->Drive(move, turn);
	//Coeur de la commande

	frc::SmartDashboard::PutNumber("Centre X", centreX);
	frc::SmartDashboard::PutNumber("Largeur particule", largeur);

}

// Make this return true when this Command no longer needs to run execute()
bool Capture::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void Capture::End() {
	Robot::camera->EndGrip();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Capture::Interrupted() {
	End();
}

void Capture::SetParam(double centreX, double largeur)
{
	std::lock_guard<priority_mutex> lock(mutex);
	m_centreX = centreX;
	m_largeur = largeur;
}
