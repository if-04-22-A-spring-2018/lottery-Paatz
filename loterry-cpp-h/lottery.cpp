/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			lottery.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * Implementation of a library for analyzing lottery tips.
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lottery.h"
#define 	UUID_LEN   40
#define 	MAX_TIP_LEN   17
#define 	MAX_LINE_LEN   (UUID_LEN + 1 + MAX_TIP_LEN + 1)

static char * currentFileName;
static char c;
static int* draw;
static bool set = false;

bool init_lottery(char* filename, char j)
{
	 c=j;
	 set = false;
	 FILE* fd= fopen(filename, "r");
	 currentFileName = filename;
	 if(fd == 0)
	 {
		 return false;
	 }
	 fclose(fd);

	 return true;
}

bool get_tip(int tip, int* array)
{
  	FILE* fd= fopen(currentFileName, "r");

		if(tip < 0 || fd == 0 ){
        fclose(fd);
        return false;
    }

    char* line ;
		int i = 0;
		char buffer[MAX_LINE_LEN] = {0};
    while(line != 0 && i <= tip) {
        line = fgets(buffer, MAX_LINE_LEN, fd);
        i++;
        if (line != buffer) {
            fclose(fd);
            return false;
        }
    }


    int r = 0;

    while( r < UUID_LEN  && buffer[r] != c ){
        r++;
    }

    int count = 0;

    int num = 0;
    while(count < 6){
        r++;
        if(buffer[r]<= '9' && buffer[r]>= '0'){
            num = num * 10 + (buffer[r]-'0');
        }
        else{
            array[count] = num;
            num = 0;
            count++;
        }
    }

    fclose(fd);
    return true;
}

bool set_drawing(int* array)
{
	set = true;
	draw = array;
	return false;

}

int get_tip_result(int tip)
{
	if(!set)
	{
		return -1;
	}

		int bb[6];

    if(!get_tip(tip, bb))
		{
			return -2;
		}
    int count = 0;
    for (int i = 0; i < 6; ++i)
		{
        for (int r = 0; r < 6; ++r)
				 {
            if(bb[i] == draw[r])
						{
							count++;
						}

         }
    }
    return count;
}
int get_right_tips_count(int tip)
{
	if(!set|| tip < 0 || tip > TIP_SIZE)
	{
		return -1;
	}

    int i = 0;
    int counter = 0;
    int second = 0;

    while(second != -2&& second != -1){
        second = get_tip_result(i);
        if(second == tip)
				{
					counter++;
				}
        i++;
    }

    return counter;
}
