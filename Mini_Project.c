#include <stdio.h>
#include <string.h>

#define  WITH_ENGINE_TEMP_CONTROLLER 1 //1 to take engine temperature in consideration, any other number in order not

typedef enum{
	on,off
}state;

typedef struct{//Structure to save the system info
	state engine_state;
	state AC_state;
	state engine_tempreture_controller_state;
	int speed;
	int room_temp;
	int engine_temp;
}system_info;

system_info s1={off,off,off,0,35,90},*ptr=&s1;
//initializing structure members to reasonable values
//pointer to structure to help edit,print members

void display_main_menu();//function that begins the program
void sensors_set_menu();//function that changes the system state
void Set_the_traffic_light_color();//function in control of speed
void Set_the_room_tempreture();//function in control of air conditioning
#if(WITH_ENGINE_TEMP_CONTROLLER==1)
void set_engine_tempreture();//function in control of engine temperature controller
#endif
void system_state();//function that display the system state

void (*ptf[3])()={display_main_menu,sensors_set_menu,system_state};//array of three (pointers to functions) as these three functions are called multiple times so it makes it easier to call them

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);setvbuf(stderr, NULL, _IONBF, 0);
	ptf[0]();//beginning the program by calling the function that starts the program
	printf("Good bye");//this line declares the end of the program
}

void display_main_menu()
{
	while(1){
		char input;
		printf("a. Turn on the vehicle engine\nb. Turn off the vehicle engine\nc. Quit the system\n\nChoice: ");
		scanf(" %c",&input);
		switch(input){
		case 'a':
		case 'A':
			ptr->engine_state=on;
			printf("Turn on the vehicle engine\n\n");
			ptf[1]();//calling the function in control of editing the system state
			break;
		case 'b':
		case 'B':
			ptr->engine_state=off;
			printf("Turn off the vehicle engine\n\n");
			continue;//function recalls itself until the input is either a or c
		case 'c':
		case 'C':
			printf("Quit the system\n\n");//end program
			return;
		default:
			printf("wrong input\n\n");
			continue;
		}//end switch
	}//end while
}

void sensors_set_menu()
{
	//calling functions in control of each member of system state
	while(1){
		char input;
		printf("a. Turn off the engine\nb. Set the traffic light color\nc. Set the room temperature\n");
#if(WITH_ENGINE_TEMP_CONTROLLER==1)
		printf("d. Set the engine temperature\n");
#endif
		printf("\nChoice: ");
		scanf(" %c",&input);
		switch(input){
		case 'a':
		case 'A':
			return;
		case 'b':
		case 'B':
			Set_the_traffic_light_color();
			break;
		case 'c':
		case 'C':
			Set_the_room_tempreture();
			break;
#if(WITH_ENGINE_TEMP_CONTROLLER==1)
		case 'd':
		case 'D':
			set_engine_tempreture();
			break;
#endif
		default:
			printf("wrong input\n\n");
			continue;
		}//end switch
	}//end while
}

void Set_the_traffic_light_color()
{
	while(1)
	{
		char traffic_light_color;
		printf("Enter traffic light color:\n'G' for green\n'O' for orange\n'R' for red\n\nChoice: ");
		scanf(" %c",&traffic_light_color);
		if(traffic_light_color=='G'||traffic_light_color=='g')
		{
			ptr->speed=100;
			break;
		}
		else if(traffic_light_color=='o'||traffic_light_color=='O')
		{
			ptr->speed=30;
			break;
		}
		else if(traffic_light_color=='r'||traffic_light_color=='R')
		{
			ptr->speed=0;
			break;
		}
		else
		{
			printf("wrong input\n\n");
			continue;
		}

	}//end while
	ptf[2]();//to display system state after editing the speed
	return;//return to the choices
}

void Set_the_room_tempreture()
{
	int temperature;
	printf("Enter room temperature: ");
	scanf("%d",&temperature);
	//if-else if-else to control the air conditioner and the room temperature members of structure
	if(temperature<10){
		ptr->AC_state=on;
		ptr->room_temp=20;
	}
	else if(temperature>30){
		ptr->AC_state=on;
		ptr->room_temp=20;
	}
	else{
		ptr->AC_state=off;
	}
	ptf[2]();//to display system state after editing the room temperature and AC state
	return;//return to the choices
}
#if(WITH_ENGINE_TEMP_CONTROLLER==1)
void set_engine_tempreture()
{
	int temperature;
	printf("Enter engine temperature: ");
	scanf("%d",&temperature);
	//if-else if-else to control the engine temperature controller and the engine temperature members of structure
	if(temperature<100){
		ptr->engine_tempreture_controller_state=on;
		ptr->engine_temp=125;
	}
	else if(temperature>150){
		ptr->engine_tempreture_controller_state=on;
		ptr->engine_temp=125;
	}
	else{
		ptr->engine_tempreture_controller_state=off;
	}
	ptf[2]();//to display system state after editing the engine temperature and engine temperature controller
	return;//return to the choices
}
#endif
void system_state()
{
	if((ptr->speed)==30)//to adjust members before printing the system state.
	{
		if(ptr->AC_state==off)//to not apply condition unless the air conditioner is off
		{
			ptr->AC_state=on;
			ptr->room_temp=((5/4)*ptr->room_temp)+1;
		}
#if(WITH_ENGINE_TEMP_CONTROLLER==1)
		if(ptr->engine_tempreture_controller_state==off)//to not apply condition unless the engine temperature controller is off
		{
			ptr->engine_tempreture_controller_state= on;
			ptr->engine_temp=((5/4)*ptr->engine_temp)+1;
		}
#endif
	}//end if
	(ptr->engine_state==on)?puts("Engine is on."):puts("Engine is off.");
	(ptr->AC_state==on)?puts("AC is on."):puts("AC is off.");
	printf("Vehicle Speed: %d Km/Hr.\n",ptr->speed);
	printf("Room Temperature: %d C.\n",ptr->room_temp);
#if(WITH_ENGINE_TEMP_CONTROLLER==1)
	(ptr->engine_tempreture_controller_state==on)?puts("Engine temperature controller is on."):puts("Engine temperature controller is off.");
	printf("Engine Temperature: %d C.\n",ptr->engine_temp);
#endif
	printf("\n");
}
