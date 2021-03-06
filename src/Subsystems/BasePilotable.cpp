// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "Encoder.h"
#include "BasePilotable.h"
#include "../RobotMap.h"
#include "../Commands/Pilotage.h"

double BasePilotable::K_MOVE(0.63);
double BasePilotable::K_TURN(0.18);
double BasePilotable::B_TURN(0.33);
double BasePilotable::ACCEL_THRESHOLD(130.0);
double BasePilotable::DI_MOVE(105.0);
double BasePilotable::A_MOVE(10.0);

BasePilotable::BasePilotable() : Subsystem("BasePilotable")
{

    moteurG = RobotMap::basePilotableMoteurG;
    moteurD = RobotMap::basePilotableMoteurD;
    robotDrive = RobotMap::basePilotableRobotDrive;
    gyro = RobotMap::basePilotableGyro;

    encoderG = RobotMap::basePilotableEncoderG;
    encoderD = RobotMap::basePilotableEncoderD;

    gyro->Calibrate();

}



void BasePilotable::InitDefaultCommand()
{
        SetDefaultCommand(new Pilotage());
}


void BasePilotable::Drive()
{
	robotDrive->ArcadeDrive(Robot::oi->getStick().get()->GetX(), -Robot::oi->getStick().get()->GetY());
}


void BasePilotable::Drive(double move, double turn)
{
	robotDrive->ArcadeDrive(turn, move);
}


void BasePilotable::Stop()
{
	moteurG->Set(0);
	moteurD->Set(0);
}

void BasePilotable::Avancer(double value)
{
	Drive(value, 0.0);
}

void BasePilotable::Tourner(double value)
{
	Drive(0.0, value);
}


double BasePilotable::GetEncoderD()
{
	return encoderD->GetDistance();
}

double BasePilotable::GetEncoderG()
{
	return encoderG->GetDistance();
}

double BasePilotable::GetGyro()
{

	return gyro->GetAngleX();
}

double BasePilotable::GetAccelY()
{
	return -1 * gyro->GetAccelY();
}

void BasePilotable::EncoderReset()
{
	encoderD->Reset();
	encoderG->Reset();
}

void BasePilotable::GyroReset()
{
	gyro->Reset();
}



