#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, char* argv[]) {

	char* brightness_file_path = "/sys/class/backlight/intel_backlight/brightness";
	FILE* brightness_file = fopen(brightness_file_path,"w+");
	char current_brightness_str[10];
	fgets(current_brightness_str,10,brightness_file);
	
	char* max_brightness_file_path = "/sys/class/backlight/intel_backlight/max_brightness";
	FILE* max_brighness_file = fopen(max_brightness_file_path,"r");
	char max_brightness_str[10];
	fgets(max_brightness_str,10,max_brighness_file);

	int current_brightness_int = atoi(current_brightness_str);
	int max_brightness_int = atoi(max_brightness_str);
	int min_brightness_int = 0;

	int update_brightness_int = 0;
	char update_brightness_str[10];

	if(argc < 3){
		printf("Usage:\n\
						ani_backlightctl set <percentage>: Sets the monitor brightness percentage.\n\
						ani_backlightctl increase <percentage>: Increases the brightness by percentage.\n\
						ani_backlightctl decrease <percentage>: Decreases the brightness by percentage\n");
	}

	else{
		printf("%d\n",max_brightness_int);
		if(strcmp(argv[1],"set")==0){
			int set = atoi(argv[2]);
			update_brightness_int = (max_brightness_int/100)*set;
			printf("set: %d\n",update_brightness_int);
		}

		if(strcmp(argv[1],"increase")==0){
			int increase = atoi(argv[2]);
			update_brightness_int = current_brightness_int + (max_brightness_int/100)*increase;
			printf("increase: %d\n",update_brightness_int);
		}
		
		if(strcmp(argv[1],"decrease")==0){
			int decrease = atoi(argv[2]);
			update_brightness_int = current_brightness_int - (max_brightness_int/100)*decrease;
			printf("decrease: %d\n",update_brightness_int);
		}

			if(update_brightness_int>max_brightness_int){
				printf("Overflow\n");
				update_brightness_int = max_brightness_int;
			}
			if(update_brightness_int<1000){
				printf("Underflow\n");
				update_brightness_int = min_brightness_int;
			}
			printf("%d\n",update_brightness_int);
			sprintf(update_brightness_str,"%d",update_brightness_int);
			fputs(update_brightness_str,brightness_file);
			fclose(max_brighness_file);
			fclose(brightness_file);
	}
	return 0;
}
