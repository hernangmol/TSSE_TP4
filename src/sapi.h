// sapi.h ficticia para poder testear

int LPC_GPIO_PORT;

int Chip_GPIO_SetPinDIROutput(int, int, int);
int Chip_GPIO_SetPinDIRInput(int, int, int);
int Chip_GPIO_SetPinOutHigh(int, int, int);
int Chip_GPIO_SetPinOutLow(int, int, int);
int Chip_GPIO_GetPinState(int, int, int);