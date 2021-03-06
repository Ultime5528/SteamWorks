#include "Commands/AutoBallesGearBleu.h"

#include "Tourner.h"
#include "Shoot.h"
#include "MonterBalle.h"
#include "StopShoot.h"
#include "Avancer.h"
#include "Viser.h"
#include "Spin.h"
#include "ShootClosed.h"
#include <Commands/WaitCommand.h>

double AutoBallesGearBleu::VITESSE_SHOOT(79.8);

AutoBallesGearBleu::AutoBallesGearBleu(double timeout) {

	AddParallel(new MonterBalle());
	AddParallel(new Spin());
	AddSequential(new WaitCommand("Attente AutoBallesGearBleu", 0.7));
	AddParallel(new Shoot(VITESSE_SHOOT));
	AddSequential(new WaitCommand("Attente AutoBallesGearRouge", timeout));
	AddParallel(new ShootClosed());

	AddSequential(new Tourner(-32, -63, -0.7, 0.3, 1.3));
	//AddSequential(new Tourner(-28, -57, -0.7, 0.3, 1.3));
	AddParallel(new StopShoot());

	AddSequential (new Avancer(-6.0, -8.0, -0.805, 0.54, 1.7));
	//AddSequential (new Avancer(-7.0, -10.0, -0.805, 0.54, 1.7));

	AddSequential(new Tourner(-92.31416, -130, -0.85, 0.68, 1.7));
	//AddSequential(new Tourner(-100, -136, -0.85, 0.68, 1.7));

	AddSequential(new Avancer(2.5, 3.0, 0.6, 0.0, 2.0));


	AddSequential(new Viser());


}
