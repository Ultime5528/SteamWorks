// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<Joystick> stick;
	std::shared_ptr<Joystick> gamepad;
	std::shared_ptr<JoystickButton> bouton1;
	std::shared_ptr<JoystickButton> bouton2;
	std::shared_ptr<JoystickButton> bouton3;
	std::shared_ptr<JoystickButton> bouton4;
	std::shared_ptr<JoystickButton> bouton5;
	std::shared_ptr<JoystickButton> bouton6;
	std::shared_ptr<JoystickButton> bouton7;
	std::shared_ptr<JoystickButton> bouton9;
	std::shared_ptr<JoystickButton> bouton10;
	std::shared_ptr<JoystickButton> bouton11;

	std::shared_ptr<JoystickButton> gboutonA;
	std::shared_ptr<JoystickButton> gboutonB;
	std::shared_ptr<JoystickButton> gboutonX;




    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
public:
	OI();

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

	std::shared_ptr<Joystick> getStick();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
};

#endif
