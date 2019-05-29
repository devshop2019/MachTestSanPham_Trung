#include "Btn_Process.h"
#include "MachTest_SP_IO.h"

OneButton btn_start(BTN_START_PIN, false);
OneButton btn_next(BTN_NEXT_PIN, false);
OneButton btn_previous(BTN_PREVIOUS_PIN, false);

void buttonInit(){
	btn_next.attachClick(&Up_do_0_Click);
	btn_start.attachClick(&Start_do_1_Click);
	btn_previous.attachClick(&Down_do_0_Click);
}

void buttonLoop(){
	btn_start.tick();
	btn_next.tick();
	btn_previous.tick();
}