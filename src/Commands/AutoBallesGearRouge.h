#ifndef AutoBallesGearRouge_H
#define AutoBallesGearRouge_H

#include <Commands/CommandGroup.h>


class AutoBallesGearRouge : public CommandGroup {
public:
	static double VITESSE_SHOOT;

	AutoBallesGearRouge(double timeout = 3.0);
};

#endif  // AutoBallesGearRouge_H
