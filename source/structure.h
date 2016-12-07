
void errExit(char *str);
typedef struct message{
	double last_ms;
	int last_frame;
	double bpm;
	unsigned long long start_time;

}Message;

struct timeval tv;
unsigned long long getCurrentTimestamp();
int detector(int pid, Message *addr);
void ledACT(Message *addr);
FILE *f_led, *f_aubio;

/*
struct timespec{
	time_t tv_sec; //seconds
	long tv_nsec; // nanoseconds
}

timeval
{
time_t tv_sec; //second [long int]
suseconds_t tv_usec; //microsecond [long int]

*/
