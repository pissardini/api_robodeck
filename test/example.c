#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../src/robodeck_api.c"

using namespace std;

int main(int argc, char *argv[]){
  if(connect_api()== 0){
	printf("Battery Level: %i\n", battery_api());
	disconnect_api();
  } else printf("Unable to connect to the platform.\n");
  return 0;
}
