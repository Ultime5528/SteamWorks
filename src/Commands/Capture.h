#ifndef Capture_H
#define Capture_H

#include "Commands/Command.h"

class Capture : public Command {
public:
	Capture();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // Capture_H
